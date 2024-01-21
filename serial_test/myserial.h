
#ifndef MYSERIAL_H
#define MYSERIAL_H


#include <QWidget>
//#include "widget.h"
#include <ui_widget.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPushButton>
#include <QString>


class MySerial : public QWidget
{
    Q_OBJECT

public:

    explicit MySerial(QWidget *parent = nullptr);
    ~MySerial();


    QSerialPort *mySerial; // 串口类指针

//    void onReadyRead();

//    void onSendButtonClicked();

private:
    bool openFlag; //串口打开按键标志位

public slots:
    bool onOpenCloseButtonClicked();
    void setBaudRate(QString str1);
    void setPortName(QString str1);
    // void setStopBits();
    // void setDataBits();
    // void setParity();
    void sendData(QByteArray tx_buff);
    QString showData();
signals:

};

#endif // MYSERIAL_H
