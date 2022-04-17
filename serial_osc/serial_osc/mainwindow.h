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

#define MAX_DATA_SIZE 10000 //一屏显示的最大数据点数

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void vDetectAvailablePort(void);
    int my_readuart(void);//接收数据

    void my_senduart(void);//发送数据

    QwtPlotCurve *ch_curve;
    double ch_time[MAX_DATA_SIZE] = {0};
    double ch1_val[MAX_DATA_SIZE] = {0};


    short int i16_ch_val_buf[480] = {0};
    short int i16_rx_bytes_to_use = 0;

    QSerialPort *my_serialport;
    QSerialPortInfo portInfo;

    QByteArray baRcvData;
    QByteArray baSendData;
    QString strRcvData;

private slots:
    void on_pushButton_start_clicked();
     void timerEvent(void);

     void on_pushButton_stop_clicked();

     void on_pushButton_zoomerbase_clicked();

     void on_pushButton_clear_clicked();

     void on_pushButton_open_port_clicked();

     void on_pushButton_test_send_clicked();

     void wave_init();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
