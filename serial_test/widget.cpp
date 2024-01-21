
#include "widget.h"
#include "ui_widget.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
//#include "myserial.h"
#include <QString>
#include <QDebug>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    this->serialTest = new MySerial(this);
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
    connect(timer1, &QTimer::timeout, this, &Widget::flashComPort);

    // 获取串口设置改变值
    connect(ui->comboBox_Baud, &QComboBox::textActivated, this,  &Widget::setBaudRate);
    connect(ui->comboBox_Port, &QComboBox::currentTextChanged, this, &Widget::setPortName);
    connect(ui->comboBox_Stop, &QComboBox::currentTextChanged, this, &Widget::setStopBits);
    connect(ui->comboBox_DataBit, &QComboBox::currentTextChanged, this, &Widget::setDataBits);
    connect(ui->comboBox_Varity, &QComboBox::currentTextChanged, this, &Widget::setParity);

    //设置打开串口按键
    connect(ui->btn_open, &QPushButton::clicked, this, &Widget::openCloseSw);

    // 发送数据
    connect(ui->btn_send, &QPushButton::clicked, this, &Widget::sendData);

    //接收并显示数据
    connect(serialTest->mySerial, &QSerialPort::readyRead, this, &Widget::showData);

    //清空接收区数据
    connect(ui->btn_clear_rx, &QPushButton::clicked, this, &Widget::clearRx);

    //清空发送区数据
    connect(ui->btn_clear_tx, &QPushButton::clicked, this, &Widget::clearTx);
}

Widget::~Widget()
{
    if (this->serialTest->mySerial->isOpen()) {
        this->serialTest->mySerial->clear();
        this-> serialTest->mySerial->close();
    }
    qDebug()<<"串口已关闭";

    delete ui;
}

void Widget::flashComPort() {
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
}

void Widget::openCloseSw() {
    if (this->serialTest->onOpenCloseButtonClicked()) {
        this->ui->btn_open->setText("关闭");
    } else {
        this->ui->btn_open->setText("打开");
    }
}

void Widget::setBaudRate() {
    this->serialTest->setBaudRate(this->ui->comboBox_Baud->currentText());
}

void Widget::setPortName() {
    this->serialTest->setPortName(this->ui->comboBox_Port->currentText());
}

void Widget::setStopBits() {
    QString str1 = this->ui->comboBox_Stop->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();

    int bit = this->ui->comboBox_Stop->currentIndex();
    if (bit == 0)
        this->serialTest->mySerial->setStopBits(QSerialPort::OneStop);
    else if(bit == 1)
        this->serialTest->mySerial->setStopBits(QSerialPort::TwoStop);

    qDebug() << bit;
}

void Widget::setDataBits() {
    QString str1 = this->ui->comboBox_DataBit->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();

    int bit = this->ui->comboBox_DataBit->currentIndex();
    if (bit == 0)
        this->serialTest->mySerial->setDataBits(QSerialPort::Data8);
    else if (bit == 1)
        this->serialTest->mySerial->setDataBits(QSerialPort::Data7);
    else if (bit == 2)
        this->serialTest->mySerial->setDataBits(QSerialPort::Data6);
    else if (bit == 3)
        this->serialTest->mySerial->setDataBits(QSerialPort::Data5);
}

void Widget::setParity() {
    QString str1 = this->ui->comboBox_Varity->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();

    int bit = this->ui->comboBox_Varity->currentIndex();
    if (bit == 0)
        this->serialTest->mySerial->setParity(QSerialPort::NoParity);
    else if (bit == 1)
        this->serialTest->mySerial->setParity(QSerialPort::OddParity);
    else if (bit == 2)
        this->serialTest->mySerial->setParity(QSerialPort::EvenParity);
}

void Widget::sendData() {
    QByteArray tx_buff =  this->ui->text_tx->toPlainText().toLocal8Bit(); // 为了发送中文
    this->serialTest->sendData(tx_buff);
}

void Widget::showData() {
    this->ui->text_rx->append(this->serialTest->showData());
}

void Widget::clearTx() {
    this->ui->text_tx->clear();
}

void Widget::clearRx() {
    this->ui->text_rx->clear();
}

void Widget::on_pushButton_clicked() {
    unsigned char test[4] =  {0x01, 0x02, 0x03, 0x04};
    QByteArray tx_buff = QByteArray::fromRawData((char *)test, sizeof(test));

    this->serialTest->sendData(tx_buff);
}

