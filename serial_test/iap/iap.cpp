#include "iap.h"
#include <QSettings>

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
    connect(ui->pushButton_8, &QPushButton::clicked, this, &Iap::open_file);
    qDebug() << "len:" << strlen("name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name");
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
                //packLen = value;
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

uint8_t start_cnt = 0;
QByteArray start_buff;
uint8_t start_flag = 0;

void Iap::iapReadCommParam(void) {
    QByteArray rx_buff;

    if (mySerial->bytesAvailable()) {
        rx_buff = mySerial->readAll();

        if (static_cast<unsigned char>(rx_buff.at(0)) == 0xaa) {
            start_flag = 1;
        }

        if (start_flag) {
            start_buff.append(rx_buff);
            if (start_buff.size() == 128) {
                start_flag = 0;
            } else {
                return;
            }
        } else {
            return;
        }

        qDebug()<< "已接收：" << start_buff;

        parseAndPrintFields(start_buff);

        disconnect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadCommParam);
        connect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadData);

        quint8 startChar = 0x01;
        QByteArray byteArray;

        byteArray.append(startChar);
        /* 帧计数 */
        byteArray.append(packCnt++);

        char fileInfo[128];

        sprintf(fileInfo, "name:qwe\n size:%d\n", fileSize);
        /* 文件信息 */
        //byteArray.append("name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe\n size:121\n name:qwe");
        byteArray.append(fileInfo);
        QByteArray fillArray;
        fillArray.fill(static_cast<char>(0x00), 128 - strlen(fileInfo));
        byteArray.append(fillArray);
        qDebug()<< "fileInfo:" << fileInfo;

        /* CRC */
        quint16 crc = calculateCRC16(byteArray);
        byteArray.append(crc >> 8);
        byteArray.append(crc);

        mySerial->write(byteArray);
    }
}

int len2 = 0;
void Iap::iapReadData(void) {
    QByteArray rx_buff;

    if (mySerial->bytesAvailable()) {
        rx_buff = mySerial->readAll();
        // qDebug()<< "已接收：" << rx_buff.toHex();

        if (endFlag == true) {
            connect(mySerial, &QSerialPort::readyRead, this, &UserSerial::showData);
            disconnect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadData);

            QByteArray endArray;
            quint8 startChar = 0x04;

            endArray.append(startChar);

            mySerial->write(endArray);
            offset = 0;
            endFlag = false;
            qDebug() << "结束捏" << pack_cnt;
            return;
        }

        /* 收到下一帧数据请求 */
        if (!rx_buff.isEmpty() && rx_buff.at(0) == 0x43) {
            qDebug()<< "已接收：" << rx_buff.toHex();
            QByteArray byteArray;
            quint8 startChar = 0x02;

            byteArray.append(startChar);
            byteArray.append(packCnt++);

            int bytesRead = qMin(packLen, fileSize - offset);
            byteArray.append(fileDataBuff.mid(offset, bytesRead));

            if (bytesRead < (packLen)) {
                QByteArray fillArray;
                int count = packLen - bytesRead;
                qDebug() << "count：" << count;

                fillArray.fill(static_cast<char>(0xff), count);

                byteArray.append(fillArray);
                endFlag = true;
            }
            offset += bytesRead;

            quint16 crc = calculateCRC16(byteArray);
            byteArray.append(crc >> 8);
            byteArray.append(crc);

            // qDebug() << "crc:" << crc;
            pack_cnt++;
            mySerial->write(byteArray);

            // qDebug() << "byteArray:" << byteArray;
            // qDebug() << "-------------------";
        }
    }
}

int vb_cnt = 0;
QByteArray vb_buff;
uint8_t vb_flag = 0;
void Iap::iapVB(void) {
    QByteArray rx_buff;

    if (mySerial->bytesAvailable()) {
        rx_buff = mySerial->readAll();

        if (static_cast<unsigned char>(rx_buff.at(0)) == 0xff) {
            vb_flag = 1;
            qDebug() << "开始捏";
        }

        if (vb_flag) {
            vb_buff.append(rx_buff);
            vb_cnt++;
            if (vb_cnt == fileSize) {
                vb_flag = 0;
            } else {
                return;
            }
        } else {
            return;
        }

        qDebug() << "来捏:" << vb_cnt;
        for (int i = 0; i < fileSize; i++) {
            if (vb_buff.at(i) != fileDataBuff.at(i)) {
                qDebug() << "i:" << i;
            }
        }

    }
}



void Iap::open_file() {
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
    // // 重置数组大小且不填充
    // fileDataBuff.reserve(this->file->size() + sizeof(image_header_t) + 16);

    // 不能以txt方式打开读写，不然会丢失\n等内容
    if (!this->file->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open the source file.";
        return;
    }

    QDataStream in(this->file);

    // 读取原始文件内容
    // char data[this->file->size()];
    // char *data = (char *)malloc(this->file->size());
    char *data = new char[this->file->size()];

    this->header.ih_size = this->file->size();
    // 用这种方式将文件内容写到QByteArray数组才不会丢失数据
    in.readRawData(data, this->file->size());

    QString str = "file.size:";
    ui->textFileInfo->append(str + QString::number(this->file->size()));

    fileSize = this->file->size();
    qDebug() << "data.size:" << this->file->size();
    fileDataBuff.append(data, this->file->size()); // 在数组末尾写入
    delete[] data;

    this->file->close();
}

