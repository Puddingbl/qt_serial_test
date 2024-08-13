/****************************************************************************
** Meta object code from reading C++ file 'iap.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../serial_test/iap/iap.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iap.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSIapENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSIapENDCLASS = QtMocHelpers::stringData(
    "Iap",
    "iapStart",
    "",
    "iapReadCommParam",
    "iapReadData",
    "open_file",
    "iapVB"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSIapENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[4];
    char stringdata1[9];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[12];
    char stringdata5[10];
    char stringdata6[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSIapENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSIapENDCLASS_t qt_meta_stringdata_CLASSIapENDCLASS = {
    {
        QT_MOC_LITERAL(0, 3),  // "Iap"
        QT_MOC_LITERAL(4, 8),  // "iapStart"
        QT_MOC_LITERAL(13, 0),  // ""
        QT_MOC_LITERAL(14, 16),  // "iapReadCommParam"
        QT_MOC_LITERAL(31, 11),  // "iapReadData"
        QT_MOC_LITERAL(43, 9),  // "open_file"
        QT_MOC_LITERAL(53, 5)   // "iapVB"
    },
    "Iap",
    "iapStart",
    "",
    "iapReadCommParam",
    "iapReadData",
    "open_file",
    "iapVB"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSIapENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x0a,    1 /* Public */,
       3,    0,   45,    2, 0x0a,    2 /* Public */,
       4,    0,   46,    2, 0x0a,    3 /* Public */,
       5,    0,   47,    2, 0x0a,    4 /* Public */,
       6,    0,   48,    2, 0x0a,    5 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Iap::staticMetaObject = { {
    QMetaObject::SuperData::link<UserSerial::staticMetaObject>(),
    qt_meta_stringdata_CLASSIapENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSIapENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSIapENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Iap, std::true_type>,
        // method 'iapStart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'iapReadCommParam'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'iapReadData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'open_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'iapVB'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Iap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Iap *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->iapStart(); break;
        case 1: _t->iapReadCommParam(); break;
        case 2: _t->iapReadData(); break;
        case 3: _t->open_file(); break;
        case 4: _t->iapVB(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Iap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Iap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSIapENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return UserSerial::qt_metacast(_clname);
}

int Iap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UserSerial::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
