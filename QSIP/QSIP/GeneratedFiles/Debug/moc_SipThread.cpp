/****************************************************************************
** Meta object code from reading C++ file 'SipThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SipThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SipThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SipThread_t {
    QByteArrayData data[8];
    char stringdata[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SipThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SipThread_t qt_meta_stringdata_SipThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SipThread"
QT_MOC_LITERAL(1, 10, 11), // "Label_Staut"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "Label_Reg"
QT_MOC_LITERAL(4, 33, 11), // "Button_Dial"
QT_MOC_LITERAL(5, 45, 10), // "Button_Reg"
QT_MOC_LITERAL(6, 56, 12), // "Button_Unreg"
QT_MOC_LITERAL(7, 69, 11) // "Button_Hang"

    },
    "SipThread\0Label_Staut\0\0Label_Reg\0"
    "Button_Dial\0Button_Reg\0Button_Unreg\0"
    "Button_Hang"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SipThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    1,   47,    2, 0x06 /* Public */,
       4,    1,   50,    2, 0x06 /* Public */,
       5,    1,   53,    2, 0x06 /* Public */,
       6,    1,   56,    2, 0x06 /* Public */,
       7,    1,   59,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void SipThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SipThread *_t = static_cast<SipThread *>(_o);
        switch (_id) {
        case 0: _t->Label_Staut((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->Label_Reg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->Button_Dial((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->Button_Reg((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->Button_Unreg((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->Button_Hang((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SipThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SipThread::Label_Staut)) {
                *result = 0;
            }
        }
        {
            typedef void (SipThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SipThread::Label_Reg)) {
                *result = 1;
            }
        }
        {
            typedef void (SipThread::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SipThread::Button_Dial)) {
                *result = 2;
            }
        }
        {
            typedef void (SipThread::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SipThread::Button_Reg)) {
                *result = 3;
            }
        }
        {
            typedef void (SipThread::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SipThread::Button_Unreg)) {
                *result = 4;
            }
        }
        {
            typedef void (SipThread::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SipThread::Button_Hang)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject SipThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SipThread.data,
      qt_meta_data_SipThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SipThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SipThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SipThread.stringdata))
        return static_cast<void*>(const_cast< SipThread*>(this));
    return QThread::qt_metacast(_clname);
}

int SipThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SipThread::Label_Staut(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SipThread::Label_Reg(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SipThread::Button_Dial(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SipThread::Button_Reg(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SipThread::Button_Unreg(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SipThread::Button_Hang(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
