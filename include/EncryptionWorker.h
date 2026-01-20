#ifndef ENCRYPTION_WORKER_H
#define ENCRYPTION_WORKER_H

#include <QObject>
#include <QString>
#include "FileManager.h"
#include <QStringList>
#include <string>
#include <fstream>


class EncryptionWorker : public QObject
{
    Q_OBJECT
public:
    explicit EncryptionWorker(const QStringList& filePaths, const QString& password, QObject *parent = nullptr);

    public slots:
        void process(QString& outputPath);

    signals:
        void progressUpdated(int percentage);
        void statusMessage(const QString& msg);
        void fileCompleted(const QString& filePath);
        void errorOccured(const QString& filePath, const QString& errorMessage);
        void finished();

    private:
    bool isEncryptedByUs(const std::string &filePath);

    QStringList m_files;
    QString m_password;
};

#endif // ENCRYPTION_WORKER_H