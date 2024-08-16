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

    watcher = new QFileSystemWatcher(this);

    loadIapFile();

    // 打开配置文件
    QString config_path = qApp->applicationDirPath() + "/config/Setting.ini";
    // 读配置文件信息
    QSettings *pIniSet = new QSettings(config_path, QSettings::IniFormat);
    // 读配置文件里的路径信息
    QString fileName = pIniSet->value("/iapFilePath/file").toString();

    if (!fileName.isEmpty()) {
        watcher->addPath(fileName);

        connect(watcher, &QFileSystemWatcher::fileChanged, this, &Iap::onFileChanged);
        connect(watcher, &QFileSystemWatcher::directoryChanged, this, &Iap::onDirectoryChanged);
    }
    delete pIniSet;

    connect(ui->pushButton_2, &QPushButton::clicked, this, &Iap::iapStart);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &Iap::open_file);
    connect(this, &Iap::iapError, this, &Iap::iapErrorHandle);
}

Iap::~Iap()
{
    delete watcher;
    qDebug()<<"iap结束";
}

void Iap::iapStart(void) {
    packCnt = 0;
    packDataLen = 0;
    cmdBuff.clear();
    endState = 0;
    fileParam.readFileOffset = 0;

    progressNum = 0;
    progressCnt = 0;
    ui->progressBar->setValue(progressNum);

    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_8->setEnabled(false);

    disconnect(mySerial, &QSerialPort::readyRead, this, &UserSerial::showData);
    connect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadData);

    // 发送握手信号
    QByteArray tx_buff("pbl+updata\r\n");
    qDebug()<<"已发送："<< tx_buff;
    mySerial->write(tx_buff);

    // 定时查询是否握手成功
    timerCheckHS = new QTimer(this);
    connect(timerCheckHS, &QTimer::timeout, this, &Iap::handShakeCheck);
    timerCheckHS->start(50);
}

void Iap::iapErrorHandle() {
    timerCheckHS->stop();
    connect(mySerial, &QSerialPort::readyRead, this, &UserSerial::showData);
    disconnect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadData);

    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_8->setEnabled(true);

    ui->progressBar->setValue(0);
    qDebug() << "错啦";
}

void Iap::handShakeCheck() {
    static quint8 hsNum = 0;
    if (transStep != 0) {
        disconnect(timerCheckHS, &QTimer::timeout, this, &Iap::handShakeCheck);
        timerCheckHS->stop();
        return;
    }
    hsNum++;
    if (hsNum >= 10) {
        disconnect(timerCheckHS, &QTimer::timeout, this, &Iap::handShakeCheck);
        emit iapError();
    }
    QByteArray tx_buff("pbl+updata\r\n");
    qDebug()<<"已发送："<< tx_buff;
    mySerial->write(tx_buff);
}

