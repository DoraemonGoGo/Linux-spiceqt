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
    QByteArrayData data[14];
    char stringdata0[297];
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
QT_MOC_LITERAL(7, 119, 28), // "on_actionResize_to_triggered"
QT_MOC_LITERAL(8, 148, 28), // "on_actiontoolclose_triggered"
QT_MOC_LITERAL(9, 177, 28), // "on_action_usbredir_triggered"
QT_MOC_LITERAL(10, 206, 17), // "updateSpiceWindow"
QT_MOC_LITERAL(11, 224, 20), // "handleShortcutAction"
QT_MOC_LITERAL(12, 245, 21), // "on_action_1_triggered"
QT_MOC_LITERAL(13, 267, 29) // "on_actionFile_Input_triggered"

    },
    "SpiceMainWindow\0on_actionToolBar_toggled\0"
    "\0arg1\0on_actionFullscreen_triggered\0"
    "checked\0on_actiontoolfullscreen_triggered\0"
    "on_actionResize_to_triggered\0"
    "on_actiontoolclose_triggered\0"
    "on_action_usbredir_triggered\0"
    "updateSpiceWindow\0handleShortcutAction\0"
    "on_action_1_triggered\0"
    "on_actionFile_Input_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpiceMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       6,    0,   70,    2, 0x0a /* Public */,
       7,    0,   71,    2, 0x0a /* Public */,
       8,    0,   72,    2, 0x0a /* Public */,
       9,    0,   73,    2, 0x0a /* Public */,
      10,    0,   74,    2, 0x0a /* Public */,
      11,    0,   75,    2, 0x0a /* Public */,
      12,    0,   76,    2, 0x0a /* Public */,
      13,    0,   77,    2, 0x0a /* Public */,

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
        case 3: _t->on_actionResize_to_triggered(); break;
        case 4: _t->on_actiontoolclose_triggered(); break;
        case 5: _t->on_action_usbredir_triggered(); break;
        case 6: _t->updateSpiceWindow(); break;
        case 7: _t->handleShortcutAction(); break;
        case 8: _t->on_action_1_triggered(); break;
        case 9: _t->on_actionFile_Input_triggered(); break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
