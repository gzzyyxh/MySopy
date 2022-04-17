#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

static float sum = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->clear();
    //通过QSerialPortInfo查找可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->comboBox->addItem(info.portName());
    }
    //this->setMaximumSize(430,531);
    //this->setMinimumSize(430,531);
    //连接信号和槽
    QObject::connect(&serial, &QSerialPort::readyRead, this, &MainWindow::serialPort_readyRead);
    ui->comboBox_2->addItem(QWidget::tr("115200"));
    ui->comboBox_3->addItem(QWidget::tr("8"));
    //ui->comboBox_4->addItem();
    ui->comboBox_5->addItem(QWidget::tr("1"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//监测串口
void MainWindow::on_pushButton_3_clicked()
{
    ui->comboBox->clear();
    //通过QSerialPortInfo查找可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serialp;
        serialp.setPort(info);
        if(serialp.open(QIODevice::ReadWrite))
        {
            ui->comboBox->addItem(serialp.portName());
            serialp.close();
            }
        }
}
//打开串口
void MainWindow::on_pushButton_4_clicked()
{
    if(ui->pushButton_4->text()==QString("打开串口"))
     {
         //设置串口名
         serial.setPortName(ui->comboBox->currentText());
         //设置波特率
         serial.setBaudRate(ui->comboBox_2->currentText().toInt());
         //设置数据位数
         switch(ui->comboBox_3->currentIndex())
         {
         case 8: serial.setDataBits(QSerialPort::Data8); break;
         default: break;
         }
         //设置奇偶校验
//         switch(ui->comboBox_4->currentIndex())
//         {
//         case 0: serial.setParity(QSerialPort::NoParity); break;
//         default: break;
//         }
         //设置停止位
         switch(ui->comboBox_5->currentIndex())
         {
         case 1: serial.setStopBits(QSerialPort::OneStop); break;
         case 2: serial.setStopBits(QSerialPort::TwoStop); break;
         default: break;
         }
         //设置流控制
         serial.setFlowControl(QSerialPort::NoFlowControl);
         //打开串口
         if(!serial.open(QIODevice::ReadWrite))
         {
             QMessageBox::about(NULL,"提示","无法打开串口!");
             return;
         }
         //下拉菜单控件失能
         ui->comboBox->setEnabled(false);
         ui->comboBox_2->setEnabled(false);
         ui->comboBox_3->setEnabled(false);
         ui->comboBox_4->setEnabled(false);
         ui->comboBox_5->setEnabled(false);
         ui->pushButton_4->setText(QString("关闭串口"));
         //发送按键使能
         ui->pushButton_2->setEnabled(true);
     }
     else
     {
         //关闭串口
         serial.close();
         //下拉菜单控件使能
         ui->comboBox->setEnabled(true);
         ui->comboBox_2->setEnabled(true);
         ui->comboBox_3->setEnabled(true);
         ui->comboBox_4->setEnabled(true);
         ui->comboBox_5->setEnabled(true);
         ui->pushButton_4->setText(QString("打开串口"));
         //发送按键失能
         ui->pushButton_2->setEnabled(false);
     }
}
//发送数据
void MainWindow::on_pushButton_2_clicked()
{
    //获取界面上的数据并转换成utf8格式的字节流
    QByteArray data = ui->textEdit_2->toPlainText().toUtf8();
    serial.write(data);
}
//清空接收
void MainWindow::on_pushButton_clicked()
{
   ui->textEdit->clear();
}

//串口接收
void MainWindow::serialPort_readyRead()
{
    //从接收缓冲区中读取数据
    QByteArray buffer = serial.readAll();
    sum += buffer.size();
    ui->size->setText("size: "+QString::number(sum));
    //从界面中读取以前收到的数据
//    QString recv = ui->textEdit->toPlainText();
    QString recv = QString(buffer);
    //清空以前的显示
    //ui->textEdit->clear();
    //重新显示
//    ui->textEdit->append(recv);
//    qDebug() << recv;
    ui->textEdit->insertPlainText(buffer);
}



