/****************************************************************************
** Meta object code from reading C++ file 'myserial.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../serial_test/myserial.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myserial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMySerialENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMySerialENDCLASS = QtMocHelpers::stringData(
    "MySerial",
    "onOpenCloseButtonClicked",
    "",
    "setBaudRate",
    "setPortName",
    "setStopBits",
    "setDataBits",
    "setParity",
    "sendData",
    "showData",
    "clearTx",
    "clearRx"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMySerialENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[9];
    char stringdata1[25];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[12];
    char stringdata5[12];
    char stringdata6[12];
    char stringdata7[10];
    char stringdata8[9];
    char stringdata9[9];
    char stringdata10[8];
    char stringdata11[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMySerialENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMySerialENDCLASS_t qt_meta_stringdata_CLASSMySerialENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "MySerial"
        QT_MOC_LITERAL(9, 24),  // "onOpenCloseButtonClicked"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 11),  // "setBaudRate"
        QT_MOC_LITERAL(47, 11),  // "setPortName"
        QT_MOC_LITERAL(59, 11),  // "setStopBits"
        QT_MOC_LITERAL(71, 11),  // "setDataBits"
        QT_MOC_LITERAL(83, 9),  // "setParity"
        QT_MOC_LITERAL(93, 8),  // "sendData"
        QT_MOC_LITERAL(102, 8),  // "showData"
        QT_MOC_LITERAL(111, 7),  // "clearTx"
        QT_MOC_LITERAL(119, 7)   // "clearRx"
    },
    "MySerial",
    "onOpenCloseButtonClicked",
    "",
    "setBaudRate",
    "setPortName",
    "setStopBits",
    "setDataBits",
    "setParity",
    "sendData",
    "showData",
    "clearTx",
    "clearRx"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMySerialENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x0a,    1 /* Public */,
       3,    0,   75,    2, 0x0a,    2 /* Public */,
       4,    0,   76,    2, 0x0a,    3 /* Public */,
       5,    0,   77,    2, 0x0a,    4 /* Public */,
       6,    0,   78,    2, 0x0a,    5 /* Public */,
       7,    0,   79,    2, 0x0a,    6 /* Public */,
       8,    0,   80,    2, 0x0a,    7 /* Public */,
       9,    0,   81,    2, 0x0a,    8 /* Public */,
      10,    0,   82,    2, 0x0a,    9 /* Public */,
      11,    0,   83,    2, 0x0a,   10 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MySerial::staticMetaObject = { {
    QMetaObject::SuperData::link<Widget::staticMetaObject>(),
    qt_meta_stringdata_CLASSMySerialENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMySerialENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMySerialENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MySerial, std::true_type>,
        // method 'onOpenCloseButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setBaudRate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setPortName'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setStopBits'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setDataBits'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setParity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearTx'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearRx'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MySerial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MySerial *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onOpenCloseButtonClicked(); break;
        case 1: _t->setBaudRate(); break;
        case 2: _t->setPortName(); break;
        case 3: _t->setStopBits(); break;
        case 4: _t->setDataBits(); break;
        case 5: _t->setParity(); break;
        case 6: _t->sendData(); break;
        case 7: _t->showData(); break;
        case 8: _t->clearTx(); break;
        case 9: _t->clearRx(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *MySerial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MySerial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMySerialENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int MySerial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
