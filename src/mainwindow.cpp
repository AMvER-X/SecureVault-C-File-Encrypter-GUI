#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AlgoEnum.h"
#include "DropZone.h"
#include "EncryptionWorker.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QString>
#include <QShortcut>
#include <QKeySequence>
#include <QThread>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DropZone* customDropZone = new DropZone(this);

    // Initialise the model for the file queue
    m_queueModel = new QStringListModel(this);

    // Connect the model to the QListView
    ui->fileListView->setModel(m_queueModel);

    customDropZone->setText("☁ Click or Drag and Drop File Here");
    customDropZone->setAlignment(Qt::AlignCenter);
    customDropZone->setMinimumHeight(200);
    customDropZone->setStyleSheet(
        " QLabel {"
        " border: 2px dashed #555;"
        " border-radius: 10px;"
        " background-color: white;"
        " color: #888;"
        " font-weight: bold;"
        "}"
        " QLabel:hover {"
        " background-color: #232020ff;" 
        " border-color: #888;"
        "}"
    );

    ui->verticalLayout_4->replaceWidget(ui->fileUploadLabel, customDropZone);
    ui->fileUploadLabel->deleteLater();
    ui->fileUploadLabel = customDropZone;
    connect(customDropZone, &DropZone::fileDropped, this, &MainWindow::handleNewFile);

    // Popiulating combo boxes with options
    ui->encComboBox->addItem("AES-256-GCM", static_cast<int>(CryptoAlgo::AES_256_GCM));
    ui->encComboBox->addItem("RSA", static_cast<int>(CryptoAlgo::RSA));
    ui->encComboBox->addItem("ECC", static_cast<int>(CryptoAlgo::ECC));    
    ui->encComboBox->addItem("Diffie-Hellman", static_cast<int>(CryptoAlgo::DIFFIE_HELLMAN));    

    ui->hashComboBox->addItem("BLAKE2b", static_cast<int>(CryptoAlgo::BLAKE2B));
    ui->hashComboBox->addItem("SHA-256", static_cast<int>(CryptoAlgo::SHA_256));
    ui->hashComboBox->addItem("SHA-512", static_cast<int>(CryptoAlgo::SHA_512));

    // Enabling context menu for file list view
    ui->fileListView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->fileListView, &QListView::customContextMenuRequested, this, &MainWindow::showContextMenu);


    // Enabling delete key to remove selected file
    QShortcut *deleteShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->fileListView);
    connect(deleteShortcut, &QShortcut::activated, [this](){
        QModelIndex index = ui->fileListView->currentIndex();
        if (index.isValid()){
            removeSelectedFile(m_fileQueue.at(index.row()));
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleNewFile(const QString &path){
    // Check if directory
    QFileInfo fileInfo(path);

    // validation
    if (!fileInfo.exists()){
        QMessageBox::critical(this, "File Error", "The file does not exist.");
        return;
    }

    if (!fileInfo.isFile() || fileInfo.isDir()){
        QMessageBox::critical(this, "Security Error", "The selected path is a directory/ folder. Please select a file.");
        return;
    }

    // Check for duplicates
    if (m_fileQueue.contains(path)){
        QMessageBox::information(this, "Duplicate File", "The selected file is already in the queue.");
        return;
    }

    
    // Add to queue
    m_fileQueue.append(path);
    
    
    // Update the model QListView
    m_queueModel->setStringList(m_fileQueue);
    
    progressUpdated(0);
    ui->statusLabel->setText(QString("Files: %1").arg(m_fileQueue.size()));

}

bool MainWindow::passwordsMatch() const{
    QString pwd1 = ui->passwordLineEdit->text();
    QString pwd2 = ui->passwordRepeatLineEdit->text(); 

    if (pwd1 != pwd2){
        QMessageBox::warning(const_cast<MainWindow*>(this), "Password Mismatch", "The passwords entered do not match. Please re-enter.");
        return false;
    }
    return true;
}

void MainWindow::on_startButton_clicked(){
    encryptButtonLogic();
}

void MainWindow::encryptButtonLogic(){
    if (m_fileQueue.isEmpty()) {
        QMessageBox::warning(const_cast<MainWindow*>(this), "No Files", "No file's have been selected to encrypt.");
        return;
    }
    if (!passwordsMatch()){
        QMessageBox::warning(const_cast<MainWindow*>(this), "No Files", "No file's have been selected to encrypt.");
        return;
    }

    // Check where user wants to save file to
    QString outPath = QFileDialog::getExistingDirectory(
        this,
        tr("Select Output Directory"),
        "/home",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    // Cancelled?
    if (outPath.isEmpty()){
        return;
    }

    // Create thread and worker
    QThread *thread = new QThread;
    EncryptionWorker* worker = new EncryptionWorker(m_fileQueue, ui->passwordLineEdit->text());
    worker->moveToThread(thread);

    // Connect Signals to slots
    connect(worker, &EncryptionWorker::progressUpdated, this, &MainWindow::progressUpdated);
    connect(worker, &EncryptionWorker::statusMessage, this, &MainWindow::statusMessage);
    connect(worker, &EncryptionWorker::fileCompleted, this, &MainWindow::fileCompleted);
    connect(worker, &EncryptionWorker::errorOccured, this, &MainWindow::errorOccured);
    connect(worker, &EncryptionWorker::finished, this, &MainWindow::finished);

    // Start the 'process' function upon start
    connect(thread, &QThread::started, [worker, outPath]() mutable {
        worker->process(outPath);
    });

    // Kill thread upon completion
    connect(worker, &EncryptionWorker::finished, thread, &QThread::quit);

    // Clear memory
    connect(worker, &EncryptionWorker::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    // do da stuff 
    ui->startButton->setEnabled(false);
    thread->start();
}

void MainWindow::progressUpdated(int percentage){
    ui->progressBar->setValue(percentage);
}

void MainWindow::statusMessage(const QString& msg){
    ui->statusLabel->setText(msg);
}

void MainWindow::fileCompleted(const QString& filePath){
    qDebug() << "Successfully processed:" << filePath;
}

void MainWindow::errorOccured(const QString& filePath, const QString& errorMessage){
    QMessageBox::critical(this, "Encryption Error",
    QString("File: %1\nError: %2").arg(filePath, errorMessage));
}

void MainWindow::finished(){
    statusMessage("Status: All Operations Complete.");
    progressUpdated(100);

    ui->startButton->setEnabled(true);

    ui->passwordLineEdit->clear();
    ui->passwordRepeatLineEdit->clear();

    QMessageBox::information(this, "Success", "The queue has been processed.");
}

void MainWindow::removeSelectedFile(const QString path){
    // Remove from queue
    m_fileQueue.removeAll(path);
    // Update the model QListView
    m_queueModel->setStringList(m_fileQueue);

    // Update status
    ui->statusLabel->setText(QString("Files: %1").arg(m_fileQueue.size()));

    if (m_fileQueue.isEmpty()){
        progressUpdated(0);
    }
}

void MainWindow::showContextMenu(const QPoint &pos){
    // Did user click on a valid item?
    QModelIndex index = ui->fileListView->indexAt(pos);
    if (!index.isValid()){
        return; // No valid item at this position
    }

    QMenu menu(this);
    QAction *removeAction = menu.addAction("❌ Remove Selected File");
    // Execute menu at cursor position
    QAction *selectedAction = menu.exec(ui->fileListView->viewport()->mapToGlobal(pos));

    if (selectedAction == removeAction){
        QString pathToRemove = m_fileQueue.at(index.row());
        removeSelectedFile(pathToRemove);
    }

}
