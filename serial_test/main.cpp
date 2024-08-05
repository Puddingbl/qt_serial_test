
// #include "widget.h"
#include <QApplication>


#include "userSerial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w;
    userSerial w;
    w.show();
    return a.exec();
}
