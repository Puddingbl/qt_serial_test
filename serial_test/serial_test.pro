QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 引入串口工程类型
QT += serialport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AES/qaesencryption.cpp \
    crc.cpp \
    main.cpp \
    myserial.cpp \
    widget.cpp

HEADERS += \
    AES/aesni/aesni-enc-cbc.h \
    AES/aesni/aesni-enc-ecb.h \
    AES/aesni/aesni-key-exp.h \
    AES/aesni/aesni-key-init.h \
    AES/qaesencryption.h \
    crc.h \
    myserial.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