void Iap::waitCheck() {
    if (transWait == true) {
        emit iapError();
    }
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
                progressCnt = (fileParam.fileSize / packDataLen + 0.5);
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
        TransState state = sendDataHandle(rx_buff);
        if (state == IAP_TRANING) {
            transWait = false;
        } else if (state == IAP_WAIT) {
            transWait = true;
        } else if (state == IAP_COMPL) {
            transStep = 2;
        } else if (state == IAP_ERROR) {
            timerCheckHS->stop();
            emit iapError();
            qDebug() << "错啦1";
        }
    } break;

    case 0: {      
        TransState state = sendFileParamHandle(rx_buff);
        if (state == IAP_TRANING) {
            // transWait = false;
        } else if (state == IAP_WAIT) {
            // transWait = true;
        } else if (state == IAP_COMPL) {
            transStep = 1;
            connect(timerCheckHS, &QTimer::timeout, this, &Iap::waitCheck);
            timerCheckHS->start(200);
        } else if (state == IAP_ERROR) {
            timerCheckHS->stop();
            emit iapError();
            qDebug() << "错啦0";
        }
    } break;

    case 2: {
        TransState state = sendEndHandle(rx_buff);
        if (state == IAP_TRANING) {
            transWait = false;
        } else if (state == IAP_WAIT) {
            transWait = true;
        } else if (state == IAP_COMPL) {
            timerCheckHS->stop();

            connect(mySerial, &QSerialPort::readyRead, this, &UserSerial::showData);
            disconnect(mySerial, &QSerialPort::readyRead, this, &Iap::iapReadData);
            transStep = 0;

            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_8->setEnabled(true);

            mySerial->clear();
            mySerial->close();

            // 设置延时100毫秒后调用
            QTimer::singleShot(100, qApp, [this](){mySerial->open(QIODevice::ReadWrite);});
        } else if (state == IAP_ERROR) {
            timerCheckHS->stop();
            emit iapError();
            qDebug() << "错啦2";
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
            return IAP_WAIT;
        }
        step = 0;

        qDebug() << cmdBuff;
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
        return IAP_WAIT;
    }

    /* 收到下一帧数据请求 */
    if (cmdBuff.at(0) == ACK && cmdBuff.at(1) == C) {
        sendPack(STX, getPackData(&fileParam));
        // qDebug()<< "正常";
    } else if (byteArray.at(0) == NAK) {
        fileParam.readFileOffset -= packDataLen;
        sendPack(STX, getPackData(&fileParam));
    } else if (cmdBuff.at(0) == CA && cmdBuff.at(1) == CA) {
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
        // qDebug() << byteArray.toHex();
        for (int i = 0; i < byteArray.size(); i++) {
            if (byteArray.at(i) == ACK) {
                cmdBuff.append(byteArray.at(i));
            } else if (byteArray.at(i) == C) {
                cmdBuff.append(byteArray.at(i));
            }
        }
        if (cmdBuff.size() < 2) {
            return IAP_WAIT;
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
            return IAP_WAIT;
        }
        QByteArray endArray;
        quint8 startChar = EOT;

        endArray.append(startChar);
        mySerial->write(endArray);

        endState = 2;
    } break;

    case 2: {
        if (byteArray.at(0) != ACK) {
            return IAP_WAIT;
        }

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

    ui->progressBar->setValue(progressNum * 100 / progressCnt);
    progressNum++;
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
    QString lastFile = pIniSet->value("/iapFilePath/file").toString();

    if (lastPath.isEmpty()) {
        // 如果是空的，则用根目录
        lastPath = "./";
    }

    if (lastPath.isEmpty()) {
        // 如果是空的，则用根目录
        lastFile = "";
    }

    // 打开文件
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("打开文件"),
        lastPath, tr("bin files(*.bin);;hex files(*.hex);;All files (*.*)"));

    QFileInfo fileInfo(fileName);
    fileParam.fileName = fileInfo.fileName();
    fileParam.fileDataBuff.clear();

    QFile *currentFile = new QFile(fileName);

    // 不能以txt方式打开读写，不然会丢失\n等内容
    if (!currentFile->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open the source file.";
        return;
    }

    // 找到选中文件路径中最后一个斜杠的位置
    int end = fileName.lastIndexOf("/");
    // 提取选中文件路径中的目录部分
    QString _path = fileName.left(end);
    // 将上次访问的路径保存到配置文件中
    pIniSet->setValue("/iapFilePath/path", _path);
    pIniSet->setValue("/iapFilePath/file", fileName);
    delete pIniSet;
    pIniSet = nullptr;

    // 用于监控IAP文件变化
    watcher->addPath(fileName);
    disconnect(watcher, &QFileSystemWatcher::fileChanged, this, &Iap::onFileChanged);
    disconnect(watcher, &QFileSystemWatcher::directoryChanged, this, &Iap::onDirectoryChanged);
    connect(watcher, &QFileSystemWatcher::fileChanged, this, &Iap::onFileChanged);
    connect(watcher, &QFileSystemWatcher::directoryChanged, this, &Iap::onDirectoryChanged);

    QDataStream in(currentFile);

    // 读取原始文件内容
    char *data = new char[currentFile->size()];

    // 用这种方式将文件内容写到QByteArray数组才不会丢失数据
    in.readRawData(data, currentFile->size());

    fileParam.fileSize = currentFile->size();
    qDebug() << "data.size:" << currentFile->size();
    fileParam.fileDataBuff.append(data, currentFile->size()); // 在数组末尾写入
    delete[] data;

    currentFile->close();
    delete currentFile;
}

void Iap::onFileChanged() {
    qDebug() << "改了";
    loadIapFile();
}


void Iap::loadIapFile() {
    // 打开配置文件
    QString config_path = qApp->applicationDirPath() + "/config/Setting.ini";
    // 读配置文件信息
    QSettings *pIniSet = new QSettings(config_path, QSettings::IniFormat);
    // 读配置文件里的路径信息
    QString fileName = pIniSet->value("/iapFilePath/file").toString();
    QFile *loadFile = new QFile(fileName);

    QFileInfo fileInfo(fileName);
    fileParam.fileName = fileInfo.fileName();
    fileParam.fileDataBuff.clear();

    // 不能以txt方式打开读写，不然会丢失\n等内容
    if (!loadFile->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open the source file.";
        return;
    }

    QDataStream in(loadFile);

    // 读取原始文件内容
    char *data = new char[loadFile->size()];

    // 用这种方式将文件内容写到QByteArray数组才不会丢失数据
    in.readRawData(data, loadFile->size());

    fileParam.fileSize = loadFile->size();
    qDebug() << "data.size:" << loadFile->size();
    fileParam.fileDataBuff.append(data, loadFile->size()); // 在数组末尾写入
    delete[] data;

    loadFile->close();

    delete loadFile;
}

void Iap::onDirectoryChanged() {
    qDebug() << "没了";
}
