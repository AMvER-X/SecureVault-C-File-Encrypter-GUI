/*
Contains the actual logic for implementing our encryption algorithims from the libsodium library.
*/

#include "CryptoEngine.h"
#include "KeyDeriver.h"
#include <iostream>
#include <sodium.h>
#include <stdexcept>
#include <algorithm>
#include <cstring>

// --- Helper Implementation ---

std::vector<unsigned char> CryptoEngine::serializeFixedHeader(const Header& hdr){
    // Serialize fixed fields in little-endian form as they are laid out in memory.
    // Salt is written immediately after function
    std::vector<unsigned char> out;
    out.reserve(sizeof(Header)); // Optimisation: alloc memory in advance
    auto append = [&](const void* ptr, std::size_t len){
        const unsigned char* p = static_cast<const unsigned char*>(ptr);
        out.insert(out.end(), p, p + len);
    };
    append(&hdr.magic, sizeof(hdr.magic));
    append(&hdr.version, sizeof(hdr.version));
    append(&hdr.reserved, sizeof(hdr.reserved));
    append(&hdr.saltLen, sizeof(hdr.saltLen));
    append(&hdr.chunkSize, sizeof(hdr.chunkSize));
    append(&hdr.chunkCount, sizeof(hdr.chunkCount));
    append(&hdr.baseNonce, sizeof(hdr.baseNonce));

    return out;
}

// Deserializer to ensure we read data exactly how we wrote it
// This prevents struct padding issues.
void CryptoEngine::deserializeFixedHeader(const std::vector<unsigned char>& data, Header& hdr){
    if(data.size() < 36) throw std::runtime_error("Header too short");
    
    size_t offset = 0;
    auto readField = [&](void* ptr, std::size_t len){
        std::memcpy(ptr, data.data() + offset, len);
        offset += len;
    };

    readField(&hdr.magic, sizeof(hdr.magic));
    readField(&hdr.version, sizeof(hdr.version));
    readField(&hdr.reserved, sizeof(hdr.reserved));
    readField(&hdr.saltLen, sizeof(hdr.saltLen));
    readField(&hdr.chunkSize, sizeof(hdr.chunkSize));
    readField(&hdr.chunkCount, sizeof(hdr.chunkCount));
    readField(&hdr.baseNonce, sizeof(hdr.baseNonce));
}

void CryptoEngine::deriveChunkNonce(
    const unsigned char baseNonce[GCM_IV_SIZE],
    uint64_t i,
    unsigned char outNonce[GCM_IV_SIZE]
){
    // Pattern: first 4 bytes from baseNonce, last 8 bytes are counter i (little-endian).
    std::memcpy(outNonce, baseNonce, 4);
    // Write i as little-endian into bytes [4..11]
    for (int j = 0; j < 8; ++j){
        outNonce[4 + j] = static_cast<unsigned char>((i >> (8 * j)) & 0xFF);
    }
}


int CryptoEngine::writeHeader(
    std::ofstream& ofsObj,
    const std::vector<unsigned char>& salt,
    const Header& hdr,
    std::vector<unsigned char>& aadOut
){
    if (!ofsObj.is_open()) return 0;

    // Validating salt len
    if (salt.size() != hdr.saltLen){
        std::cerr << "Error: Salt length mismatch" << std::endl;
        return 0;
    }

    // Serliaize and write fixed header
    aadOut = serializeFixedHeader(hdr);

    ofsObj.write(reinterpret_cast<const char*>(aadOut.data()), static_cast<std::streamsize>(aadOut.size()));
    if (ofsObj.fail()){
        std::cerr << "Error: Failed to write fixed header." << std::endl;
        return 0;
    }

    // Write salt immediately after fixed header
    ofsObj.write(reinterpret_cast<const char*>(salt.data()), static_cast<std::streamsize>(salt.size()));
    if (ofsObj.fail()){
        std::cerr << "Error: Failed to write salt." << std::endl;
        return 0;
    }
    
    return 1;
}

