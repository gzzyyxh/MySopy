#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <QTimer>
#include <qevent.h>
#include <qwt_plot.h>
#include <QtMath>
#include<qwt_plot_zoomer.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
//#include <QThread>
//#include <QObject>

#define MAX_DATA_SIZE 500 //一屏显示的最大数据点数
QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void vDetectAvailablePort(void);
    int my_readuart(void);//接收数据

    QwtPlotCurve *ch_curve;
    double ch_time[MAX_DATA_SIZE] = {0};
    double ch1_val[MAX_DATA_SIZE] = {0};

    float wave[500] = {0};

    short int i16_rx_bytes_to_use = 0;

    QSerialPort *my_serialport;
    QSerialPortInfo portInfo;

    QByteArray baRcvData;
    QString strRcvData;
//    double sitRcvData[500];
    QVector<float> sitRcvData;

private slots:
    void on_start_clicked();

    void timerEvent(void);

//    void on_open_clicked();

    void on_open_clicked();

    void on_stop_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
