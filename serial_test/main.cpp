
// #include "widget.h"
#include <QApplication>


#include "userSerial.h"
#include "iap/iap.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w;
    // UserSerial w;
    Iap w;

    w.show();
    return a.exec();
}
