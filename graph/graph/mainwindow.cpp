#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    XData.resize(50);    //分配空间
    XData.value(0,1);
    YData.resize(50);
    Y1Data.resize(50);
    Y2Data.resize(50);
    Y3Data.resize(50);
    ui->horizontalAMax->setRange(600,3000);
    ui->horizontalAMax->setValue(600);
    ui->horizontalAMin->setRange(0,600);
    ui->horizontalAMin->setValue(0);
    ui->horizontalVMax->setRange(500,800);
    ui->horizontalVMax->setValue(600);
    ui->horizontalVMin->setRange(0,500);
    ui->horizontalVMin->setValue(400);

    Plot = ui->widget;        //指定窗口用于显示波形
    Plot->addGraph();        //添加一条线
    Plot->addGraph();        //再添加一条线
    Plot->graph(0)->setPen(QPen(Qt::red));    //设置第一根线的颜色为红色
    Plot->graph(1)->setPen(QPen(Qt::blue));   //设置第二根线的颜色为蓝色
    Plot->xAxis->setLabel("mS");        //设置x轴的标签
    Plot->yAxis->setLabel("mA");        //设置y轴的标签
//    Plot->rescaleAxes(true);
    Plot->yAxis->setRange(0,700);        //初始化y轴的范围
    Plot->xAxis->rescale(true);          //让x轴自动随着数变化

    PlotV = ui->widget_C;
    PlotV->addGraph();
    PlotV->addGraph();
    PlotV->graph(0)->setPen(QPen(Qt::red));
    PlotV->graph(1)->setPen(QPen(Qt::blue));
    PlotV->xAxis->setLabel("mS");
    PlotV->yAxis->setLabel("Count");
    PlotV->yAxis->setRange(400,600);
    PlotV->xAxis->rescale(true);

    GraphShow();    //给图形赋值
    InitPort();    //初始化串口
    QTimer::singleShot(80,this,&Widget::ReadPort);//定一定时器，方便接收数据
    Clk = 0;    //x轴的时间数，初试为0
}

MainWindow::~MainWindow()
{
    delete ui;
}

void Widget::InitPort()    //判断当前是否有效的串口，并得到相关得数据
{
    //遍历所有有效的串口，得到每个有效串口得数据
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name :"<<info.portName();
        qDebug() << "Description: "<<info.description();
        qDebug() << "Manufacturer: "<<info.manufacturer();
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {//判断是否能够打开该串口，如果能，则将相应的串口名加到串口的下拉栏里
            ui->comboBoxCom->addItem(info.portName());
            serial.close();//这里只是起判定效果，不用以打开，还得关闭当前串口，方便查询其他串口
        }
    }
}
//这个是开启按键的槽函数，如果有有效的串口，然后进行打开操作，也可以充当关闭串口的作用
void Widget::on_pushButtonS_clicked()
{
    //判断当前程序处于什么状态中，如果没有串口使用，则进入“开启串口”
    if(ui->pushButtonS->text() == "开启串口")
    {    //得到当前串口栏得数据
        SerialPort.setPortName(ui->comboBoxCom->currentText());
        if(SerialPort.open(QIODevice::ReadOnly))
        {
            SerialPort.setBaudRate(ui->comboBoxBaut->currentText().toInt());//设置波特率
            SerialPort.setDataBits(QSerialPort::Data8);//设置数据位为8位
            SerialPort.setParity(QSerialPort::NoParity);//没有奇偶校验位
            SerialPort.setFlowControl(QSerialPort::NoFlowControl);//没有流控制
            SerialPort.setStopBits(QSerialPort::OneStop);//设置一个停止位

            ui->pushButtonS->setText("关闭串口");    //更改按键状态
        }
        else{
            qDebug() << "串口没有打开";
            return;
        }
    }else if(ui->pushButtonS->text() == "关闭串口")
        {
        SerialPort.close();
        ui->pushButtonS->setText("开启串口");
    }
    else{
        qDebug() <<"无效操作";
    }
}
//获取串口数据，我这里是采用每隔40ms来获取一次数据
void Widget::ReadPort()
{
    QTimer::singleShot(40,this,&Widget::ReadPort);
    if(SerialPort.isOpen() == false)
        return;
    //得到串口数据
    QByteArray temp = SerialPort.readAll();
    if(temp.isEmpty())
        return;
    //将数据进行文本化显示
    ui->textEditR->append(QString(temp));
    GetData(QString(temp));//处理当前数据，得出有效数据，这个函数实现是按要求来的，就不贴出来了
    GraphShow();
}

void Widget::GraphShow()
{
    Plot->graph(0)->setData(XData,YData);
    Plot->graph(1)->setData(XData,Y1Data);
    Plot->yAxis->setRange(Slither_aMin,Slither_aMax);
    Plot->xAxis->rescale(true);
    Plot->replot();//重新绘制

    PlotV->graph(0)->setData(XData,Y2Data);
    PlotV->graph(1)->setData(XData,Y3Data);
    PlotV->yAxis->setRange(Slither_vMin,Slither_vMax);
    PlotV->xAxis->rescale(true);
    PlotV->replot();
}

