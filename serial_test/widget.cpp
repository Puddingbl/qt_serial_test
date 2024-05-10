
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

    //QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::CBC, QAESEncryption::PKCS7);

    //this->aes = new QAESEncryption();

    ui->lineEditKey->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9]+$")));
    ui->lineEditKey->setMaxLength(16);
    ui->lineEditIv->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9]+$")));
    ui->lineEditIv->setMaxLength(16);

    // fileDataBuff.clear();
    // // 重置数组大小且不填充
    // fileDataBuff.reserve(this->file->size()+sizeof(image_header_t));

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

    connect(ui->pushButton_3, &QPushButton::clicked, this, &Widget::open_file);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Widget::updateFileWithCRC16);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &Widget::updateFileWithAES);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &Widget::saveAs);
}

Widget::~Widget()
{
    if (this->serialTest->mySerial->isOpen()) {
        this->serialTest->mySerial->clear();
        this-> serialTest->mySerial->close();
    }
    if (!this->file) {
        free(this->file);
    }
    qDebug()<<"串口已关闭";

    delete ui;
}

void Widget::flashComPort() {
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
    this->ui->text_rx->append(tx_buff);
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

void Widget::open_file() {   
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("打开文件"),
        "./", tr("bin files(*.bin);;hex files(*.hex);;All files (*.*)"));

    this->file = new QFile(fileName);

    fileDataBuff.clear();
    // 重置数组大小且不填充
    fileDataBuff.reserve(this->file->size() + sizeof(image_header_t) + 16);

    // 不能以txt方式打开读写，不然会丢失\n等内容
    if (!this->file->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open the source file.";
        return;
    }

    QDataStream in(this->file);
    qDebug() << "die1";
    // 读取原始文件内容
    // char data[this->file->size()];
    // char *data = (char *)malloc(this->file->size());
    char *data = new char[this->file->size()];
    qDebug() << "die2";
    this->header.ih_size = this->file->size();
    // 用这种方式将文件内容写到QByteArray数组才不会丢失数据
    in.readRawData(data, this->file->size());
    qDebug() << "die3";
    QString str = "file.size:";
    ui->textFileInfo->append(str + QString::number(this->file->size()));
    qDebug() << "die3";
    qDebug() << "data.size:" << sizeof(data);
    fileDataBuff.append(data, this->file->size()); // 在数组末尾写入
    delete[] data;
    qDebug() << "die3";
    this->file->close();
}

void Widget::updateFileWithCRC16() {
    // 计算CRC16
    //quint16 crcValue = crc16_ccitt(fileData);
     this->header.ih_hcrc = calculateCRC16(fileDataBuff);

    // 在数组头部写入CRC16校验值
    fileDataBuff.prepend(reinterpret_cast<const char*>(&this->header), sizeof(this->header));
    qDebug() << "fileDataBuff.size:" << fileDataBuff.size();
    // qDebug() << "fileDataBuff:" << fileDataBuff.toHex();

    QString str = "header.ih_hcrc:";
    ui->textFileInfo->append(str + QString::number(this->header.ih_hcrc));
    str = "fileDataBuff.size:";
    ui->textFileInfo->append(str + QString::number(fileDataBuff.size()));

    //qDebug() << "crcValue:" << crcValue;
    qDebug() << "header.ih_hcrc:" << this->header.ih_hcrc;
    qDebug() << "fileDataBuff.size:" << fileDataBuff.size();
}

void Widget::updateFileWithAES() {
    QString key = "0123456789012345";
    QByteArray iv = QString("1234567812345678").toUtf8();

    QString key_temp = this->ui->lineEditKey->text();
    QString iv_temp = this->ui->lineEditIv->text();

    if (key_temp.length() == 16) {
        key = key_temp;

        QString str = "key:";
        ui->textFileInfo->append(str+key);
        qDebug() << "Key: " << key;
    }
    if (iv_temp.length() == 16) {
        iv = iv_temp.toUtf8();

        QString str = "iv:";
        ui->textFileInfo->append(str+iv);
        qDebug() << "iv: " << iv;
    }     

    QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::CBC, QAESEncryption::PKCS7); // QAESEncryption::PKCS7 QAESEncryption::ZERO
    QByteArray enBA = encryption.encode(fileDataBuff, key.toUtf8(), iv); //CBC模式（必须要有初始IV向量）
    // qDebug() << "enBA: " << enBA;

    fileDataBuff.clear();
    fileDataBuff.append(enBA, enBA.size()); // 在数组末尾写入
    // qDebug() << "fileDataBuff: " << fileDataBuff;
    // qDebug() << "fileDataBuff: " << fileDataBuff.toHex();
 }

void Widget::saveAs() {
    // 获取另存文件的路径
    QFileDialog fileDialog;

    QString str = fileDialog.getSaveFileName(this, tr("另存文件"), this->file->fileName(), tr("bin files(*.bin);;hex files(*.hex);;All files (*.*)"));
    QFile newFile(str);

    if (!newFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open the new file.";
        return;
    }
    QDataStream out(&newFile);
    out.writeRawData(reinterpret_cast<const char*>(fileDataBuff.data()), fileDataBuff.size());

    newFile.close();
}
