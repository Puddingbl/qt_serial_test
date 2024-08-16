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



    // 打开配置文件
    QString config_path = qApp->applicationDirPath() + "/config/Setting.ini";
    // 读配置文件信息
    QSettings *pIniSet = new QSettings(config_path, QSettings::IniFormat);
    // 读配置文件里的路径信息
    QString lastPath = pIniSet->value("/iapFilePath/path").toString();

    if (!lastPath.isEmpty()) {
        // 打开文件
        QString fileName = QFileDialog::getOpenFileName(
            this, tr("打开文件"),
            lastPath, tr("bin files(*.bin);;hex files(*.hex);;All files (*.*)"));

        QFileSystemWatcher *watcher = new QFileSystemWatcher(this);
        watcher->addPath(fileName);

        connect(watcher, &QFileSystemWatcher::fileChanged, this, &Iap::onFileChanged);
        connect(watcher, &QFileSystemWatcher::directoryChanged, this, &Iap::onDirectoryChanged);
    }



    connect(ui->pushButton_2, &QPushButton::clicked, this, &Iap::iapStart);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &Iap::open_file);    
}



Iap::~Iap()
{
    qDebug()<<"iap结束";
}


void Iap::iapStart(void) {
    QByteArray tx_buff;

    packCnt = 0;
    packDataLen = 0;
    cmdBuff.clear();
    endState = 0;
    // fileParam.fileDataBuff.clear();
    // fileParam.fileName.clear();
    // fileParam.fileSize = 0;
    fileParam.readFileOffset = 0;

    pack_cnt = 0;  // 调试用的参数，不重要

    disconnect(mySerial, &QSerialPort::readyRead, this, &UserSerial::showData);
    connect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadData);

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
                if (value.toInt() > 1024) {
                    qDebug() << "帧长过长:" << value;
                    hasThreeNonEmptyKeys = false;
                    break;
                }

                packDataLen = value.toInt();
                qDebug() << "Packet Length:" << packDataLen;
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

void Iap::iapReadData(void) {
    static quint8 transStep = 0;

    if (!mySerial->bytesAvailable()) {
        return;
    }

    QByteArray rx_buff = mySerial->readAll();
    // qDebug()<< "已接收：" << rx_buff;

    // 防止被发大量数据攻击
    if (rx_buff.size() > 1050) {
        qDebug()<< "啊？我被攻击了？";
        return;
    }

    switch (transStep) {
    case 1: {
        if (sendDataHandle(rx_buff) == IAP_COMPL) {
            transStep = 2;
        }
    } break;

    case 0: {
        if (sendFileParamHandle(rx_buff) == IAP_COMPL) {
            transStep = 1;
        }
    } break;

    case 2: {
        if (sendEndHandle(rx_buff) == IAP_COMPL) {
            connect(mySerial, &QSerialPort::readyRead, this, &UserSerial::showData);
            disconnect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadData);
            transStep = 0;
        }
    } break;

    default: break;
    }
}

Iap::TransState Iap::sendFileParamHandle(QByteArray byteArray) {
    static quint8 step = 0;

    switch (step) {
    case 0: {
        if (static_cast<unsigned char>(byteArray.at(0)) == C) {
            step = 1;
            cmdBuff.append(byteArray);
        }
    } break;

    case 1: {
        cmdBuff.append(byteArray);
        if (cmdBuff.size() != 128) {
            return IAP_TRANING;
        }

        step = 0;
        // qDebug()<< "已接收：" << cmdBuff;

        parseAndPrintFields(cmdBuff);
        sendPack(SOH, getFileInfo());
        cmdBuff.clear();

        return IAP_COMPL;
    } break;

    default: {
        step = 0;
        cmdBuff.clear();
        return IAP_ERROR;
    } break;
    }
    return IAP_TRANING;
}

Iap::TransState Iap::sendDataHandle(QByteArray byteArray) {
    for (int i = 0; i < byteArray.size(); i++) {
        if (byteArray.at(i) == ACK) {
            cmdBuff.append(byteArray.at(i));
        } else if (byteArray.at(i) == C) {
            cmdBuff.append(byteArray.at(i));
        } else if (byteArray.at(i) == CA) {
            cmdBuff.append(byteArray.at(i));
        } else if (byteArray.at(i) == NAK) {
            quint8 temp = 0;
            cmdBuff.append(byteArray.at(i));
            cmdBuff.append(temp);
        }
    }

    if (cmdBuff.size() < 2) {
        return IAP_TRANING;
    }

    /* 收到下一帧数据请求 */
    if (cmdBuff.at(0) == ACK && cmdBuff.at(1) == C) {
        sendPack(STX, getPackData(&fileParam));
        // qDebug()<< "正常";
    } else if (byteArray.at(0) == NAK) {
        fileParam.readFileOffset -= packDataLen;
        sendPack(STX, getPackData(&fileParam));
    } else if (cmdBuff.at(0) == CA && cmdBuff.at(1) == CA) {
        connect(mySerial, &QSerialPort::readyRead, this, &UserSerial::showData);
        disconnect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadData);
        return IAP_ERROR;
    }
    cmdBuff.clear();

    // 文件发完，发送结束信号
    if (fileParam.readFileOffset >= fileParam.fileSize) {
        return IAP_COMPL;
    }
    return IAP_TRANING;
}

