#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleNewFile(const QString &path);
    void removeSelectedFile(const QString path);
    void showContextMenu(const QPoint &pos);
    void on_startButton_clicked();
    
    void progressUpdated(int percentage);
    void statusMessage(const QString& msg);
    void fileCompleted(const QString& filePath);
    void errorOccured(const QString& filePath, const QString& errorMessage);
    void finished();
    
private:
    Ui::MainWindow *ui;
    QStringList m_fileQueue; // Raw data
    QStringListModel* m_queueModel; // Bridge to QListView
    bool passwordsMatch() const;
    void encryptButtonLogic();
};
#endif // MAINWINDOW_H
