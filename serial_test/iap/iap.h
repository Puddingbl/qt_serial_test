#ifndef IAP_H
#define IAP_H

#include "userSerial.h"


class Iap : public UserSerial
{
    Q_OBJECT

public:
    explicit Iap(Widget *parent = nullptr);
    ~Iap();

    bool parseAndPrintFields(const QString &data);
private:
    quint8 packCnt = 0;
    QByteArray fileDataBuff;
    int fileSize = 0;
    int startPosition = 0;
    int offset = 0;
    int packLen = 128;

    bool endFlag = false;

    int pack_cnt = 0;


public slots:
    void iapStart(void);
    void iapReadCommParam(void);
    void iapReadData(void);
    void open_file(void);
    void iapVB(void);

signals:

};


#endif // MYSERIAL_H
