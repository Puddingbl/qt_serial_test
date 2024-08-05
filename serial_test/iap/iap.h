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


public slots:
    void iapStart(void);
    void iapReadCommParam(void);
    void iapReadData(void);

signals:

};


#endif // MYSERIAL_H
