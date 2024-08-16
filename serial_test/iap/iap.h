#ifndef IAP_H
#define IAP_H

#include "userSerial.h"
#include <QFileSystemWatcher>

#define SOH                     (0x01)  /* start of 128-byte data packet */
#define STX                     (0x02)  /* start of 1024-byte data packet */
#define EOT                     (0x04)  /* end of transmission */
#define ACK                     (0x06)  /* acknowledge */
#define NAK                     (0x15)  /* negative acknowledge */
#define CA                      (0x18)  /* two of these in succession aborts transfer, 上位机或下位机连续发两个CA则表示停止传输 */
#define C                       (0x43)  /* 'C' == 0x43, request command */


class Iap : public UserSerial
{
    Q_OBJECT

public:
    explicit Iap(Widget *parent = nullptr);
    ~Iap();

    typedef enum {
        IAP_TRANING = 0,
        IAP_COMPL,
        IAP_ERROR
    } TransState;

    struct iapFileParam {
        QString fileName;
        int fileSize;
        int readFileOffset;
        QByteArray fileDataBuff;
    };

    TransState sendFileParamHandle(QByteArray byteArray);
    TransState sendDataHandle(QByteArray byteArray);
    TransState sendEndHandle(QByteArray byteArray);

    bool parseAndPrintFields(const QString &data);
    void sendPack(quint8 cmd, QByteArray packData);

    QByteArray getPackData(struct iapFileParam *fileParam);
    QByteArray getFileInfo();
    int iapPackCheck(QByteArray byteArray);

private:
    quint8 packCnt = 0;
    int packDataLen = 128;

    struct iapFileParam fileParam;
    QByteArray cmdBuff;
    quint8 endState = 0;

    int pack_cnt = 0; // 调试用的参数，不重要

public slots:
    void iapStart(void);
    void iapReadData(void);
    void open_file(void);

    void onFileChanged();
    void onDirectoryChanged();
signals:

};


#endif // MYSERIAL_H
