/*
Implementation for file encryption. 
*/
#include "FileManager.h"
#include "CryptoEngine.h"
#include <iostream>
#include <fstream>
#include <QFileInfo>
#include <QDir>

int FileManager::encryptFile(
    const std::string& inputPath,
    const std::string& outputPath,
    const std::string& passphrase
){
    // Open streams in binary mode (std::ios::binary = correct byte-level I/O)
    std::ifstream ifsObj(inputPath, std::ios::binary);
    std::ofstream ofsObj(outputPath, std::ios::binary | std::ios::trunc);

    // Check stream status
    if (!ifsObj.is_open()){
        std::cerr << "Error: Could not open input file for reading: " << inputPath << std::endl;
        return 0;
    }

    if (!ofsObj.is_open()){
        std::cerr << "Error: Could not open output file for writting" << outputPath << std::endl;
        return 0;
    }

    // Delegation of stream to CryptoEngine
    CryptoEngine engine;
    if (!engine.encryptStream(ifsObj, ofsObj, passphrase)) {
        std::cerr << "Encryption failed." << std::endl;
        return 0;
    }
    ofsObj.flush();
    ofsObj.close();
    ifsObj.close();

    return 1;
}

int FileManager::decryptFile(
    const std::string& inputPath,
    const std::string& outputPath,
    const std::string& passphrase
){
    // Open streams in binary mode (std::ios::binary = correct byte-level I/O)
    std::ifstream ifsObj(inputPath, std::ios::binary);
    std::ofstream ofsObj(outputPath, std::ios::binary | std::ios::trunc);

    // Check stream status
    if (!ifsObj.is_open()){
        std::cerr << "Error: Could not open input file for reading: " << inputPath << std::endl;
        return 0;
    }

    if (!ofsObj.is_open()){
        std::cerr << "Error: Could not open output file for writting" << outputPath << std::endl;
        return 0;
    }

    CryptoEngine engine;
        if (!engine.decryptStream(ifsObj, ofsObj, passphrase)) {
        std::cerr << "Decryption failed." << std::endl;
        return 0;
    }
    ofsObj.flush();
    ofsObj.close();
    ifsObj.close();

    return 1;

}

std::vector<unsigned char> FileManager::hashFile(const std::string& path){
    std::ifstream ifsObj(path, std::ios::binary);

    if (!ifsObj.is_open()){
        std::cerr << "Error: Could not open file stream for hashing" << std::endl;
        return {};
    }

    // Generate state using libsodium data types
    crypto_generichash_state state;
    crypto_generichash_init(&state, nullptr, 0, crypto_generichash_BYTES);

    std::vector<char> buffer(1024 * 64); //64 KB buffer
    while (ifsObj.read(buffer.data(), buffer.size())){
        crypto_generichash_update(&state, reinterpret_cast<const unsigned char*>(buffer.data()), ifsObj.gcount());
    }
    crypto_generichash_update(&state, reinterpret_cast<const unsigned char*>(buffer.data()), ifsObj.gcount());

    std::vector<unsigned char> hash(crypto_generichash_BYTES);
    crypto_generichash_final(&state, hash.data(), hash.size());

    return hash;
}

void FileManager::printHash(const std::vector<unsigned char>& hash, const std::string& label){
    std::cout << label << ": ";
    for (unsigned char byte : hash) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    std::cout << std::dec << std::endl;
}