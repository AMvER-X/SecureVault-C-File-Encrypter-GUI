/*
KeyDriver, responsible for generating encryption keys from user passwords
*/
#ifndef KEY_DERIVER_H
#define KEY_DERIVER_H

#include <string>
#include <sodium.h>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <iostream>

class KeyDeriver {
    public:
        // Defininf the required AES-256 key sizes (32 bytes) - using libsodium constants
        static constexpr size_t KEY_SIZE = crypto_secretbox_KEYBYTES;
        // Argon2 salt size (16 bytes)
        static constexpr size_t SALT_SIZE = crypto_pwhash_SALTBYTES;

        /*
        Generates a cryptographically random salt required for Argon2
        Returns a vector contaiing the 16 byte random salt
        */
        static std::vector<unsigned char> generateSalt();
        
        /*
        Derives a secure key from a user's passphrase and unique salt using Argon2id
        Param 1: The user's input string (password)
        Param 2: The unique, 16-byte salt for key derivation
        Returns a vetor containing the derived 32-byte encryption key
        Throws std::runtime_error if the key generation fails or the salt is the wrong size
        */
        static std::vector<unsigned char> deriveKey(
            const std::string& passphrase,
            const std::vector<unsigned char>& salt
        );
};

#endif // KEY_DERIVER_H