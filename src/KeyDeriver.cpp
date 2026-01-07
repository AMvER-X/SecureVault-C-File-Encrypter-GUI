/*
Implementation for KeyDriver.h, KDP logic takes place here.
*/

#include "KeyDeriver.h"

std::vector<unsigned char> KeyDeriver::generateSalt(){
    // Decare vector of size salt
    std::vector<unsigned char> salt(SALT_SIZE);

    // Fill vector with cryptographically secure bytes
    randombytes_buf(salt.data(), SALT_SIZE);

    return salt;
}

std::vector<unsigned char> KeyDeriver::deriveKey(
    const std::string& passphrase,
    const std::vector<unsigned char>& salt
    ){
        if (salt.size() != SALT_SIZE){
            throw std::runtime_error("KeyDeriver: Invalid salt size provided.");
        }   
        
        std::vector<unsigned char> key(KEY_SIZE);

        // Calling libsodiums Argon2id password hashing function
        if (crypto_pwhash(
            key.data(), key.size(), // Where we want our output buffer to go (our key) + Size of key buffer  
            passphrase.c_str(), passphrase.length(), // Password + length (Lib works in const char*, so we need to pass a ptr to c style string using c_str())
            salt.data(), // Input salt data (16-bytes)
            crypto_pwhash_OPSLIMIT_MODERATE, // Time/CPU cost set to moderate
            crypto_pwhash_MEMLIMIT_MODERATE, // Memory cost set to moderate
            crypto_pwhash_ALG_DEFAULT // Current default is Argon2id
        ) != 0){
            // Has failed (0 == success), system error
            throw std::runtime_error("KeyDeriver: Key Derivation failed (Argon2id engine error).");
        }

        return key;
    }