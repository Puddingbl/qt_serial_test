
#include "userSerial.h"
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPushButton>
#include <QTimer>

userSerial::userSerial(Widget *parent)
    : Widget{parent}
{
    // mySerial =new  QSerialPort;
    mySerial = new QSerialPort(this);
    openFlag = true;

    // mySerial->setParity(QSerialPort::NoParity);
    // mySerial->setStopBits(QSerialPort::OneStop);
    // mySerial->setDataBits(QSerialPort::Data8);


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
    connect(timer1, &QTimer::timeout, this, &userSerial::flashComPort);

    // 获取串口设置改变值
    connect(ui->comboBox_Baud, &QComboBox::textActivated, this,  &userSerial::setBaudRate);
    connect(ui->comboBox_Port, &QComboBox::currentTextChanged, this, &userSerial::setPortName);
    connect(ui->comboBox_Stop, &QComboBox::currentTextChanged, this, &userSerial::setStopBits);
    connect(ui->comboBox_DataBit, &QComboBox::currentTextChanged, this, &userSerial::setDataBits);
    connect(ui->comboBox_Varity, &QComboBox::currentTextChanged, this, &userSerial::setParity);

    //设置打开串口按键
    connect(ui->btn_open, &QPushButton::clicked, this, &userSerial::onOpenCloseButtonClicked);

    // 发送数据
    connect(ui->btn_send, &QPushButton::clicked, this, &userSerial::sendData);

    //接收并显示数据
    connect(mySerial, &QSerialPort::readyRead, this, &userSerial::showData);

    //清空接收区数据
    connect(ui->btn_clear_rx, &QPushButton::clicked, this, &userSerial::clearRx);

    //清空发送区数据
    connect(ui->btn_clear_tx, &QPushButton::clicked, this, &userSerial::clearTx);


    qDebug() << "串口构造";
}

userSerial::~userSerial()
{
    if (mySerial->isOpen()) {
        mySerial->clear();
        mySerial->close();
    }

    qDebug()<<"串口已关闭";
}

void userSerial::flashComPort() {
    //qDebug() << "够钟了";

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

void userSerial::onOpenCloseButtonClicked(void) {
    if(openFlag) {
        // if (mySerial->isOpen()) {
        if (mySerial->open(QIODevice::ReadWrite)) {
            openFlag = false;
            ui->btn_open->setText("关闭");
            qDebug()<<"串口已打开,读写模式";
        }
        else {
            qDebug() << "串口打开异常："<<mySerial->errorString().toUtf8().data();
            // mySerial->clearError();
        }
    }
    else {
        ui->btn_open->setText("打开");
        mySerial->clear();
        mySerial->close();
        openFlag = true;
        qDebug()<<"串口已关闭";
    }
}

void userSerial::setBaudRate(void) {
    QString str1 = ui->comboBox_Baud->currentText();

    qDebug() << "选择了:"<<str1.toUtf8().data();
    mySerial->setBaudRate(str1.toInt());
}

void userSerial::setPortName(void) {
    QString str1 = ui->comboBox_Port->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();
    //        const QString portnameStr = ui->comboBox_Port->currentText();
    //       QSerialPortInfo info(portnameStr);
    mySerial->setPortName(str1);
}

void userSerial::setStopBits(void) {
    QString str1 = ui->comboBox_Stop->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();

    int bit = ui->comboBox_Stop->currentIndex();
    if (bit == 0)
        mySerial->setStopBits(QSerialPort::OneStop);
    else if(bit == 1)
        mySerial->setStopBits(QSerialPort::TwoStop);

    qDebug() << bit;
}

void userSerial::setDataBits(void) {
    QString str1 = ui->comboBox_DataBit->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();

    int bit = ui->comboBox_DataBit->currentIndex();
    if (bit == 0)
        mySerial->setDataBits(QSerialPort::Data8);
    else if (bit == 1)
        mySerial->setDataBits(QSerialPort::Data7);
    else if (bit == 2)
        mySerial->setDataBits(QSerialPort::Data6);
    else if (bit == 3)
        mySerial->setDataBits(QSerialPort::Data5);
}

void userSerial::setParity(void) {
    QString str1 = ui->comboBox_Varity->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();

    int bit = ui->comboBox_Varity->currentIndex();
    if (bit == 0)
        mySerial->setParity(QSerialPort::NoParity);
    else if (bit == 1)
        mySerial->setParity(QSerialPort::OddParity);
    else if (bit == 2)
        mySerial->setParity(QSerialPort::EvenParity);
}

void userSerial::sendData(void) {
    QByteArray tx_buff =  ui->text_tx->toPlainText().toLocal8Bit(); // 为了发送中文

    if (mySerial->isOpen()) {
        mySerial->write(tx_buff);
        qDebug()<<"已发送："<<QString::fromUtf8(tx_buff);
    }
    else {
        qDebug()<<"命令发送异常"<<mySerial->errorString().toUtf8().data();
        // mySerial->clearError();
    }
    ui->text_rx->append(QString::fromLocal8Bit(tx_buff));
    // 测试
    // ui->text_rx->append(QString::fromUtf8(tx_buff));
    // qDebug()<<"已接收："<<QString::fromUtf8(tx_buff);
}

void userSerial::showData(void) {
    QByteArray rx_buff;

    if (mySerial->bytesAvailable()) {
        rx_buff = mySerial->readAll();
        QString str = QString::fromLocal8Bit(rx_buff); // 为了显示中文
        // ui->text_rx->insertPlainText(QString::fromUtf8(rx_buff));
        // ui->text_rx->append(str);
        qDebug()<<"已接收："<<str;

        ui->text_rx->append(str);
    }
}

void userSerial::clearTx() {
    ui->text_tx->clear();
}

void userSerial::clearRx() {
    ui->text_rx->clear();
}

