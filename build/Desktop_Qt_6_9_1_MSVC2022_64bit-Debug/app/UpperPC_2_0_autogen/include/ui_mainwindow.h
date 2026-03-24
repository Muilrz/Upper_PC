/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QProgressBar *progressBar;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnReset;
    QPushButton *btnPause;
    QPushButton *btnContinue;
    QGroupBox *groupBox;
    QComboBox *cmbPort;
    QComboBox *cmbBaud;
    QPushButton *btnRefreshPorts;
    QPushButton *btnOpenPort;
    QLineEdit *edtTx;
    QPushButton *btnSend;
    QLabel *lblUartStatus;
    QPlainTextEdit *txtRx;
    QGroupBox *MFF102;
    QPushButton *btnMffRefresh;
    QPushButton *btnMffPos2;
    QPushButton *btnMffConnect;
    QPushButton *btnMffPos1;
    QLabel *lblMffStatus;
    QComboBox *cmbMffSerial;
    QPushButton *btnMffStartPolling;
    QPushButton *btnMffStopPolling;
    QPushButton *btnMffReadPos;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuEDA_FSM;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(774, 576);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(120, 210, 461, 20));
        progressBar->setMinimumSize(QSize(0, 20));
        progressBar->setValue(0);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 82, 211));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnStart = new QPushButton(layoutWidget);
        btnStart->setObjectName("btnStart");
        btnStart->setMinimumSize(QSize(0, 18));

        verticalLayout->addWidget(btnStart);

        btnStop = new QPushButton(layoutWidget);
        btnStop->setObjectName("btnStop");
        btnStop->setMinimumSize(QSize(0, 18));

        verticalLayout->addWidget(btnStop);

        btnReset = new QPushButton(layoutWidget);
        btnReset->setObjectName("btnReset");
        btnReset->setMinimumSize(QSize(0, 18));

        verticalLayout->addWidget(btnReset);

        btnPause = new QPushButton(layoutWidget);
        btnPause->setObjectName("btnPause");
        btnPause->setMinimumSize(QSize(0, 18));

        verticalLayout->addWidget(btnPause);

        btnContinue = new QPushButton(layoutWidget);
        btnContinue->setObjectName("btnContinue");
        btnContinue->setMinimumSize(QSize(0, 18));

        verticalLayout->addWidget(btnContinue);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 240, 571, 231));
        cmbPort = new QComboBox(groupBox);
        cmbPort->setObjectName("cmbPort");
        cmbPort->setGeometry(QRect(360, 20, 191, 31));
        cmbBaud = new QComboBox(groupBox);
        cmbBaud->setObjectName("cmbBaud");
        cmbBaud->setGeometry(QRect(360, 60, 191, 31));
        btnRefreshPorts = new QPushButton(groupBox);
        btnRefreshPorts->setObjectName("btnRefreshPorts");
        btnRefreshPorts->setGeometry(QRect(360, 100, 91, 31));
        btnOpenPort = new QPushButton(groupBox);
        btnOpenPort->setObjectName("btnOpenPort");
        btnOpenPort->setGeometry(QRect(460, 100, 91, 31));
        edtTx = new QLineEdit(groupBox);
        edtTx->setObjectName("edtTx");
        edtTx->setGeometry(QRect(10, 130, 331, 81));
        btnSend = new QPushButton(groupBox);
        btnSend->setObjectName("btnSend");
        btnSend->setGeometry(QRect(360, 140, 191, 31));
        lblUartStatus = new QLabel(groupBox);
        lblUartStatus->setObjectName("lblUartStatus");
        lblUartStatus->setGeometry(QRect(360, 180, 201, 31));
        txtRx = new QPlainTextEdit(groupBox);
        txtRx->setObjectName("txtRx");
        txtRx->setGeometry(QRect(10, 20, 331, 101));
        txtRx->setReadOnly(true);
        MFF102 = new QGroupBox(centralwidget);
        MFF102->setObjectName("MFF102");
        MFF102->setGeometry(QRect(130, 10, 451, 191));
        btnMffRefresh = new QPushButton(MFF102);
        btnMffRefresh->setObjectName("btnMffRefresh");
        btnMffRefresh->setGeometry(QRect(210, 20, 101, 31));
        btnMffPos2 = new QPushButton(MFF102);
        btnMffPos2->setObjectName("btnMffPos2");
        btnMffPos2->setGeometry(QRect(340, 70, 81, 41));
        btnMffConnect = new QPushButton(MFF102);
        btnMffConnect->setObjectName("btnMffConnect");
        btnMffConnect->setGeometry(QRect(330, 20, 101, 31));
        btnMffPos1 = new QPushButton(MFF102);
        btnMffPos1->setObjectName("btnMffPos1");
        btnMffPos1->setGeometry(QRect(230, 70, 81, 41));
        lblMffStatus = new QLabel(MFF102);
        lblMffStatus->setObjectName("lblMffStatus");
        lblMffStatus->setGeometry(QRect(30, 130, 171, 31));
        cmbMffSerial = new QComboBox(MFF102);
        cmbMffSerial->setObjectName("cmbMffSerial");
        cmbMffSerial->setGeometry(QRect(10, 20, 181, 31));
        btnMffStartPolling = new QPushButton(MFF102);
        btnMffStartPolling->setObjectName("btnMffStartPolling");
        btnMffStartPolling->setGeometry(QRect(230, 130, 101, 31));
        btnMffStopPolling = new QPushButton(MFF102);
        btnMffStopPolling->setObjectName("btnMffStopPolling");
        btnMffStopPolling->setGeometry(QRect(340, 130, 91, 31));
        btnMffReadPos = new QPushButton(MFF102);
        btnMffReadPos->setObjectName("btnMffReadPos");
        btnMffReadPos->setGeometry(QRect(110, 110, 91, 41));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 774, 17));
        menuEDA_FSM = new QMenu(menubar);
        menuEDA_FSM->setObjectName("menuEDA_FSM");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuEDA_FSM->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "RESET", nullptr));
        btnPause->setText(QCoreApplication::translate("MainWindow", "PAUSE", nullptr));
        btnContinue->setText(QCoreApplication::translate("MainWindow", "CONTINUE", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243", nullptr));
        btnRefreshPorts->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        btnOpenPort->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        lblUartStatus->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201: \346\234\252\350\277\236\346\216\245", nullptr));
        MFF102->setTitle(QCoreApplication::translate("MainWindow", "MFF102-\347\224\265\345\212\250\347\277\273\350\275\254\345\231\250", nullptr));
        btnMffRefresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\350\256\276\345\244\207", nullptr));
        btnMffPos2->setText(QCoreApplication::translate("MainWindow", "\344\275\215\347\275\256 2", nullptr));
        btnMffConnect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245/\346\226\255\345\274\200", nullptr));
        btnMffPos1->setText(QCoreApplication::translate("MainWindow", "\344\275\215\347\275\256 1", nullptr));
        lblMffStatus->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\347\212\266\346\200\201\357\274\232", nullptr));
        btnMffStartPolling->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\350\256\276\345\244\207\350\275\256\350\257\242", nullptr));
        btnMffStopPolling->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\235\237\350\256\276\345\244\207\350\275\256\350\257\242", nullptr));
        btnMffReadPos->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\345\275\223\345\211\215\344\275\215\347\275\256", nullptr));
        menuEDA_FSM->setTitle(QCoreApplication::translate("MainWindow", "EDA-FSM\346\265\213\350\257\225\347\211\210\346\234\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
