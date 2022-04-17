#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <sys/time.h>
#include <QThread>

QTimer *timer = new QTimer();
QwtPlotZoomer *zoomer;//缩放器

struct timeval trecv_start,trecv_end,taction_start,taction_end,trecv;
float timeuse;

int sec = 0;

int iActDataLen = 0;
int i_wave = 0;
int total_time = 0;
int total_points = 0;
double ppt = 0;
float trig_level = 1;
int trig_edge = 1;
bool trig = 0;
bool trig_en = 0;
int trig_count = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int i = 0;

    ui->setupUi(this);

    ch_curve = new QwtPlotCurve("CH0");

    ch_curve->setPen(Qt::yellow);
    ch_curve->setStyle( QwtPlotCurve::Steps );

    ui->qwtPlot->setCanvasBackground(QColor(0,0,0));

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

int o = 0;
int p = 0;

void MainWindow::timerEvent(){
    trig_en = 0;
    trig = 0;
    iActDataLen = 0;
    sec++;
    int i = 0;
    int counter = 0;
    int counter_2 = 0;
    trig_count = 0;

    if(p == 0){
        gettimeofday(&trecv_start,NULL);
        p++;
    }

    my_readuart();
    gettimeofday(&trecv,NULL);
    double timeu = (1000000*(trecv.tv_sec-trecv_start.tv_sec) + trecv.tv_usec-trecv_start.tv_usec)/1000000.0;
    qDebug()<< QString::number(timeu)<<"s  and baRcvData.size(): "<<baRcvData.size()<< " and each cost: "<<QString::number(timeu/baRcvData.size())<<"s";

    if(o == 0){
        gettimeofday(&taction_start,NULL);
        o++;
    }

    if(baRcvData.size() >= MAX_DATA_SIZE){
        sitRcvData.clear();
//    qDebug()<<"baRcvData.size(): "<<baRcvData.size();
        p = 0;
        gettimeofday(&trecv_end,NULL);
        double time_use = (1000000*(trecv_end.tv_sec-trecv_start.tv_sec) + trecv_end.tv_usec-trecv_start.tv_usec)/1000000.0;
        qDebug()<<"This recv cost: " + QString::number(time_use)<<"s  and baRcvData.size(): "<<baRcvData.size()<< " and each cost: "<<QString::number(time_use/baRcvData.size())<<"s";
    const char *s = baRcvData.data();
    while(*s){
        double f = 5.0*(1.0 - (float(*s)>=0?float(*s):(float(*s) + 256))/128.0);
        if(counter == MAX_DATA_SIZE/2)
            trig_en = 1;
        if(trig_en){
            if (abs(f - trig_level) < 0.5){
                    if(sitRcvData.data()[counter -10] < f){
                        trig = 1;
                        trig_count = counter;
                        trig_en = 0;
                    }
            }
        }
        if(trig){
            sitRcvData.append(f);
            counter_2++;
        }
        else
            sitRcvData.append(f);
        s++;
        counter++;
        if(counter_2 == MAX_DATA_SIZE/2){
            qDebug()<<"sitRcvData.size()"<<sitRcvData.size()<<"counter:"<<counter<<"counter_2"<<counter_2<<"trig_count: "<<trig_count;
            sitRcvData.remove(0,sitRcvData.size() - MAX_DATA_SIZE);
            break;
        }
    }
//    qDebug()<<sitRcvData;
    baRcvData.clear();
    total_points += sitRcvData.size();
    i16_rx_bytes_to_use = sitRcvData.size();

//    qDebug()<<"start    sitRcvData.size(): "<<sitRcvData.size();
    i_wave = 0;
    for(i=0; i<MAX_DATA_SIZE; i++)//一次处理10次数据
    {
               ch1_val[iActDataLen] = (double)sitRcvData.data()[i_wave];
               iActDataLen++;
        i_wave++;
    }

    ch_curve->setSamples(ch_time,ch1_val,iActDataLen);

    ch_curve->attach(ui->qwtPlot);

    ui->qwtPlot->replot();

    ui->total_time->setText("total time:"+QString::number(total_time));
    ui->total_points->setText("total points:"+QString::number(total_points));
    ui->ppu->setText("ppu:"+QString::number(double(total_points)/double(total_time)));

    gettimeofday(&taction_end,NULL);
    qDebug()<<"This action use:" + QString::number((1000000*(taction_end.tv_sec-taction_start.tv_sec) + taction_end.tv_usec-taction_start.tv_usec)/1000000.0)<<"s";
    }
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

int MainWindow::my_readuart()
{
    total_time++;
    baRcvData += my_serialport->readAll();

    return 0;
}


void MainWindow::on_stop_clicked()
{
    timer->stop();
}

