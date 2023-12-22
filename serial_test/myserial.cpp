
#include "myserial.h"
#include "ui_widget.h"
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPushButton>
#include <QString>

MySerial::MySerial(QWidget *parent)
    : QWidget{parent}
{
    this->ui = ((Widget*)parent)->ui;
    mySerial =new  QSerialPort;
    openFlag = true;
    qDebug() << "串口构造";
}

MySerial::~MySerial()
{
    qDebug() << "串口析构";
}


void MySerial::onOpenCloseButtonClicked() {
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

void MySerial::setBaudRate() {
    QString str1 = ui->comboBox_Baud->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();
    mySerial->setBaudRate(ui->comboBox_Baud->currentText().toInt());
}

void MySerial::setPortName() {
    QString str1 = ui->comboBox_Port->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();
    //        const QString portnameStr = ui->comboBox_Port->currentText();
    //       QSerialPortInfo info(portnameStr);
    mySerial->setPortName(str1);
}

void MySerial::setStopBits() {
    QString str1 = ui->comboBox_Stop->currentText();
    qDebug() << "选择了:"<<str1.toUtf8().data();

    int bit = ui->comboBox_Stop->currentIndex();
    if (bit == 0)
        mySerial->setStopBits(QSerialPort::OneStop);
    else if(bit == 1)
        mySerial->setStopBits(QSerialPort::TwoStop);

    qDebug() << bit;
}

void MySerial::setDataBits() {
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

void MySerial::setParity() {
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

void MySerial::sendData() {
    QByteArray tx_buff =  ui->text_tx->toPlainText().toLocal8Bit(); // 为了发送中文

    if (mySerial->isOpen()) {
        mySerial->write(tx_buff);
        qDebug()<<"已发送："<<QString::fromUtf8(tx_buff);
    }
    else {
        qDebug()<<"命令发送异常"<<mySerial->errorString().toUtf8().data();
        // mySerial->clearError();
    }

    // 测试
    // ui->text_rx->append(QString::fromUtf8(tx_buff));
    qDebug()<<"已接收："<<QString::fromUtf8(tx_buff);
}

void MySerial::showData() {
        QByteArray rx_buff;

        if (mySerial->bytesAvailable()) {
            rx_buff = mySerial->readAll();
            QString str = QString::fromLocal8Bit(rx_buff); // 为了显示中文
            // ui->text_rx->insertPlainText(QString::fromUtf8(rx_buff));
            ui->text_rx->append(str);
            qDebug()<<"已接收："<<str;
        }
}

void MySerial::clearTx() {
    ui->text_tx->clear();
}

void MySerial::clearRx() {
    ui->text_rx->clear();
}
