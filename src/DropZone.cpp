#include "DropZone.h"
#include <QFileInfo>
#include <QFileDialog>

DropZone::DropZone(QWidget *parent) : QLabel(parent){
    setAcceptDrops(true);
}

void DropZone::dropEvent(QDropEvent *event){
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls()){
        QString path = mimeData->urls().at(0).toLocalFile();

        QFileInfo fileInfo(path);

        if (!fileInfo.exists()) return;
        if (!fileInfo.isFile()) return; // Block folders/ directories
        if (!fileInfo.isReadable()) return; // Has read permissions

        emit fileDropped(path); // Sends validated path to controller
    }
}

void DropZone::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
}

void DropZone::mousePressEvent(QMouseEvent *event){
    // Makes label act like a button to open file dialog when clicked
    Q_UNUSED(event);
    QString path = QFileDialog::getOpenFileName(this, "Select File to Upload");
    if (!path.isEmpty()) emit fileDropped(path);
}