/****************************************************************************
** Meta object code from reading C++ file 'HTTPProvider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HTTPProvider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HTTPProvider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HTTPProvider_t {
    QByteArrayData data[12];
    char stringdata[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HTTPProvider_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HTTPProvider_t qt_meta_stringdata_HTTPProvider = {
    {
QT_MOC_LITERAL(0, 0, 12), // "HTTPProvider"
QT_MOC_LITERAL(1, 13, 8), // "finished"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "readyRead"
QT_MOC_LITERAL(4, 33, 12), // "errorOccured"
QT_MOC_LITERAL(5, 46, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(6, 74, 3), // "err"
QT_MOC_LITERAL(7, 78, 16), // "transferFinished"
QT_MOC_LITERAL(8, 95, 11), // "endOfThread"
QT_MOC_LITERAL(9, 107, 21), // "disconnectFromBrowser"
QT_MOC_LITERAL(10, 129, 16), // "writeReplyHeader"
QT_MOC_LITERAL(11, 146, 12) // "checkTimeout"

    },
    "HTTPProvider\0finished\0\0readyRead\0"
    "errorOccured\0QNetworkReply::NetworkError\0"
    "err\0transferFinished\0endOfThread\0"
    "disconnectFromBrowser\0writeReplyHeader\0"
    "checkTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HTTPProvider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x0a /* Public */,
       4,    1,   56,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,
      10,    0,   62,    2, 0x0a /* Public */,
      11,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HTTPProvider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HTTPProvider *_t = static_cast<HTTPProvider *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: { bool _r = _t->readyRead();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->errorOccured((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 3: _t->transferFinished(); break;
        case 4: _t->endOfThread(); break;
        case 5: _t->disconnectFromBrowser(); break;
        case 6: _t->writeReplyHeader(); break;
        case 7: _t->checkTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HTTPProvider::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HTTPProvider::finished)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject HTTPProvider::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HTTPProvider.data,
      qt_meta_data_HTTPProvider,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HTTPProvider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HTTPProvider::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HTTPProvider.stringdata))
        return static_cast<void*>(const_cast< HTTPProvider*>(this));
    return QObject::qt_metacast(_clname);
}

int HTTPProvider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void HTTPProvider::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
