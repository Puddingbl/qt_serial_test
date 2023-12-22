
#ifndef MYSERIAL_H
#define MYSERIAL_H


#include <QWidget>
#include "widget.h"
#include <ui_widget.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPushButton>



class MySerial : public QWidget
{
    Q_OBJECT

public:

    explicit MySerial(QWidget *parent = nullptr);
    ~MySerial();

    Ui::Widget *ui; //用于调用ui里控件

    QSerialPort *mySerial; // 串口类指针

//    void onReadyRead();

//    void onSendButtonClicked();

private:
    bool openFlag; //串口打开按键标志位

public slots:
    void onOpenCloseButtonClicked();
    void setBaudRate();
    void setPortName();
    void setStopBits();
    void setDataBits();
    void setParity();
    void sendData();
    void showData();
    void clearTx();
    void clearRx();
signals:

};

#endif // MYSERIAL_H
