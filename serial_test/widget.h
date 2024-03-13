
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "myserial.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QFileDialog>

#include "crc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QStringList oldPortStringList;

    Ui::Widget *ui;

    MySerial *serialTest;

    void flashComPort();
    void setBaudRate();
    void setPortName();
    void setStopBits();
    void setDataBits();
    void setParity();
    void openCloseSw();
    void sendData();
    void showData();
    void clearTx();
    void clearRx();

    void open_file();
    void updateFileWithCRC16();
    QFile *file;

private slots:


private:


};

#endif // WIDGET_H

