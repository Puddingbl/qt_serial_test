#ifndef IAP_H
#define IAP_H

#include "userSerial.h"

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

    bool parseAndPrintFields(const QString &data);
    void sendFrame();

private:
    quint8 packCnt = 0;
    QByteArray fileDataBuff;
    int fileSize = 0;
    int startPosition = 0;
    int offset = 0;
    int packLen = 128;

    bool endFlag = false;

    int pack_cnt = 0;

    quint8 state = 0;
    QByteArray cmdBuff;

public slots:
    void iapStart(void);
    void iapReadCommParam(void);
    void iapReadData(void);
    void open_file(void);
    // void iapVB(void);

signals:

};


#endif // MYSERIAL_H
