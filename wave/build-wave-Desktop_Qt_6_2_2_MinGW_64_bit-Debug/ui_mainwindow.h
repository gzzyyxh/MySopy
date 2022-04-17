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
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QwtPlot *qwtPlot;
    QPushButton *start;
    QPushButton *open;
    QComboBox *cbox_port;
    QPushButton *stop;
    QLabel *total_time;
    QLabel *total_points;
    QLabel *ppt;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1142, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        qwtPlot = new QwtPlot(centralwidget);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
        qwtPlot->setGeometry(QRect(80, 30, 971, 401));
        start = new QPushButton(centralwidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(340, 470, 92, 29));
        open = new QPushButton(centralwidget);
        open->setObjectName(QString::fromUtf8("open"));
        open->setGeometry(QRect(210, 470, 92, 29));
        cbox_port = new QComboBox(centralwidget);
        cbox_port->setObjectName(QString::fromUtf8("cbox_port"));
        cbox_port->setGeometry(QRect(80, 470, 89, 28));
        stop = new QPushButton(centralwidget);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setGeometry(QRect(460, 470, 92, 29));
        total_time = new QLabel(centralwidget);
        total_time->setObjectName(QString::fromUtf8("total_time"));
        total_time->setGeometry(QRect(600, 450, 251, 20));
        total_points = new QLabel(centralwidget);
        total_points->setObjectName(QString::fromUtf8("total_points"));
        total_points->setGeometry(QRect(600, 480, 251, 20));
        ppt = new QLabel(centralwidget);
        ppt->setObjectName(QString::fromUtf8("ppt"));
        ppt->setGeometry(QRect(600, 510, 251, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1142, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        start->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        open->setText(QCoreApplication::translate("MainWindow", "open", nullptr));
        stop->setText(QCoreApplication::translate("MainWindow", "stop", nullptr));
        total_time->setText(QCoreApplication::translate("MainWindow", "total time:", nullptr));
        total_points->setText(QCoreApplication::translate("MainWindow", "total points:", nullptr));
        ppt->setText(QCoreApplication::translate("MainWindow", "ppt:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
