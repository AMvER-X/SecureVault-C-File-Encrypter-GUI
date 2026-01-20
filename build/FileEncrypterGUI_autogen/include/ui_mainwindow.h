/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QFrame *EncryptionFrame;
    QVBoxLayout *verticalLayout_3;
    QFrame *encSettingFrame;
    QLabel *encLabel;
    QFrame *methodFrame;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *methodLabel;
    QComboBox *encComboBox;
    QComboBox *hashComboBox;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *passwordLabelRepeat;
    QLineEdit *passwordRepeatLineEdit;
    QSpacerItem *verticalSpacer;
    QPushButton *startButton;
    QFrame *FileFrame;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *fileUploadLabel;
    QLabel *fileQueueLabel;
    QListView *fileListView;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("/* The Main Background */\n"
"QMainWindow { background-color: #1e1e1e; }\n"
"\n"
"/* The Sidebar */\n"
"#sidebarFrame {\n"
"    background-color: #252525;\n"
"    border-right: 1px solid #333;\n"
"}\n"
"\n"
"/* The Glowing Start Button */\n"
"QPushButton#btnStart {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"    padding: 10px;\n"
"}\n"
"QPushButton#btnStart:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"/* The File List */\n"
"QListWidget {\n"
"    background-color: #2d2d2d;\n"
"    border: 1px solid #3d3d3d;\n"
"    color: #e0e0e0;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(30, 30, 30, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        QBrush brush2(QColor(45, 45, 45, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush2);
        QBrush brush3(QColor(37, 37, 37, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush3);
        QBrush brush4(QColor(15, 15, 15, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Dark, brush4);
        QBrush brush5(QColor(20, 20, 20, 255));
        brush5.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush6);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Shadow, brush6);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipBase, brush7);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipText, brush6);
        QBrush brush8(QColor(255, 255, 255, 127));
        brush8.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Accent, brush6);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush3);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Dark, brush4);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush6);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Shadow, brush6);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::AlternateBase, brush4);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipBase, brush7);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Accent, brush6);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush2);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush3);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Dark, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Mid, brush5);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush4);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Shadow, brush6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::AlternateBase, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipBase, brush7);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipText, brush6);
        QBrush brush9(QColor(15, 15, 15, 127));
        brush9.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush9);
#endif
        QBrush brush10(QColor(21, 21, 21, 255));
        brush10.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Accent, brush10);