int CryptoEngine::readHeader(
    std::ifstream& ifsObj,
    std::vector<unsigned char>& saltOut,
    Header& hdrOut,
    std::vector<unsigned char>& aadOut
){
    if (!ifsObj.is_open()) return 0;

    // Calculate the exact packed size of the fixed header
    // magic(4)+ver(1)+res(3)+saltLen(4)+chkSz(4)+chkCnt(8)+nonce(12) = 36 bytes
    const size_t PACKED_HEADER_SIZE = 36; 
    std::vector<unsigned char> headerBuffer(PACKED_HEADER_SIZE);

    // Read fixed-size header directly into buffer
    ifsObj.read(reinterpret_cast<char*>(headerBuffer.data()), static_cast<std::streamsize>(PACKED_HEADER_SIZE));
    
    if (ifsObj.gcount() != static_cast<std::streamsize>(PACKED_HEADER_SIZE) || ifsObj.fail()){
        std::cerr << "Error: Failed to read fixed header." << std::endl;
        return 0;
    }

    // Manually unpack (deserialize) into the struct
    try {
        deserializeFixedHeader(headerBuffer, hdrOut);
    } 
    catch (...) { 
        return 0; 
    }

    // Save this buffer as our AAD (Authenticated Associated Data)
    aadOut = headerBuffer;
    
    // Validation
    if (hdrOut.magic != MAGIC_NUMBER || hdrOut.version != ALGO_VERSION){
        std::cerr << "Error: Invalid magic/version." << std::endl;
        return 0;
    }
    else
    if (hdrOut.saltLen != KeyDeriver::SALT_SIZE){
        std::cerr << "Unexpected salt length." << std::endl;
        return 0;
    }
    else
    if (hdrOut.chunkSize == 0 || hdrOut.chunkSize > (1024u * 64u * 16u)){ // Max 16MB
        std::cerr << "Error: Invalid chunk size." << std::endl;
        return 0;
    }
    
    // Read Salt
    saltOut.resize(hdrOut.saltLen);
    
    ifsObj.read(reinterpret_cast<char*>(saltOut.data()), static_cast<std::streamsize>(saltOut.size()));
    if (ifsObj.fail() || ifsObj.gcount() != static_cast<std::streamsize>(saltOut.size())){
        std::cerr << "Error: Failed to read salt." << std::endl;
        return 0;
    }

    return 1;
}

// --- Encryption ---
int CryptoEngine::encryptStream(
    std::ifstream& ifsObj,
    std::ofstream& ofsObj,
    const std::string& passphrase,
    std::size_t chunkSize
){
    if (!ifsObj.is_open() || !ofsObj.is_open()) return 0;

    try{
        // Generating salt based on random inputs
        std::vector<unsigned char> salt = KeyDeriver::generateSalt();
        std::vector<unsigned char> key = KeyDeriver::deriveKey(passphrase, salt);

        // Prepare header
        Header hdr{};
        hdr.magic = MAGIC_NUMBER;
        hdr.version = ALGO_VERSION;
        std::memset(hdr.reserved, 0, sizeof(hdr.reserved));
        hdr.saltLen = static_cast<uint32_t>(salt.size());
        hdr.chunkSize = static_cast<uint32_t>(chunkSize);
        hdr.chunkCount = 0; // Optional, can be filled in later
        randombytes_buf(hdr.baseNonce, sizeof(hdr.baseNonce));

        // Write header (+salt) and capture AAD
        std::vector<unsigned char> aad;
        if (!writeHeader(ofsObj, salt, hdr, aad)) return 0;

        // Preparing the buffers for encrypting in chunks
        std::vector<unsigned char> plaintext_buff(chunkSize);
        std::vector<unsigned char> ciphertext_buf(chunkSize);
        std::vector<unsigned char> tag_buf(CHUNK_SIZE);

        unsigned long long ciphertext_len = 0;
        uint64_t chunk_index = 0;

        // --- Loop to process stream ---
        while (true){
            // Read next chunk
            ifsObj.read(reinterpret_cast<char*>(plaintext_buff.data()), static_cast<std::streamsize>(plaintext_buff.size()));
            std::streamsize bytes_read = ifsObj.gcount();

            if (bytes_read <= 0) break; // Nothing left to read, eof

            // Derive unique nonce for this chunk
            unsigned char nonce[GCM_IV_SIZE];
            deriveChunkNonce(hdr.baseNonce, chunk_index, nonce);

            // Encrypt our chunk using AES-256 GCM with AAD for fixed header bytes
            if (crypto_aead_aes256gcm_encrypt_detached(
                ciphertext_buf.data(), // Output buffer for ciphertext + tag
                tag_buf.data(), //Output buffer for auth tag
                &ciphertext_len,
                plaintext_buff.data(), // Input plaintext
                static_cast<unsigned long long>(bytes_read), // Length to encrypt
                aad.data(), static_cast<unsigned long long>(aad.size()), // No additional non-confidential data
                nullptr, // Ignored for detach mode
                nonce, // Input buffer for IV/nonce
                key.data() // Encryption key
            ) != 0){
                throw std::runtime_error("Encryption failed on a data chunk.");
            }

            // Writting ciphertext then tag
            ofsObj.write(reinterpret_cast<const char*>(ciphertext_buf.data()), static_cast<std::streamsize>(bytes_read));
            ofsObj.write(reinterpret_cast<const char*>(tag_buf.data()), static_cast<std::streamsize>(GCM_TAG_SIZE));
            
            if (ofsObj.fail()){
                throw std::runtime_error("Output file write error");
            }
            ++chunk_index;
        }
    }
    catch (std::exception& e){
        std::cerr << "Encryption Error " << e.what() << std::endl;
        return 0;
    }
    return 1;
}

