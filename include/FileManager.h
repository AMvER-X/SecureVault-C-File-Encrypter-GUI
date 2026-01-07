/*
Facilitate the stream-based methods of the CryptoEngine by managing file paths, 
opening/closing streams, and basic error checking.
*/
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

class FileManager{
    public:
    /*
    Opens input and output files + delegates stream encryption.
    Handles file path validation, opening binary streams, and delegates the
    core cryptographic work to the CryptoEngine.
    Param inputPath: Path to the plaintext file to be encrypted
    Param outPut file: Path to where the encrypted file will be saved.
    Param passPhrase: Users password
    Returns 1 if file operations + encryption succeed, 0 if failure
    */
    int encryptFile(
        const std::string& inputPath,
        const std::string& outputPath,
        const std::string& passphrase
    );

    /*
    Opens input and output files + delegates stream decryption.
    Handles file path validation, opening binary streams, and delegates the
    core cryptographic work to the CryptoEngine.
    Param inputPath: Path to the ciphertext file to be decrypted
    Param outPut file: Path to where the decrypted file will be saved.
    Param passPhrase: Users password
    Returns 1 if file operations + decryption succeed, 0 if failure
    */
    int decryptFile(
        const std::string& inputPath,
        const std::string& outputPath,
        const std::string& passphrase
    );

    // --- Helper Function: Hash File for Integrity Check ---
    std::vector<unsigned char> hashFile(const std::string& path);

    // Used to print hash of file to console
    void printHash(const std::vector<unsigned char>& hash, const std::string& label);

};

#endif // FILE_MANAGER_H