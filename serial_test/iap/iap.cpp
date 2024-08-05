#include "iap.h"


Iap::Iap(Widget *parent)
    : UserSerial{parent}
{
    ui->lineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9]+$")));
    ui->lineEdit->setMaxLength(16);
    ui->lineEdit_2->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9]+$")));
    ui->lineEdit_2->setMaxLength(16);

    /* 设置禁止用户编辑 */
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &Iap::iapStart);
    qDebug()<<"长度："<< sizeof("name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name");
}



Iap::~Iap()
{

    qDebug()<<"iap结束";
}


void Iap::iapStart(void) {
    QByteArray tx_buff;


    disconnect(mySerial, &QSerialPort::readyRead, this, &UserSerial::showData);
    connect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadCommParam);

    tx_buff.append("pbl+updata\r\n");
    qDebug()<<"已发送："<< tx_buff;
    mySerial->write(tx_buff);
}

// 函数用于解析并打印特定字段的值
bool Iap::parseAndPrintFields(const QString &data) {
    bool hasThreeNonEmptyKeys = true;

    // 使用逗号分割整个字符串为多个键值对
    QStringList keyValuePairs = data.split(",");

    // 遍历每个键值对
    foreach(const QString &pair, keyValuePairs) {
        // 使用冒号分割键值对，得到键和值
        QStringList parts = pair.split(":");

        if (parts.size() == 2) {
            QString key = parts.first().trimmed(); // 去除可能存在的空格
            QString value = parts.last().trimmed(); // 去除可能存在的空格

            // 根据键名判断并打印值
            if (key == "prtcl") {
                qDebug() << "Protocol:" << value;
                ui->lineEdit_3->setText(value);
            } else if (key == "packLen") {
                qDebug() << "Packet Length:" << value;
                ui->lineEdit_4->setText(value);
            } else if (key == "verif") {
                qDebug() << "Verification:" << value;
                ui->lineEdit_5->setText(value);
            } else {
                hasThreeNonEmptyKeys = false;
            }
        } else {
            hasThreeNonEmptyKeys = false;
        }
    }
    return hasThreeNonEmptyKeys;
}

void Iap::iapReadCommParam(void) {
    QByteArray rx_buff;

    if (mySerial->bytesAvailable()) {
        rx_buff = mySerial->readAll();
        qDebug()<< "已接收：" << rx_buff;

        parseAndPrintFields(rx_buff);

        disconnect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadCommParam);
        connect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadData);

        /* 控制字符 */
        QString startHexString = "01"; // 十六进制表示
        QByteArray byteArray = QByteArray::fromHex(startHexString.toUtf8());

        /* 帧计数 */
        byteArray.append(packCnt++);

        /* 文件信息 */
        byteArray.append("name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name");

        /* CRC */
        quint16 crc = calculateCRC16(byteArray);
        byteArray.append(crc >> 8);
        byteArray.append(crc);

        mySerial->write(byteArray);
    }
}

void Iap::iapReadData(void) {
    QByteArray rx_buff;

    if (mySerial->bytesAvailable()) {
        rx_buff = mySerial->readAll();
        qDebug()<< "已接收：" << rx_buff;

        /* 收到下一帧数据请求 */
        if (!rx_buff.isEmpty() && rx_buff.at(0) == 0x43) {
            qDebug() << "okkkk";

            QString startHexString = "02"; // 十六进制表示
            QByteArray byteArray = QByteArray::fromHex(startHexString.toUtf8());

            byteArray.append(packCnt++);

            byteArray.append("name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name");
            quint16 crc = calculateCRC16(byteArray);
            byteArray.append(crc >> 8);
            byteArray.append(crc);

            mySerial->write(byteArray);
        }
    }
}
