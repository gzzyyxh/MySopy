#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "qcustomplot.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort SerialPort;        //用于设置串口
    QSerialPortInfo SerialPortInfo;//用于得到串口信息
    int Clk ;    //x轴的时间数
    QCustomPlot *Plot;    //定义一个窗口绘图的句柄
    QVector <double>    XData;//x轴数据
    QVector <double>    YData;//线1的y轴数据
    QVector <double>    Y1Data;//线2的y轴数据
    QCustomPlot *PlotV;    //定义另一个窗口绘图的句柄
    QVector <double>    Y2Data;
    QVector <double>    Y3Data;
};
#endif // MAINWINDOW_H
