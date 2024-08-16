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
    "iapError",
    "",
    "iapStart",
    "iapReadData",
    "open_file",
    "onFileChanged",
    "onDirectoryChanged",
    "iapErrorHandle"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSIapENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[4];
    char stringdata1[9];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[12];
    char stringdata5[10];
    char stringdata6[14];
    char stringdata7[19];
    char stringdata8[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSIapENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSIapENDCLASS_t qt_meta_stringdata_CLASSIapENDCLASS = {
    {
        QT_MOC_LITERAL(0, 3),  // "Iap"
        QT_MOC_LITERAL(4, 8),  // "iapError"
        QT_MOC_LITERAL(13, 0),  // ""
        QT_MOC_LITERAL(14, 8),  // "iapStart"
        QT_MOC_LITERAL(23, 11),  // "iapReadData"
        QT_MOC_LITERAL(35, 9),  // "open_file"
        QT_MOC_LITERAL(45, 13),  // "onFileChanged"
        QT_MOC_LITERAL(59, 18),  // "onDirectoryChanged"
        QT_MOC_LITERAL(78, 14)   // "iapErrorHandle"
    },
    "Iap",
    "iapError",
    "",
    "iapStart",
    "iapReadData",
    "open_file",
    "onFileChanged",
    "onDirectoryChanged",
    "iapErrorHandle"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSIapENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   57,    2, 0x0a,    2 /* Public */,
       4,    0,   58,    2, 0x0a,    3 /* Public */,
       5,    0,   59,    2, 0x0a,    4 /* Public */,
       6,    0,   60,    2, 0x0a,    5 /* Public */,
       7,    0,   61,    2, 0x0a,    6 /* Public */,
       8,    0,   62,    2, 0x0a,    7 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
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
        // method 'iapError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'iapStart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'iapReadData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'open_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFileChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDirectoryChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'iapErrorHandle'
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
        case 0: _t->iapError(); break;
        case 1: _t->iapStart(); break;
        case 2: _t->iapReadData(); break;
        case 3: _t->open_file(); break;
        case 4: _t->onFileChanged(); break;
        case 5: _t->onDirectoryChanged(); break;
        case 6: _t->iapErrorHandle(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Iap::*)();
            if (_t _q_method = &Iap::iapError; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
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
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Iap::iapError()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