Iap::TransState Iap::sendEndHandle(QByteArray byteArray) {
    switch (endState) {
    case 0: {
        qDebug() << byteArray.toHex();
        for (int i = 0; i < byteArray.size(); i++) {
            if (byteArray.at(i) == ACK) {
                cmdBuff.append(byteArray.at(i));
            } else if (byteArray.at(i) == C) {
                cmdBuff.append(byteArray.at(i));
            }
        }
        if (cmdBuff.size() < 2) {
            break;
        }

        if (cmdBuff.at(0) == ACK && cmdBuff.at(1) == C) {
            endState = 1;
            QByteArray endArray;
            quint8 startChar = EOT;

            endArray.append(startChar);
            mySerial->write(endArray);
        }
        cmdBuff.clear();
    } break;

    case 1: {
        if (byteArray.at(0) != NAK) {
            break;
        }
        QByteArray endArray;
        quint8 startChar = EOT;

        endArray.append(startChar);
        mySerial->write(endArray);

        endState = 2;
    } break;

    case 2: {
        if (byteArray.at(0) != ACK) {
            break;
        }
        // connect(mySerial, &QSerialPort::readyRead, this, &UserSerial::showData);
        // disconnect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadData);

        return IAP_COMPL;
    } break;

    default: break;
    }
    return IAP_TRANING;
}

void Iap::sendPack(quint8 cmd, QByteArray packData) {
    QByteArray byteArray;
    quint8 startChar = cmd;

    // 帧头
    byteArray.append(startChar);
    byteArray.append(packCnt++);

    // 帧数据
    byteArray.append(packData);

    // 校验
    quint16 check = iapPackCheck(byteArray);
    byteArray.append(check >> 8);
    byteArray.append(check);

    pack_cnt++;
    mySerial->write(byteArray);
    // qDebug() << "packCnt:" << byteArray;
}

int Iap::iapPackCheck(QByteArray byteArray) {
    int crc = calculateCRC16(byteArray);

    return crc;
}

QByteArray Iap::getFileInfo() {
    QByteArray byteArray;
    QByteArray fillArray;

    QString fileInfo;
    QTextStream(&fileInfo) << "name:" << fileParam.fileName << "\n "
                           << "size:" << fileParam.fileSize << "\n";
    /* 文件信息 */
    byteArray.append(fileInfo.toUtf8());
    fillArray.fill(static_cast<char>(0x00), 128 - fileInfo.size());
    byteArray.append(fillArray);

    return byteArray;
}

QByteArray Iap::getPackData(struct iapFileParam *fileParam) {
    int bytesRead = qMin(packDataLen, fileParam->fileSize - fileParam->readFileOffset);
    QByteArray packData = fileParam->fileDataBuff.mid(fileParam->readFileOffset, bytesRead);
    // qDebug()<< "packData:" << packData;
    if (bytesRead < (packDataLen)) {
        QByteArray fillArray;
        int count = packDataLen - bytesRead;
        qDebug() << "count：" << count;

        fillArray.fill(static_cast<char>(0xff), count);

        packData.append(fillArray);
    }
    fileParam->readFileOffset += packDataLen;

    return packData;
}


void Iap::open_file() {
    // 打开配置文件
    QString config_path = qApp->applicationDirPath() + "/config/Setting.ini";
    // 读配置文件信息
    QSettings *pIniSet = new QSettings(config_path, QSettings::IniFormat);
    // 读配置文件里的路径信息
    QString lastPath = pIniSet->value("/iapFilePath/path").toString();

    if (lastPath.isEmpty()) {
        // 如果是空的，则用根目录
        lastPath = "./";
    }

    // 打开文件
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("打开文件"),
        lastPath, tr("bin files(*.bin);;hex files(*.hex);;All files (*.*)"));

    QFileInfo fileInfo(fileName);
    fileParam.fileName = fileInfo.fileName();

    this->file = new QFile(fileName);

    fileParam.fileDataBuff.clear();

    // 不能以txt方式打开读写，不然会丢失\n等内容
    if (!this->file->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open the source file.";
        return;
    }

    // 找到选中文件路径中最后一个斜杠的位置
    int end = fileName.lastIndexOf("/");
    // 提取选中文件路径中的目录部分
    QString _path = fileName.left(end);
    // 将上次访问的路径保存到配置文件中
    pIniSet->setValue("/iapFilePath/path", _path);
    delete pIniSet;
    pIniSet = nullptr;

    QDataStream in(this->file);

    // 读取原始文件内容
    char *data = new char[this->file->size()];

    this->header.ih_size = this->file->size();
    // 用这种方式将文件内容写到QByteArray数组才不会丢失数据
    in.readRawData(data, this->file->size());

    QString str = "file.size:";
    ui->textFileInfo->append(str + QString::number(this->file->size()));

    fileParam.fileSize = this->file->size();
    qDebug() << "data.size:" << this->file->size();
    fileParam.fileDataBuff.append(data, this->file->size()); // 在数组末尾写入
    delete[] data;

    this->file->close();
}

