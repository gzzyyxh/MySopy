#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <sys/time.h>

QTimer *timer = new QTimer();

//static int i = 0;

struct timeval tpstart,tpend;
float timeuse;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<(double)-1.3;

}

MainWindow::~MainWindow()
{
    delete ui;
//    delete timer;
}

//static int j = 0;

//void MainWindow::timerEventp(){

////    if(i == 1000){
////        qDebug()<<j;
////        j++;
////        i = 0;
////    }
////    i++;
//    if(j == 0){
//        gettimeofday(&tpstart,NULL);
//        j++;
//    }
//    gettimeofday(&tpend,NULL);
//    timeuse=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec)/1000000.0;
//    qDebug()<<timeuse<<"s";
//}

