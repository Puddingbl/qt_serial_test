
#ifndef USERSERIAL_H
#define USERSERIAL_H


#include <QWidget>
#include "widget.h"
#include <ui_widget.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPushButton>
#include <QString>


class UserSerial : public Widget
{
    Q_OBJECT

public:

    explicit UserSerial(Widget *parent = nullptr);
    ~UserSerial();


    QSerialPort *mySerial; // 串口类指针
    QStringList oldPortStringList;

    void flashComPort();
//    void onReadyRead();
//    void onSendButtonClicked();

private:
    bool openFlag; //串口打开按键标志位
    QTimer *timerCheckPort;

public slots:
    void onOpenCloseButtonClicked(void);
    void setBaudRate(void);
    void setPortName(void);
    void setStopBits(void);
    void setDataBits(void);
    void setParity(void);
    void sendData(void);
    void showData(void);
    void clearTx(void);
    void clearRx(void);
signals:

};

#endif // MYSERIAL_H
