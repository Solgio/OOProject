/****************************************************************************
** Meta object code from reading C++ file 'LibraryWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/View/LibraryWindow.h"
#include <QtGui/qtextcursor.h>
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
    "contentDataChanged",
    "",
    "importContent",
    "saveToFile",
    "extension",
    "updateContentDisplay",
    "showContentDetails",
    "QModelIndex",
    "index",
    "showAddContentDialog",
    "checked",
    "editContent",
    "Content*",
    "content",
    "hideDetailView",
    "applySearchFilter",
    "text",
    "applyFilters",
    "clearFilters",
    "clearSearch",
    "delayedSearch",
    "updateFilterCounter",
    "changeSortDirection"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13LibraryWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  116,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,  117,    2, 0x08,    2 /* Private */,
       4,    1,  118,    2, 0x08,    3 /* Private */,
       6,    0,  121,    2, 0x08,    5 /* Private */,
       7,    1,  122,    2, 0x08,    6 /* Private */,
      10,    1,  125,    2, 0x08,    8 /* Private */,
      10,    0,  128,    2, 0x28,   10 /* Private | MethodCloned */,
      12,    1,  129,    2, 0x08,   11 /* Private */,
      12,    0,  132,    2, 0x28,   13 /* Private | MethodCloned */,
      15,    0,  133,    2, 0x08,   14 /* Private */,
      16,    1,  134,    2, 0x08,   15 /* Private */,
      18,    0,  137,    2, 0x08,   17 /* Private */,
      19,    0,  138,    2, 0x08,   18 /* Private */,
      20,    0,  139,    2, 0x08,   19 /* Private */,
      21,    0,  140,    2, 0x08,   20 /* Private */,
      22,    0,  141,    2, 0x08,   21 /* Private */,
      23,    0,  142,    2, 0x08,   22 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

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
        // method 'contentDataChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'importContent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveToFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateContentDisplay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showContentDetails'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'showAddContentDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'showAddContentDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editContent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Content *, std::false_type>,
        // method 'editContent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hideDetailView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applySearchFilter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'applyFilters'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearFilters'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearSearch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'delayedSearch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateFilterCounter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeSortDirection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void LibraryWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LibraryWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->contentDataChanged(); break;
        case 1: _t->importContent(); break;
        case 2: _t->saveToFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->updateContentDisplay(); break;
        case 4: _t->showContentDetails((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 5: _t->showAddContentDialog((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->showAddContentDialog(); break;
        case 7: _t->editContent((*reinterpret_cast< std::add_pointer_t<Content*>>(_a[1]))); break;
        case 8: _t->editContent(); break;
        case 9: _t->hideDetailView(); break;
        case 10: _t->applySearchFilter((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->applyFilters(); break;
        case 12: _t->clearFilters(); break;
        case 13: _t->clearSearch(); break;
        case 14: _t->delayedSearch(); break;
        case 15: _t->updateFilterCounter(); break;
        case 16: _t->changeSortDirection(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (LibraryWindow::*)();
            if (_q_method_type _q_method = &LibraryWindow::contentDataChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void LibraryWindow::contentDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
