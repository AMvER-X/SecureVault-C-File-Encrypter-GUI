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
    return a.exec();
}