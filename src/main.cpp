/*
Main program file
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sodium.h>
#include "KeyDeriver.h"
#include "ErrorEnum.h"
#include "FileManager.h"

#include "mainwindow.h"
#include <QApplication>


// --- Main Testing Logic ---
int main(int argc, char* argv[]){

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // Initialise libsodium
    if (sodium_init() < 0){
        std::cerr << "Fatal Error: libsodium initialisation failed." << std::endl;
        return libsodiumFail;
    }
    FileManager fm;

    const std::string INPUT_FILE = "test_input.txt";
    const std::string ENCRYPTED_FILE = "encrypted.encr";
    const std::string DECRYPTED_FILE = "decrypted_output.txt";
    const std::string PASSWORD = "MyStrongPassword123";

    // Dummy input file for testing
    std::cout << "--- 1. PREP: Creating Test File ---" << std::endl;
    std::ofstream testOfsObj(INPUT_FILE);

    if (!testOfsObj.is_open()){
        std::cerr << "Error: Could not create test input file" << std::endl;
        return fileError;
    }

    for (int i = 0; i < 10000; ++i){
        testOfsObj << "Line " << i << ": This is a chunk of test data for streaming encryption verification.\n";
    }
    testOfsObj.close();

    // Calculate original hash
    std::vector<unsigned char> originalHash = fm.hashFile(INPUT_FILE);
    fm.printHash(originalHash, "Original File Hash");
    std::cout << std::endl;

    // --- Encryption Test ---
    std::cout << "--- 2. ENCRYPTING FILE ---" << std::endl;
    if (fm.encryptFile(INPUT_FILE, ENCRYPTED_FILE, PASSWORD)){
        std::cout << "✅ ENCRYPTION SUCCESS: " << INPUT_FILE << " -> " << ENCRYPTED_FILE << std::endl;
    }
    else {
        std::cerr << "❌ ENCRYPTION FAILED. Terminating." << std::endl;
        return encryptionError;
    }
    std::cout << std::endl;

    // --- Decryption Test ---
    std::cout << "--- 3. DECRYPTING FILE (CORRECT PASSWORD) ---" << std::endl;
    if (fm.decryptFile(ENCRYPTED_FILE, DECRYPTED_FILE, PASSWORD)){
        std::cout << "✅ DECRYPTION SUCCESS: " << ENCRYPTED_FILE << " -> " << DECRYPTED_FILE << std::endl;
    } 
    else {
        std::cerr << "❌ DECRYPTION FAILED (Correct Password). This is a critical failure." << std::endl;
        return decryptionError;
    }
    std::cout << std::endl;

    // --- Integrity Check ---
    std::cout << "--- 4. INTEGRITY CHECK ---" << std::endl;
    std::vector<unsigned char> decryptedHash = fm.hashFile(DECRYPTED_FILE);
    fm.printHash(decryptedHash, "Decrypted File Hash");

    if (originalHash == decryptedHash){
        std::cout << "\n\n🚀 FINAL RESULT: BULLETPROOF! Original and Decrypted file hashes MATCH." << std::endl;
        // Clean up test files
        std::remove(INPUT_FILE.c_str());
        std::remove(ENCRYPTED_FILE.c_str());
        std::remove(DECRYPTED_FILE.c_str());
        std::cout << "Cleaned up test files." << std::endl;
    }
    else{
        std::cerr << "\n\n❌ FINAL RESULT: CRITICAL FAILURE! File hashes DO NOT MATCH. STREAMING OR CRYPTO LOGIC IS BROKEN." << std::endl;
        return integrityError;
    }
    std::cout << std::endl;

    // --- FAILURE MODE TEST (INCORRECT PASSWORD) ---
    std::cout << "--- 5. FAILURE MODE TEST (WRONG PASSWORD) ---" << std::endl;
    if (fm.decryptFile(ENCRYPTED_FILE, "fail_test.txt", "WrongPassword456")){
        std::cerr << "❌ FAILURE TEST FAILED: Decryption succeeded with the WRONG password. FATAL SECURITY FLAW." << std::endl;
        return decryptionError;
    }
    else{
        std::cout << "✅ FAILURE TEST SUCCESS: Decryption failed (as expected) with wrong password. Authentication Tag rejected the input." << std::endl;
    }

    return a.exec();
}