#endif
        centralwidget->setPalette(palette);
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        EncryptionFrame = new QFrame(centralwidget);
        EncryptionFrame->setObjectName("EncryptionFrame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EncryptionFrame->sizePolicy().hasHeightForWidth());
        EncryptionFrame->setSizePolicy(sizePolicy);
        EncryptionFrame->setMinimumSize(QSize(250, 0));
        EncryptionFrame->setMaximumSize(QSize(300, 16777215));
        EncryptionFrame->setFrameShape(QFrame::Shape::StyledPanel);
        EncryptionFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(EncryptionFrame);
        verticalLayout_3->setObjectName("verticalLayout_3");
        encSettingFrame = new QFrame(EncryptionFrame);
        encSettingFrame->setObjectName("encSettingFrame");
        sizePolicy.setHeightForWidth(encSettingFrame->sizePolicy().hasHeightForWidth());
        encSettingFrame->setSizePolicy(sizePolicy);
        encSettingFrame->setMinimumSize(QSize(230, 0));
        encSettingFrame->setMaximumSize(QSize(280, 16777215));
        encSettingFrame->setAutoFillBackground(false);
        encSettingFrame->setStyleSheet(QString::fromUtf8("EncSettFrame { background-colour: #414141}"));
        encSettingFrame->setFrameShape(QFrame::Shape::StyledPanel);
        encSettingFrame->setFrameShadow(QFrame::Shadow::Raised);
        encLabel = new QLabel(encSettingFrame);
        encLabel->setObjectName("encLabel");
        encLabel->setGeometry(QRect(10, 10, 250, 30));
        encLabel->setMinimumSize(QSize(240, 30));
        encLabel->setMaximumSize(QSize(250, 900));
        QPalette palette1;
        encLabel->setPalette(palette1);

        verticalLayout_3->addWidget(encSettingFrame);

        methodFrame = new QFrame(EncryptionFrame);
        methodFrame->setObjectName("methodFrame");
        sizePolicy.setHeightForWidth(methodFrame->sizePolicy().hasHeightForWidth());
        methodFrame->setSizePolicy(sizePolicy);
        methodFrame->setMinimumSize(QSize(230, 0));
        methodFrame->setMaximumSize(QSize(280, 400));
        methodFrame->setFrameShape(QFrame::Shape::StyledPanel);
        methodFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(methodFrame);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        methodLabel = new QLabel(methodFrame);
        methodLabel->setObjectName("methodLabel");
        methodLabel->setMinimumSize(QSize(200, 20));
        methodLabel->setMaximumSize(QSize(250, 16777215));

        verticalLayout_2->addWidget(methodLabel);

        encComboBox = new QComboBox(methodFrame);
        encComboBox->setObjectName("encComboBox");
        encComboBox->setMinimumSize(QSize(200, 0));
        encComboBox->setMaximumSize(QSize(265, 16777215));

        verticalLayout_2->addWidget(encComboBox);

        hashComboBox = new QComboBox(methodFrame);
        hashComboBox->setObjectName("hashComboBox");
        hashComboBox->setMinimumSize(QSize(200, 0));
        hashComboBox->setMaximumSize(QSize(265, 16777215));

        verticalLayout_2->addWidget(hashComboBox);

        passwordLabel = new QLabel(methodFrame);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setMinimumSize(QSize(200, 0));
        passwordLabel->setMaximumSize(QSize(250, 16777215));

        verticalLayout_2->addWidget(passwordLabel);

        passwordLineEdit = new QLineEdit(methodFrame);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setMinimumSize(QSize(200, 0));
        passwordLineEdit->setMaximumSize(QSize(265, 16777215));

        verticalLayout_2->addWidget(passwordLineEdit);

        passwordLabelRepeat = new QLabel(methodFrame);
        passwordLabelRepeat->setObjectName("passwordLabelRepeat");
        passwordLabelRepeat->setMinimumSize(QSize(200, 0));
        passwordLabelRepeat->setMaximumSize(QSize(250, 16777215));

        verticalLayout_2->addWidget(passwordLabelRepeat);

        passwordRepeatLineEdit = new QLineEdit(methodFrame);
        passwordRepeatLineEdit->setObjectName("passwordRepeatLineEdit");
        passwordRepeatLineEdit->setMinimumSize(QSize(200, 0));
        passwordRepeatLineEdit->setMaximumSize(QSize(265, 16777215));

        verticalLayout_2->addWidget(passwordRepeatLineEdit);

        verticalSpacer = new QSpacerItem(0, 50, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        startButton = new QPushButton(methodFrame);
        startButton->setObjectName("startButton");
        startButton->setMinimumSize(QSize(200, 0));
        startButton->setMaximumSize(QSize(250, 16777215));

        verticalLayout_2->addWidget(startButton);


        verticalLayout_6->addLayout(verticalLayout_2);


        verticalLayout_3->addWidget(methodFrame);


        horizontalLayout->addWidget(EncryptionFrame);

        FileFrame = new QFrame(centralwidget);
        FileFrame->setObjectName("FileFrame");
        FileFrame->setFrameShape(QFrame::Shape::StyledPanel);
        FileFrame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(FileFrame);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        fileUploadLabel = new QLabel(FileFrame);
        fileUploadLabel->setObjectName("fileUploadLabel");
        fileUploadLabel->setMinimumSize(QSize(1000, 0));

        verticalLayout_4->addWidget(fileUploadLabel);

        fileQueueLabel = new QLabel(FileFrame);
        fileQueueLabel->setObjectName("fileQueueLabel");

        verticalLayout_4->addWidget(fileQueueLabel);

        fileListView = new QListView(FileFrame);
        fileListView->setObjectName("fileListView");
        fileListView->setMovement(QListView::Movement::Static);
        fileListView->setSpacing(10);
        fileListView->setViewMode(QListView::ViewMode::IconMode);

        verticalLayout_4->addWidget(fileListView);


        verticalLayout_5->addLayout(verticalLayout_4);


        horizontalLayout->addWidget(FileFrame);


        verticalLayout->addLayout(horizontalLayout);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout->addWidget(statusLabel);


        horizontalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush11(QColor(73, 73, 73, 255));
        brush11.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush11);
        QBrush brush12(QColor(109, 109, 109, 255));
        brush12.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush12);
        QBrush brush13(QColor(91, 91, 91, 255));
        brush13.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush13);
        QBrush brush14(QColor(36, 36, 36, 255));
        brush14.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Dark, brush14);
        QBrush brush15(QColor(49, 49, 49, 255));
        brush15.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Mid, brush15);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush6);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush11);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Shadow, brush6);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::AlternateBase, brush14);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipBase, brush7);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Accent, brush6);
#endif
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush11);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush12);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush13);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Dark, brush14);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Mid, brush15);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush6);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush11);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Shadow, brush6);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::AlternateBase, brush14);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipBase, brush7);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Accent, brush6);
#endif
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush14);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush11);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush12);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush13);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Dark, brush14);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Mid, brush15);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush14);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush14);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush11);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush11);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Shadow, brush6);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::AlternateBase, brush11);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipBase, brush7);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipText, brush6);
        QBrush brush16(QColor(36, 36, 36, 127));
        brush16.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush16);
#endif
        QBrush brush17(QColor(51, 51, 51, 255));
        brush17.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Accent, brush17);
#endif
        menubar->setPalette(palette2);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        encLabel->setText(QCoreApplication::translate("MainWindow", "Encryption Settings", nullptr));
        methodLabel->setText(QCoreApplication::translate("MainWindow", "Method:", nullptr));
        passwordLabel->setText(QCoreApplication::translate("MainWindow", "Master Passphrase", nullptr));
        passwordLabelRepeat->setText(QCoreApplication::translate("MainWindow", "Repeat Passphrase", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\360\237\233\241Start Process", nullptr));
        fileUploadLabel->setText(QCoreApplication::translate("MainWindow", "\342\230\201 DRAG AND DROP FILES HERE", nullptr));
        fileQueueLabel->setText(QCoreApplication::translate("MainWindow", "File Queue", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Ready to process...", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
