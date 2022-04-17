#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>



QTimer *timer = new QTimer();
QwtPlotZoomer *zoomer;//缩放器

int iActDataLen = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int i=0;

    ui->setupUi(this);

    ch_curve = new QwtPlotCurve("CH0");

    ch_curve->setPen(Qt::red);
//    ch_curve->setStyle( QwtPlotCurve::Steps );

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

    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,  -6000.0, 6000.0 );
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
    delete zoomer;
}

void MainWindow::timerEvent()
{
   int i = 0;
   int j = 0;

   //my_senduart();
   //my_readuart();
   wave_init();

   if(i16_rx_bytes_to_use < 80)
   {
       return;
   }

   for(i=0; i<10; i++)//一次处理10次数据
   {
       ch1_val[iActDataLen] = (double)i16_ch_val_buf[i];
       //ch2_val[iActDataLen] = (double)i16_ch_val_buf[1+i*4];
       //ch3_val[iActDataLen] = (double)i16_ch_val_buf[2+i*4];
       //ch4_val[iActDataLen] = (double)i16_ch_val_buf[3+i*4];

       if(iActDataLen < (MAX_DATA_SIZE - 1))
       {
            iActDataLen++;
       }
       else
       {
            for(j=0;j<(MAX_DATA_SIZE - 1);j++)
            {
               ch1_val[j] =  ch1_val[j+1];
               //ch2_val[j] =  ch2_val[j+1];
               //ch3_val[j] =  ch3_val[j+1];
               //ch4_val[j] =  ch4_val[j+1];
            }
       }

   }

   for(i=0;i<(i16_rx_bytes_to_use - 80)/2; i++)
   {
       i16_ch_val_buf[i] = i16_ch_val_buf[i+40];

   }

   i16_rx_bytes_to_use -= 80;

   ui->textEdit_ch1_value->setText(QString::number(ch1_val[iActDataLen-1]));

   ch_curve->setSamples(ch_time,ch1_val,iActDataLen);
   ch_curve->attach(ui->qwtPlot);

   ui->qwtPlot->replot();
}


void MainWindow::on_pushButton_start_clicked()
{
    my_serialport->readAll();
    my_serialport->clear();
    timer->start(10);
}

void MainWindow::on_pushButton_stop_clicked()
{
    timer->stop();
}

void MainWindow::on_pushButton_zoomerbase_clicked()
{
    zoomer->setZoomBase();
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,  -6000.0, 6000.0 );
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom, 0.0, MAX_DATA_SIZE );

    ui->qwtPlot->replot();
}

void MainWindow::on_pushButton_clear_clicked()
{
    int i = 0;

    iActDataLen = 0;

    for(i=0;i<MAX_DATA_SIZE;i++)
    {
       ch_time[i] = i;
       ch1_val[i] = 0;
    }
    ch_curve->setSamples(ch_time,ch1_val,iActDataLen);
    ch_curve->attach(ui->qwtPlot);

    ui->qwtPlot->replot();
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

void MainWindow::on_pushButton_open_port_clicked()
{
    my_serialport->setPortName(ui->cbox_port->currentText().trimmed());
    my_serialport->close();

    if(ui->pushButton_open_port->text().trimmed() == tr("open"))
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

             ui->pushButton_open_port->setText(tr("close"));
         }
    }
    else
    {
        my_serialport->close();
        ui->pushButton_open_port->setText(tr("open"));
    }

}

int MainWindow::my_readuart()
{
    baRcvData.clear();

    baRcvData = my_serialport->readAll();
//    if((baRcvData == NULL) || (baRcvData.size() == 0))
//    {
//        return -1;
//    }

    memcpy(&i16_ch_val_buf[i16_rx_bytes_to_use/2],baRcvData.data(),baRcvData.size());
    i16_rx_bytes_to_use += baRcvData.size();

    qDebug()<<"received bytes:"<<baRcvData.size();
    qDebug()<<"received data:"<<baRcvData;

    return i16_rx_bytes_to_use;
}

void MainWindow::on_pushButton_test_send_clicked()
{
    my_senduart();
}

void MainWindow::my_senduart(void)
{
    int i=0;
    short int iTmpChValue[40];

    static  int iCount;

    baSendData.resize(sizeof(iTmpChValue));

    //产生4个正弦波，通过串口发送出去，如果将串口的Rx和Tx短接，则在示波器上将显示4个正弦波的波形
    for(i=0;i<10;i++)
    {
        iCount++;

        //iTmpChValue[i] = qSin((double)iCount/ 0.0005 * 2 * 3.1415926);
        iTmpChValue[i] = (double)500;
        //iTmpChValue[1+i*4] = 50*qSin((double)iCount/ 50 * 2 * 3.1415926+3.1415926/3);
        //iTmpChValue[2+i*4] = 50*qSin((double)iCount/ 50 * 2 * 3.1415926+3.1415926*2/3);
        //iTmpChValue[3+i*4] = 50*qSin((double)iCount/ 50 * 2 * 3.1415926+3.1415926);
    }

    memcpy(baSendData.data(),&iTmpChValue,sizeof(iTmpChValue));

    my_serialport->write(baSendData);
}


