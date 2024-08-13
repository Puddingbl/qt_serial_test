
#include "widget.h"
#include "ui_widget.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QSettings>


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


    connect(ui->pushButton_3, &QPushButton::clicked, this, &Widget::open_file);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Widget::updateFileWithCRC16);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &Widget::updateFileWithAES);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &Widget::saveAs);
}

Widget::~Widget()
{

    if (!this->file) {
        free(this->file);
    }
    if (!this->ui) {
        free(this->ui);
    }
    qDebug()<<"串口已关闭";

    delete ui;
}



void Widget::open_file() {
    // 打开配置文件
    QString config_path = qApp->applicationDirPath() + "/config/Setting.ini";
    // 读配置文件信息
    QSettings *pIniSet = new QSettings(config_path, QSettings::IniFormat);
    // 读配置文件里的路径信息
    QString lastPath = pIniSet->value("/LastPath/path").toString();

    if (lastPath.isEmpty()) {
        // 如果是空的，则用根目录
        lastPath = "./";
    }

    // 打开文件
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("打开文件"),
        lastPath, tr("bin files(*.bin);;hex files(*.hex);;All files (*.*)"));

    // 找到选中文件路径中最后一个斜杠的位置
    int end = fileName.lastIndexOf("/");
    // 提取选中文件路径中的目录部分
    QString _path = fileName.left(end);
    // 将上次访问的路径保存到配置文件中
    pIniSet->setValue("/LastPath/path", _path);
    delete pIniSet;
    pIniSet = nullptr;


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
