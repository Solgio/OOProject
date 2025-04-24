/****************************************************************************
** Meta object code from reading C++ file 'LibraryWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/View/LibraryWindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LibraryWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
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
struct qt_meta_tag_ZN13LibraryWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13LibraryWindowE = QtMocHelpers::stringData(
    "LibraryWindow",
    "importContent",
    "",
    "saveToFile",
    "extension",
    "updateContentDisplay",
    "showContentDetails",
    "QListWidgetItem*",
    "item",
    "editContentTriggered",
    "checked",
    "editContent",
    "Content*",
    "content",
    "hideDetailView",
    "onFilterChanged",
    "index"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13LibraryWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x08,    1 /* Private */,
       3,    1,   75,    2, 0x08,    2 /* Private */,
       5,    0,   78,    2, 0x08,    4 /* Private */,
       6,    1,   79,    2, 0x08,    5 /* Private */,
       9,    1,   82,    2, 0x08,    7 /* Private */,
       9,    0,   85,    2, 0x28,    9 /* Private | MethodCloned */,
      11,    1,   86,    2, 0x08,   10 /* Private */,
      11,    0,   89,    2, 0x28,   12 /* Private | MethodCloned */,
      14,    0,   90,    2, 0x08,   13 /* Private */,
      15,    1,   91,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,

       0        // eod
};

Q_CONSTINIT const QMetaObject LibraryWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN13LibraryWindowE.offsetsAndSizes,
    qt_meta_data_ZN13LibraryWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13LibraryWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LibraryWindow, std::true_type>,
        // method 'importContent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveToFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateContentDisplay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showContentDetails'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'editContentTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'editContentTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editContent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Content *, std::false_type>,
        // method 'editContent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hideDetailView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFilterChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void LibraryWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LibraryWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->importContent(); break;
        case 1: _t->saveToFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->updateContentDisplay(); break;
        case 3: _t->showContentDetails((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 4: _t->editContentTriggered((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->editContentTriggered(); break;
        case 6: _t->editContent((*reinterpret_cast< std::add_pointer_t<Content*>>(_a[1]))); break;
        case 7: _t->editContent(); break;
        case 8: _t->hideDetailView(); break;
        case 9: _t->onFilterChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *LibraryWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LibraryWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13LibraryWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int LibraryWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
