/****************************************************************************
** Meta object code from reading C++ file 'spicemainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../spice-client1/spicemainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spicemainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SpiceMainWindow_t {
    QByteArrayData data[20];
    char stringdata0[398];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpiceMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpiceMainWindow_t qt_meta_stringdata_SpiceMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SpiceMainWindow"
QT_MOC_LITERAL(1, 16, 24), // "on_actionToolBar_toggled"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 4), // "arg1"
QT_MOC_LITERAL(4, 47, 29), // "on_actionFullscreen_triggered"
QT_MOC_LITERAL(5, 77, 7), // "checked"
QT_MOC_LITERAL(6, 85, 33), // "on_actiontoolfullscreen_trigg..."
QT_MOC_LITERAL(7, 119, 28), // "on_actiontoolclose_triggered"
QT_MOC_LITERAL(8, 148, 17), // "updateSpiceWindow"
QT_MOC_LITERAL(9, 166, 20), // "handleShortcutAction"
QT_MOC_LITERAL(10, 187, 21), // "on_action_1_triggered"
QT_MOC_LITERAL(11, 209, 29), // "on_actionFile_input_triggered"
QT_MOC_LITERAL(12, 239, 31), // "on_actionmulti_screen_triggered"
QT_MOC_LITERAL(13, 271, 20), // "addDisplay_triggered"
QT_MOC_LITERAL(14, 292, 16), // "onUsbDeviceAdded"
QT_MOC_LITERAL(15, 309, 11), // "description"
QT_MOC_LITERAL(16, 321, 18), // "onUsbDeviceRemoved"
QT_MOC_LITERAL(17, 340, 28), // "on_action_usbredir_triggered"
QT_MOC_LITERAL(18, 369, 20), // "disconnectUsbDevices"
QT_MOC_LITERAL(19, 390, 7) // "devices"

    },
    "SpiceMainWindow\0on_actionToolBar_toggled\0"
    "\0arg1\0on_actionFullscreen_triggered\0"
    "checked\0on_actiontoolfullscreen_triggered\0"
    "on_actiontoolclose_triggered\0"
    "updateSpiceWindow\0handleShortcutAction\0"
    "on_action_1_triggered\0"
    "on_actionFile_input_triggered\0"
    "on_actionmulti_screen_triggered\0"
    "addDisplay_triggered\0onUsbDeviceAdded\0"
    "description\0onUsbDeviceRemoved\0"
    "on_action_usbredir_triggered\0"
    "disconnectUsbDevices\0devices"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpiceMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x0a /* Public */,
       4,    1,   87,    2, 0x0a /* Public */,
       6,    0,   90,    2, 0x0a /* Public */,
       7,    0,   91,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x0a /* Public */,
       9,    0,   93,    2, 0x0a /* Public */,
      10,    0,   94,    2, 0x0a /* Public */,
      11,    0,   95,    2, 0x0a /* Public */,
      12,    0,   96,    2, 0x0a /* Public */,
      13,    0,   97,    2, 0x0a /* Public */,
      14,    1,   98,    2, 0x0a /* Public */,
      16,    1,  101,    2, 0x0a /* Public */,
      17,    0,  104,    2, 0x0a /* Public */,
      18,    1,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   19,

       0        // eod
};

void SpiceMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SpiceMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionToolBar_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_actionFullscreen_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_actiontoolfullscreen_triggered(); break;
        case 3: _t->on_actiontoolclose_triggered(); break;
        case 4: _t->updateSpiceWindow(); break;
        case 5: _t->handleShortcutAction(); break;
        case 6: _t->on_action_1_triggered(); break;
        case 7: _t->on_actionFile_input_triggered(); break;
        case 8: _t->on_actionmulti_screen_triggered(); break;
        case 9: _t->addDisplay_triggered(); break;
        case 10: _t->onUsbDeviceAdded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->onUsbDeviceRemoved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_action_usbredir_triggered(); break;
        case 13: _t->disconnectUsbDevices((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SpiceMainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_SpiceMainWindow.data,
    qt_meta_data_SpiceMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SpiceMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpiceMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpiceMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SpiceMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
