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
    QPushButton *stop;
    QwtPlot *qwtPlot;
    QPushButton *open;
    QPushButton *start;
    QLabel *total_points;
    QLabel *total_time;
    QLabel *ppu;
    QComboBox *cbox_port;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1182, 660);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stop = new QPushButton(centralwidget);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setGeometry(QRect(480, 480, 92, 29));
        qwtPlot = new QwtPlot(centralwidget);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
        qwtPlot->setGeometry(QRect(100, 40, 971, 401));
        open = new QPushButton(centralwidget);
        open->setObjectName(QString::fromUtf8("open"));
        open->setGeometry(QRect(230, 480, 92, 29));
        start = new QPushButton(centralwidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(360, 480, 92, 29));
        total_points = new QLabel(centralwidget);
        total_points->setObjectName(QString::fromUtf8("total_points"));
        total_points->setGeometry(QRect(620, 490, 251, 20));
        total_time = new QLabel(centralwidget);
        total_time->setObjectName(QString::fromUtf8("total_time"));
        total_time->setGeometry(QRect(620, 460, 251, 20));
        ppu = new QLabel(centralwidget);
        ppu->setObjectName(QString::fromUtf8("ppu"));
        ppu->setGeometry(QRect(620, 520, 251, 20));
        cbox_port = new QComboBox(centralwidget);
        cbox_port->setObjectName(QString::fromUtf8("cbox_port"));
        cbox_port->setGeometry(QRect(100, 480, 89, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1182, 25));
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
        stop->setText(QCoreApplication::translate("MainWindow", "stop", nullptr));
        open->setText(QCoreApplication::translate("MainWindow", "open", nullptr));
        start->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        total_points->setText(QCoreApplication::translate("MainWindow", "total points:", nullptr));
        total_time->setText(QCoreApplication::translate("MainWindow", "total time:", nullptr));
        ppu->setText(QCoreApplication::translate("MainWindow", "ppu:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