// When reading from stream, can't have streams be constant
int CryptoEngine::decryptStream(
    std::ifstream& ifsObj,
    std::ofstream& ofsObj,
    const std::string& passphrase
){
    if (!ifsObj.is_open() || !ofsObj.is_open()) return 0;

    try{           
            // Read File header + Salt & capture AAD
            std::vector<unsigned char> salt;
            Header hdr{};
            std::vector<unsigned char> aad;
            if (!readHeader(ifsObj, salt, hdr, aad)) return 0;

            // Derive the key using the passphrase + file's salt
            std::vector<unsigned char> key = KeyDeriver::deriveKey(passphrase, salt);


            // Preparing the buffers for decrypting in chunks
            std::vector<unsigned char> ciphertext_buf(hdr.chunkSize);
            std::vector<unsigned char> plaintext_buf(hdr.chunkSize);
            std::vector<unsigned char> tag_buf(GCM_TAG_SIZE);

            uint64_t chunk_index = 0;

        // -- Steam Processing Loop until EOF ---
        while (true){ 
            // Attempt to read a full chunk of ciphertext
            ifsObj.read(reinterpret_cast<char*>(ciphertext_buf.data()), static_cast<std::streamsize>(ciphertext_buf.size()));
            std::streamsize cipher_bytes_read = ifsObj.gcount();
                
            // Nothing read; might be EOF; ensure we don't try to read a tag for an empty chunk
            if (cipher_bytes_read <= 0) break;
            if (ifsObj.eof()) {
                ifsObj.clear(); 
            }

            // Attempt to read the Tag
            ifsObj.read(reinterpret_cast<char*>(tag_buf.data()), static_cast<std::streamsize>(tag_buf.size()));
            std::streamsize tag_bytes_read = ifsObj.gcount();

            // Handle End-Of-File "Over-read"
            // If the file ends with [Small Chunk][Tag], step 1 might have read 
            // the chunk AND the tag into ciphertext_buf.
            
            if (tag_bytes_read < static_cast<std::streamsize>(GCM_TAG_SIZE)) {
                // If we didn't get a full tag, the tag is likely inside the ciphertext buffer.
                // This happens when the remaining file size < chunkSize + tagSize
                
                if (cipher_bytes_read > static_cast<std::streamsize>(GCM_TAG_SIZE)) {
                    // Recover tag from the end of ciphertext_buf
                    long actual_cipher_len = cipher_bytes_read - GCM_TAG_SIZE;
                    
                    // Copy the tail of ciphertext_buf into tag_buf
                    std::memcpy(tag_buf.data(), 
                                ciphertext_buf.data() + actual_cipher_len, 
                                GCM_TAG_SIZE);
                    
                    // Adjust ciphertext length
                    cipher_bytes_read = actual_cipher_len;
                } else {
                    // We don't have enough data for a tag + cipher. File is corrupt.
                    throw std::runtime_error("Unexpected EOF: Missing Auth Tag.");
                }
            }

            // Derive nonce for this chunk
            unsigned char nonce[GCM_IV_SIZE];
            deriveChunkNonce(hdr.baseNonce, chunk_index, nonce);

            // Decrypt this chunk with same AAD
            if (crypto_aead_aes256gcm_decrypt_detached(
                plaintext_buf.data(),
                nullptr,
                ciphertext_buf.data(),
                static_cast<unsigned long long>(cipher_bytes_read),
                tag_buf.data(),
                aad.data(), 
                static_cast<unsigned long long>(aad.size()),
                nonce,
                key.data()
            ) != 0){
                 throw std::runtime_error("Decryption failed. Authentication Tag verification failed.");   
            }

            // Write plainext 
            ofsObj.write(reinterpret_cast<const char*>(plaintext_buf.data()), static_cast<std::streamsize>(cipher_bytes_read));
            if (ofsObj.fail()) {
                throw std::runtime_error("Output file write error.");
            }

            ++chunk_index;

            // If hdr.chunkCount > 0, you can stop after that many chunks and ignore trailing bytes.
            if (hdr.chunkCount > 0 && chunk_index >= hdr.chunkCount) {
                break;
            }
        } 
    }
    catch(const std::exception& e){
        std::cerr << "Decryption Error: " << e.what() << std::endl;
        return 0;                
    }  
    return 1;
}