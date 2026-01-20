#include "EncryptionWorker.h"
#include "CryptoEngine.h"
#include <QFileInfo>
#include <iostream>
#include <QDir>

EncryptionWorker::EncryptionWorker(const QStringList& filePaths, const QString& password, QObject *parent)
    : m_files(filePaths), m_password(password), QObject(parent) {}

    void EncryptionWorker::process(QString& outputPath){
    FileManager fm;
    std::cout << "Starting Encryption process" << std::endl;

        for (int i = 0; i < m_files.size(); i++){
            QString filePath = m_files.at(i);
            QFileInfo fileInfo(filePath);
            QString fileName = fileInfo.fileName();
            QString targetFileOutPath;

            emit statusMessage(QString("Processing: %1").arg(fileInfo.fileName()));

            int success = false;
            try{
                std::cout << "File enc status start " << std::endl;
                bool isAlreadyEncrypted = isEncryptedByUs(filePath.toStdString());

                if (!isAlreadyEncrypted){
                    QString outName = fileName + ".encr";
                    targetFileOutPath = QDir(outputPath).filePath(outName);

                    success = fm.encryptFile(filePath.toStdString(), targetFileOutPath.toStdString(), m_password.toStdString());
                    std::cout << "Encrypting file" << std::endl;
                }
                else{
                    QString outName = fileName;
                    if (outName.endsWith(".encr")){
                        outName.chop(5); // removes ".encr"
                    }
                    else{
                        outName = "decrypted_" + outName; 
                    }

                    targetFileOutPath = QDir(outputPath).filePath(outName);

                    success = fm.decryptFile(filePath.toStdString(), targetFileOutPath.toStdString(), m_password.toStdString());
                    std::cout << "Decrypting file" << std::endl;
                }
            }
            catch(...){
                success = 0;
            }

            if (!success){
                emit errorOccured(fileInfo.fileName(), "Cipher operation failed.");
            }
            else{
                emit fileCompleted(filePath);
            }

            // Calculate progress
            int progress = static_cast<int>(static_cast<double>(i + 1) / m_files.size() * 100);
            emit progressUpdated(progress);
        }

        emit statusMessage("Task Completed.");
        emit finished();
        std::cout << "Done" << std::endl;
    }

    bool EncryptionWorker::isEncryptedByUs(const std::string &filePath){
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) return 0;

        uint32_t fileMagic = 0;
        // read first 4 bytes
        file.read(reinterpret_cast<char*>(&fileMagic), sizeof(fileMagic));

        if (file.gcount() < static_cast<std::streamsize>(sizeof(fileMagic))) {
            return 0; 
        }

        return (fileMagic == CryptoEngine::MAGIC_NUMBER) ? 1 : 0;
    }