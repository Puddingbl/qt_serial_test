
#include "userSerial.h"
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPushButton>
#include <QTimer>

UserSerial::UserSerial(Widget *parent)
    : Widget{parent}
{
    // mySerial =new  QSerialPort;
    mySerial = new QSerialPort(this);
    openFlag = true;

    mySerial->setParity(QSerialPort::NoParity);
    mySerial->setStopBits(QSerialPort::OneStop);
    mySerial->setDataBits(QSerialPort::Data8);

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
    ui->comboBox_Port->setCurrentIndex(0);

    QString str1 = ui->comboBox_Baud->currentText();
    qDebug() << str1.toUtf8().data();

    str1 = ui->comboBox_Port->currentText();
    qDebug() << str1.toUtf8().data();
    mySerial->setPortName(str1);

    QTimer *timer1 = new QTimer(this);

    timer1->start(500);

    //定时刷新串口列表
    connect(timer1, &QTimer::timeout, this, &UserSerial::flashComPort);

    // 获取串口设置改变值
    connect(ui->comboBox_Baud, &QComboBox::textActivated, this,  &UserSerial::setBaudRate);
    connect(ui->comboBox_Port, &QComboBox::textActivated, this, &UserSerial::setPortName);
    connect(ui->comboBox_Stop, &QComboBox::currentTextChanged, this, &UserSerial::setStopBits);
    connect(ui->comboBox_DataBit, &QComboBox::currentTextChanged, this, &UserSerial::setDataBits);
    connect(ui->comboBox_Varity, &QComboBox::currentTextChanged, this, &UserSerial::setParity);

    //设置打开串口按键
    connect(ui->btn_open, &QPushButton::clicked, this, &UserSerial::onOpenCloseButtonClicked);

    // 发送数据
    connect(ui->btn_send, &QPushButton::clicked, this, &UserSerial::sendData);

    //接收并显示数据
    connect(mySerial, &QSerialPort::readyRead, this, &UserSerial::showData);

    //清空接收区数据
    connect(ui->btn_clear_rx, &QPushButton::clicked, this, &UserSerial::clearRx);

    //清空发送区数据
    connect(ui->btn_clear_tx, &QPushButton::clicked, this, &UserSerial::clearTx);


    qDebug() << "串口构造";
}

UserSerial::~UserSerial()
{
    if (mySerial->isOpen()) {
        mySerial->clear();
        mySerial->close();
        free(mySerial);
    }

    qDebug()<<"串口已关闭";
}

void UserSerial::flashComPort() {
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

void UserSerial::onOpenCloseButtonClicked(void) {
    if(openFlag) {
        // if (mySerial->isOpen()) {
        if (mySerial->open(QIODevice::ReadWrite)) {
            openFlag = false;
            ui->btn_open->setText("关闭");
            qDebug()<<"串口已打开,读写模式";
        }
        else {
            qDebug() << "串口打开异常："<< mySerial->errorString().toUtf8().data();
            // qDebug() << "串口名："<< mySerial->portName();
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

void UserSerial::setBaudRate(void) {
    QString str1 = ui->comboBox_Baud->currentText();

    qDebug() << "选择了:"<<str1.toUtf8().data();
    mySerial->setBaudRate(str1.toInt());
}

void UserSerial::setPortName(void) {
    QString str1 = ui->comboBox_Port->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();

    mySerial->setPortName(str1);
}

void UserSerial::setStopBits(void) {
    QString str1 = ui->comboBox_Stop->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();

    int bit = ui->comboBox_Stop->currentIndex();
    if (bit == 0)
        mySerial->setStopBits(QSerialPort::OneStop);
    else if(bit == 1)
        mySerial->setStopBits(QSerialPort::TwoStop);

    qDebug() << bit;
}

void UserSerial::setDataBits(void) {
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

void UserSerial::setParity(void) {
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

void UserSerial::sendData(void) {
    QByteArray tx_buff =  ui->text_tx->toPlainText().toLocal8Bit(); // 为了发送中文

    if (mySerial->isOpen()) {
        // tx_buff.append("\r\n");
        mySerial->write(tx_buff);
        qDebug()<<"已发送："<<QString::fromUtf8(tx_buff);
    }
    else {
        qDebug()<<"命令发送异常"<<mySerial->errorString().toUtf8().data();
        // mySerial->clearError();
    }
    ui->text_rx->append(QString::fromLocal8Bit(tx_buff));
}

void UserSerial::showData(void) {
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

void UserSerial::clearTx() {
    ui->text_tx->clear();
}

void UserSerial::clearRx() {
    ui->text_rx->clear();
}

