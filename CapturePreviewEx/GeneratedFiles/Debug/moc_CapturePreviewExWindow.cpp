/****************************************************************************
** Meta object code from reading C++ file 'CapturePreviewExWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CapturePreviewExWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CapturePreviewExWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CapturePreviewExWindow_t {
    QByteArrayData data[22];
    char stringdata0[385];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CapturePreviewExWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CapturePreviewExWindow_t qt_meta_stringdata_CapturePreviewExWindow = {
    {
QT_MOC_LITERAL(0, 0, 22), // "CapturePreviewExWindow"
QT_MOC_LITERAL(1, 23, 29), // "RefreshInputStreamDataMessage"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 4), // "flag"
QT_MOC_LITERAL(4, 59, 22), // "SelectVideoModeMessage"
QT_MOC_LITERAL(5, 82, 5), // "index"
QT_MOC_LITERAL(6, 88, 16), // "AddDeviceMessage"
QT_MOC_LITERAL(7, 105, 10), // "IDeckLink*"
QT_MOC_LITERAL(8, 116, 8), // "deckLink"
QT_MOC_LITERAL(9, 125, 19), // "RemoveDeviceMessage"
QT_MOC_LITERAL(10, 145, 29), // "ErrorRestartingCaptureMessage"
QT_MOC_LITERAL(11, 175, 19), // "OnNewDeviceSelected"
QT_MOC_LITERAL(12, 195, 20), // "OnStartStopBnClicked"
QT_MOC_LITERAL(13, 216, 7), // "OnClose"
QT_MOC_LITERAL(14, 224, 21), // "OnStartStopBnClicked2"
QT_MOC_LITERAL(15, 246, 21), // "OnStartStopBnClicked3"
QT_MOC_LITERAL(16, 268, 21), // "OnStartStopBnClicked4"
QT_MOC_LITERAL(17, 290, 24), // "OnRefreshInputStreamData"
QT_MOC_LITERAL(18, 315, 17), // "OnSelectVideoMode"
QT_MOC_LITERAL(19, 333, 11), // "OnAddDevice"
QT_MOC_LITERAL(20, 345, 14), // "OnRemoveDevice"
QT_MOC_LITERAL(21, 360, 24) // "OnErrorRestartingCapture"

    },
    "CapturePreviewExWindow\0"
    "RefreshInputStreamDataMessage\0\0flag\0"
    "SelectVideoModeMessage\0index\0"
    "AddDeviceMessage\0IDeckLink*\0deckLink\0"
    "RemoveDeviceMessage\0ErrorRestartingCaptureMessage\0"
    "OnNewDeviceSelected\0OnStartStopBnClicked\0"
    "OnClose\0OnStartStopBnClicked2\0"
    "OnStartStopBnClicked3\0OnStartStopBnClicked4\0"
    "OnRefreshInputStreamData\0OnSelectVideoMode\0"
    "OnAddDevice\0OnRemoveDevice\0"
    "OnErrorRestartingCapture"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CapturePreviewExWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       6,    1,  100,    2, 0x06 /* Public */,
       9,    1,  103,    2, 0x06 /* Public */,
      10,    0,  106,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  107,    2, 0x09 /* Protected */,
      12,    0,  108,    2, 0x09 /* Protected */,
      13,    0,  109,    2, 0x09 /* Protected */,
      14,    0,  110,    2, 0x09 /* Protected */,
      15,    0,  111,    2, 0x09 /* Protected */,
      16,    0,  112,    2, 0x09 /* Protected */,
      17,    1,  113,    2, 0x09 /* Protected */,
      18,    1,  116,    2, 0x09 /* Protected */,
      19,    1,  119,    2, 0x09 /* Protected */,
      20,    1,  122,    2, 0x09 /* Protected */,
      21,    0,  125,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::ULong,    3,
    QMetaType::Void, QMetaType::UInt,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULong,    3,
    QMetaType::Void, QMetaType::UInt,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void CapturePreviewExWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CapturePreviewExWindow *_t = static_cast<CapturePreviewExWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->RefreshInputStreamDataMessage((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 1: _t->SelectVideoModeMessage((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 2: _t->AddDeviceMessage((*reinterpret_cast< IDeckLink*(*)>(_a[1]))); break;
        case 3: _t->RemoveDeviceMessage((*reinterpret_cast< IDeckLink*(*)>(_a[1]))); break;
        case 4: _t->ErrorRestartingCaptureMessage(); break;
        case 5: _t->OnNewDeviceSelected(); break;
        case 6: _t->OnStartStopBnClicked(); break;
        case 7: _t->OnClose(); break;
        case 8: _t->OnStartStopBnClicked2(); break;
        case 9: _t->OnStartStopBnClicked3(); break;
        case 10: _t->OnStartStopBnClicked4(); break;
        case 11: _t->OnRefreshInputStreamData((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 12: _t->OnSelectVideoMode((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 13: _t->OnAddDevice((*reinterpret_cast< IDeckLink*(*)>(_a[1]))); break;
        case 14: _t->OnRemoveDevice((*reinterpret_cast< IDeckLink*(*)>(_a[1]))); break;
        case 15: _t->OnErrorRestartingCapture(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CapturePreviewExWindow::*_t)(unsigned long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturePreviewExWindow::RefreshInputStreamDataMessage)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CapturePreviewExWindow::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturePreviewExWindow::SelectVideoModeMessage)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CapturePreviewExWindow::*_t)(IDeckLink * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturePreviewExWindow::AddDeviceMessage)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CapturePreviewExWindow::*_t)(IDeckLink * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturePreviewExWindow::RemoveDeviceMessage)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CapturePreviewExWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturePreviewExWindow::ErrorRestartingCaptureMessage)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject CapturePreviewExWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CapturePreviewExWindow.data,
      qt_meta_data_CapturePreviewExWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CapturePreviewExWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CapturePreviewExWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CapturePreviewExWindow.stringdata0))
        return static_cast<void*>(const_cast< CapturePreviewExWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CapturePreviewExWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void CapturePreviewExWindow::RefreshInputStreamDataMessage(unsigned long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CapturePreviewExWindow::SelectVideoModeMessage(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CapturePreviewExWindow::AddDeviceMessage(IDeckLink * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CapturePreviewExWindow::RemoveDeviceMessage(IDeckLink * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CapturePreviewExWindow::ErrorRestartingCaptureMessage()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
