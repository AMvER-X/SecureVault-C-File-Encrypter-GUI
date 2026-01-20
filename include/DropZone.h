#ifndef DROP_ZONE_H
#define DROP_ZONE_H

#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

class DropZone : public QLabel{
    Q_OBJECT
public: // Explicit constructor preventing implicit conversions
    explicit DropZone(QWidget *parent = nullptr);
    
    signals:
        void fileDropped(const QString &path);
    
    protected:
        void dragEnterEvent(QDragEnterEvent *event) override;

        /*
        Handle the drop event when a file is dropped onto the widget.
        Validates the file and emits the fileDropped signal if valid.
        */
        void dropEvent(QDropEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
};

#endif // DROP_ZONE_H