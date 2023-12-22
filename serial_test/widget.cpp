
#include "widget.h"
#include "ui_widget.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "myserial.h"
#include <QString>
#include <QDebug>
#include <QTimer>
MySerial *serialTest = nullptr;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    serialTest = new MySerial(this);

    //获取串口
    //清除串口号
    ui->comboBox_Port->clear();
    //遍历 QSerialPortInfo, 添加到串口下拉框中
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        oldPortStringList += info.portName();
        ui->comboBox_Port->addItem(info.portName());
    }
    //设置默认波特率
    ui->comboBox_Baud->setCurrentIndex(3);

    QString str1 = ui->comboBox_Baud->currentText();
    qDebug() << str1.toUtf8().data();

    QTimer *timer1 = new QTimer(this);

    timer1->start(500);

    //定时刷新串口列表
    connect(timer1, &QTimer::timeout, this, [=](){
        qDebug() << "够钟了";

        QStringList newPortStringList;

        foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
            newPortStringList += info.portName();
        }

        //更新串口号
        if(newPortStringList.size() != oldPortStringList.size())
        {
            oldPortStringList = newPortStringList;
            ui->comboBox_Port->clear();
            ui->comboBox_Port->addItems(oldPortStringList);
        }
    });

    // 获取串口设置改变值
    connect(ui->comboBox_Baud, &QComboBox::textActivated, serialTest,  &MySerial::setBaudRate);
    connect(ui->comboBox_Port, &QComboBox::currentTextChanged, serialTest, &MySerial::setPortName);
    connect(ui->comboBox_Stop, &QComboBox::currentTextChanged, serialTest, &MySerial::setStopBits);
    connect(ui->comboBox_DataBit, &QComboBox::currentTextChanged, serialTest, &MySerial::setDataBits);
    connect(ui->comboBox_Varity, &QComboBox::currentTextChanged, serialTest, &MySerial::setParity);

    //设置打开串口按键
    connect(ui->btn_open, &QPushButton::clicked, serialTest, &MySerial::onOpenCloseButtonClicked);

    // 发送数据
    connect(ui->btn_send, &QPushButton::clicked, serialTest, &MySerial::sendData);

    //接收并显示数据
    connect(serialTest->mySerial, &QSerialPort::readyRead, serialTest, &MySerial::showData);

    //清空接收区数据
    connect(ui->btn_clear_rx, &QPushButton::clicked, serialTest, &MySerial::clearRx);

    //清空发送区数据
    connect(ui->btn_clear_tx, &QPushButton::clicked, serialTest, &MySerial::clearTx);
}

Widget::~Widget()
{
    if (serialTest->mySerial->isOpen()) {
        serialTest->mySerial->clear();
        serialTest->mySerial->close();
    }
    qDebug()<<"串口已关闭";

    delete ui;
}


