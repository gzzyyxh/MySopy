/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_start;
    QTextEdit *textEdit_ch1_addr;
    QTextEdit *textEdit_ch2_addr;
    QTextEdit *textEdit_ch3_addr;
    QTextEdit *textEdit_ch4_addr;
    QTextEdit *textEdit_ch4_value;
    QTextEdit *textEdit_ch3_value;
    QTextEdit *textEdit_ch1_value;
    QTextEdit *textEdit_ch2_value;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_stop;
    QwtPlot *qwtPlot;
    QPushButton *pushButton_zoomerbase;
    QPushButton *pushButton_clear;
    QComboBox *cbox_port;
    QPushButton *pushButton_open_port;
    QPushButton *pushButton_test_send;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1022, 607);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(510, 510, 75, 23));
        textEdit_ch1_addr = new QTextEdit(centralWidget);
        textEdit_ch1_addr->setObjectName(QString::fromUtf8("textEdit_ch1_addr"));
        textEdit_ch1_addr->setGeometry(QRect(210, 420, 111, 31));
        textEdit_ch2_addr = new QTextEdit(centralWidget);
        textEdit_ch2_addr->setObjectName(QString::fromUtf8("textEdit_ch2_addr"));
        textEdit_ch2_addr->setGeometry(QRect(340, 420, 111, 31));
        textEdit_ch3_addr = new QTextEdit(centralWidget);
        textEdit_ch3_addr->setObjectName(QString::fromUtf8("textEdit_ch3_addr"));
        textEdit_ch3_addr->setGeometry(QRect(470, 420, 111, 31));
        textEdit_ch4_addr = new QTextEdit(centralWidget);
        textEdit_ch4_addr->setObjectName(QString::fromUtf8("textEdit_ch4_addr"));
        textEdit_ch4_addr->setGeometry(QRect(600, 420, 111, 31));
        textEdit_ch4_value = new QTextEdit(centralWidget);
        textEdit_ch4_value->setObjectName(QString::fromUtf8("textEdit_ch4_value"));
        textEdit_ch4_value->setGeometry(QRect(600, 460, 111, 31));
        textEdit_ch3_value = new QTextEdit(centralWidget);
        textEdit_ch3_value->setObjectName(QString::fromUtf8("textEdit_ch3_value"));
        textEdit_ch3_value->setGeometry(QRect(470, 460, 111, 31));
        textEdit_ch1_value = new QTextEdit(centralWidget);
        textEdit_ch1_value->setObjectName(QString::fromUtf8("textEdit_ch1_value"));
        textEdit_ch1_value->setGeometry(QRect(210, 460, 111, 31));
        textEdit_ch2_value = new QTextEdit(centralWidget);
        textEdit_ch2_value->setObjectName(QString::fromUtf8("textEdit_ch2_value"));
        textEdit_ch2_value->setGeometry(QRect(340, 460, 111, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 430, 54, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 470, 54, 12));
        pushButton_stop = new QPushButton(centralWidget);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));
        pushButton_stop->setGeometry(QRect(600, 510, 75, 23));
        qwtPlot = new QwtPlot(centralWidget);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
        qwtPlot->setGeometry(QRect(10, 10, 971, 401));
        pushButton_zoomerbase = new QPushButton(centralWidget);
        pushButton_zoomerbase->setObjectName(QString::fromUtf8("pushButton_zoomerbase"));
        pushButton_zoomerbase->setGeometry(QRect(740, 420, 75, 23));
        pushButton_clear = new QPushButton(centralWidget);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(830, 420, 75, 23));
        cbox_port = new QComboBox(centralWidget);
        cbox_port->setObjectName(QString::fromUtf8("cbox_port"));
        cbox_port->setGeometry(QRect(180, 510, 111, 22));
        pushButton_open_port = new QPushButton(centralWidget);
        pushButton_open_port->setObjectName(QString::fromUtf8("pushButton_open_port"));
        pushButton_open_port->setGeometry(QRect(300, 510, 75, 23));
        pushButton_test_send = new QPushButton(centralWidget);
        pushButton_test_send->setObjectName(QString::fromUtf8("pushButton_test_send"));
        pushButton_test_send->setGeometry(QRect(400, 510, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1022, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_start->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Address:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Value:", nullptr));
        pushButton_stop->setText(QCoreApplication::translate("MainWindow", "stop", nullptr));
        pushButton_zoomerbase->setText(QCoreApplication::translate("MainWindow", "zoomer", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        pushButton_open_port->setText(QCoreApplication::translate("MainWindow", "open", nullptr));
        pushButton_test_send->setText(QCoreApplication::translate("MainWindow", "send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
