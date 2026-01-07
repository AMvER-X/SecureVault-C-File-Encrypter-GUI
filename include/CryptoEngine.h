/*
This is the Crypto Engine which contains the core logic for implementing our encryption on our files/ data
*/
#ifndef CRYPTO_ENGINE_H
#define CRYPTO_ENGINE_H

#include <string>
#include <vector> //TODO- FIX COMMENTS DESCRIBING FUNCTIONS
#include <fstream>
#include <stdint.h>
#include <sodium.h>
#include <iomanip>

// Forward decleration 
class KeyDeriver;

class CryptoEngine{
    public:
    // --- File header constraints ---
    // These variables are for the metadata that each encrypted file must have
    // Needed for integrity and security checks.

    // Unique identifier for the file format.
    static constexpr uint32_t MAGIC_NUMBER = 0x454E4352; // 'ENCR'

    // Algorithim version flag - AES-256 GCM + Argon2
    static constexpr uint8_t ALGO_VERSION = 0x01;

    // Nonce size for AES-256 GCM (GCM for counter mode and parralel encryption) - 12-bytes
    static constexpr size_t GCM_IV_SIZE = crypto_aead_aes256gcm_NPUBBYTES;

    // Authentication tag size for GCM (16 bytes)
    static constexpr size_t GCM_TAG_SIZE = crypto_aead_aes256gcm_ABYTES;

    // Chunk size for file streaming (64 KB) - Efficient I/O
    static constexpr size_t CHUNK_SIZE = 1024 * 64;

    // --- Header layout ---
    // Header fields are written in this order and used as AAD for each chunk.
    struct Header {
        uint32_t magic;                     // MAGIC_NUMBER
        uint8_t version;                    // ALGO_VERSION
        uint8_t reserved[3];                // padding to align to 8 bytes (future use)
        uint32_t saltLen;                   // length of salt 16-bytes
        uint32_t chunkSize;                 // chosen chunk size
        uint64_t chunkCount;                // optional; 0 means "infer until EOF"
        unsigned char baseNonce[GCM_IV_SIZE]; // random 12-byte based nonce
    };

    // --- Public Symmetric Encryption Methods ---

    /*
    Encrypts data from an input stream to an output stream.
    Param ifsObj: Plaintext data to be encrypted.
    Param ofsObj: Output stream where cyphertext and header is written to.
    Param passphrase: User provided password for key derivation.
    Returns 1 on cryptographic success, 0 on failure.
    */
    int encryptStream(
        std::ifstream& ifsObj,
        std::ofstream& ofsObj,
        const std::string& passphrase,
        std::size_t chunkSize = CHUNK_SIZE
    );

    /*
    Decrypts data from an input stream to an output stream.
    Param ifsObj: Stream containing cyphertext data and header.
    Param ofsObj: Output stream where plaintext is written to.
    Param passphrase: User provided password for key derivation.
    Returns 1 on cryptographic success, 0 on failure.
    */
    int decryptStream(
        std::ifstream& ifsObj,
        std::ofstream& ofsObj,
        const std::string& passphrase
    );

    private:
    // --- Internal I/O Helper Methods (Binary structure) ---

    /*
    Used to write the header information to the file, important for encryption.
    Param ifsObj: Stream containing the file to save the header added to it.
    Param salt: Derived salt to be added to file.
    */
    int writeHeader(
        std::ofstream& ofsObj,
        const std::vector<unsigned char>& salt,
        const Header& hdr,
        std::vector<unsigned char>& aadOut // serialized fixed header (without salt), used as AAD
    ); 

    /*
    Used to read the header information to the file, important for decryption.
    Param ifsObj: Stream containing the file to read the header info from.
    Param salt: Derived salt to be read to file.
    Param iv: Derived iv to be read to the file.
    */
    int readHeader(
        std::ifstream& ifsObj,
        std::vector<unsigned char>& saltOut,
        Header& hdrOut,
        std::vector<unsigned char>& aadOut
    );

    // Serliaze the fixed-size portion of header (without salt) to bytes for AAD
    static std::vector<unsigned char> serializeFixedHeader(const Header& hdr);

    void deserializeFixedHeader(const std::vector<unsigned char>& data, Header& hdr);

    // Derive a per-chunk nonce from a baseNonce and a 64-bit little-endian counter i.
    // Ensures unique nonce per chunk: last 8 bytes are the counter; first 4 are copied from the baseNonce.
    static void deriveChunkNonce(
        const unsigned char baseNonce[GCM_IV_SIZE],
        uint64_t i,
        unsigned char outNonce[GCM_IV_SIZE]
    );

    /*
    Compute total bytes for one chunk record in the file:
    ciphertext_len <= chunk size + tag_len 
    Useful for parsing/decrypting
    */ 
    static constexpr std::size_t recordOverhead(){
        return GCM_TAG_SIZE;
    }
};

#endif // CRYPTO_HEADER_H