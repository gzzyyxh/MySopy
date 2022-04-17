#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

QTimer *timer = new QTimer();
QwtPlotZoomer *zoomer;//缩放器

int sec = 0;

int iActDataLen = 0;
int i_wave = 0;
int total_time = 0;
int total_points = 0;
double ppt = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int i = 0;

    ui->setupUi(this);

    ch_curve = new QwtPlotCurve("CH0");

    ch_curve->setPen(Qt::blue);
//  ch_curve->setStyle( QwtPlotCurve::Steps );

    connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));

    //设置示波器背景网格
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen( Qt::gray, 0.0, Qt::DotLine );
    grid->enableX( true );
    grid->enableXMin( true );
    grid->enableY( true );
    grid->enableYMin( true );
    grid->attach(  ui->qwtPlot );

    //设置缩放器,左键选择放大，右键还原
    zoomer = new QwtPlotZoomer(ui->qwtPlot->canvas());
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,Qt::RightButton );
    zoomer->setZoomBase();

    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,  -5.0, 5.0 );
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0.0, MAX_DATA_SIZE );

    for(i=0;i<MAX_DATA_SIZE;i++)
    {
       ch_time[i] = i;
       ch1_val[i] = 0;
    }

//    for(i = 0;i < 1024;i++){
//        wave[i] = 100*qSin((double)i/ 1024 * 2 * 3.1415926);
//        qDebug() << wave[i];
//    }

    my_serialport = new QSerialPort();

   //检测可用的串口
   vDetectAvailablePort();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete my_serialport;
    delete timer;
}

void MainWindow::timerEvent(){
//    for(int m = 0; m < 20; m++){

    sec++;
    int i = 0;
    int j = 0;
    my_readuart();
//    return;

    if(i16_rx_bytes_to_use < 1)
    {
        return;
    }
    if(sec%1000 == 0)
    qDebug()<<"rrrrrrrrrrrrrrrrrrrrrrrrrrrrrr: "<<i16_rx_bytes_to_use;
//    for(int j = 0; j < 1024; j++){
//        if(ch1_val[j]!=0){
//            ch1_val[j] = 0;
//        }
//        else
//            break;
//    }

    for(i=0; i<1000; i++)//一次处理10次数据
    {
        ch1_val[iActDataLen] = (double)wave[i_wave];
        if(iActDataLen < (MAX_DATA_SIZE - 1))
        {
             iActDataLen++;
        }
        else
        {
             for(j=0;j<(MAX_DATA_SIZE - 1);j++)
             {
                ch1_val[j] =  ch1_val[j+1];

             }
        }
//         qDebug() << "ch1_val: " << ch1_val[iActDataLen] << "wave:" << wave[i_wave];
        i_wave++;
        if(i_wave == 2047) {
//            i_wave = 0;
            break;
        }
        if(i_wave > i16_rx_bytes_to_use)
            break;
    }
    if(i == 500) i -= 1;
//    qDebug()<<"WWWWWWWWWWWWWWWWWWWWW:"<<i_wave;
    if(sec%1000 == 0){
    qDebug()<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii: "<<i+1;
    sec = 0;
    }

    for(int j=0;j<(i16_rx_bytes_to_use - i + 1); j++)
    {
        wave[j] = wave[j+i];

    }
    for(int j = i16_rx_bytes_to_use - i; j<i16_rx_bytes_to_use; j++)
        wave[j] = 0;

    i_wave -= i+1;

    i16_rx_bytes_to_use -= i+1;

    ch_curve->setSamples(ch_time,ch1_val,iActDataLen);
    ch_curve->attach(ui->qwtPlot);

    ui->qwtPlot->replot();
//    }

}


void MainWindow::on_start_clicked()
{
    my_serialport->readAll();
    my_serialport->clear();
    timer->start(1);
}

void MainWindow::vDetectAvailablePort()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QSerialPort serial;
        serial.setPort(info);

        if(serial.open(QIODevice::ReadWrite))
        {
            ui->cbox_port->addItem(info.portName());
            serial.close();
        }

    }
}

void MainWindow::on_open_clicked()
{
    my_serialport->setPortName(ui->cbox_port->currentText().trimmed());
    my_serialport->close();

    if(ui->open->text().trimmed() == tr("open"))
    {
         if(my_serialport->open(QIODevice::ReadWrite))
         {
             my_serialport->setBaudRate(QSerialPort::Baud115200);
             my_serialport->setDataBits(QSerialPort::Data8);
             my_serialport->setParity(QSerialPort::NoParity);
             my_serialport->setStopBits(QSerialPort::OneStop);
             my_serialport->setFlowControl(QSerialPort::NoFlowControl);
             my_serialport->setReadBufferSize(1024);
             my_serialport->clear();

             ui->open->setText(tr("close"));
         }
    }
    else
    {
        my_serialport->close();
        ui->open->setText(tr("open"));
    }

}

//int k = 0;

int MainWindow::my_readuart()
{
    total_time++;
    baRcvData.clear();
    sitRcvData.clear();

    baRcvData = my_serialport->readAll();
    if(/*(baRcvData == NULL) || */(baRcvData.size() == 0))
    {
        return -1;
    }
//    k++;
    const char *s = baRcvData.data();
//    while(((*s)+48) && ((*s)+48)>='0' && ((*s)+48)<='255') {
    while(*s){
        sitRcvData.append(5.0*(1.0 - (float(*s)>=0?float(*s):(float(*s) + 256))/128.0));
//        if(k == 100){
//            for(auto a : baRcvData){
//                qDebug()<<a;
//                break;
//            }
//        k = 0;
//        }
        s++;
    }

//    if (*s)
//    { //不是纯数字
////        qDebug()<<"received data:";
////        for(auto i : baRcvData)
////            qDebug()<<i;
////        sitRcvData.clear();
//        qDebug()<<"jffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
//        return 0;
//    }

    memcpy(&wave[i16_rx_bytes_to_use],sitRcvData.data(),sitRcvData.size());
    i16_rx_bytes_to_use += sitRcvData.size() - 1;
    total_points += sitRcvData.size() + 1;
    if(sec%1000 == 0){
    qDebug()<<"sitRcvData"<<sitRcvData.size();
    qDebug()<<"sum"<<total_points;
    qDebug()<<"sec"<<sec;
    }

//    qDebug()<<"received bytes:"<<sitRcvData.size();
//    qDebug()<<"received data:"<<sitRcvData;
//    qDebug()<<"wave_size: " << lenth(wave);
//    qDebug()<<"i16_rx_bytes_to_use: "<<i16_rx_bytes_to_use;
//    for(auto i : wave)
//    qDebug()<<"wave :"<<i;

    ui->total_time->setText("total time:"+QString::number(total_time));
    ui->total_points->setText("total points:"+QString::number(total_points));
    ui->ppt->setText("ppt:"+QString::number(double(total_points)/double(total_time)));
    return i16_rx_bytes_to_use;
}


void MainWindow::on_stop_clicked()
{
    timer->stop();
}

