/****************************************************************************
** Meta object code from reading C++ file 'findandsignupwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "findandsignupwidget.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'findandsignupwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
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
struct qt_meta_stringdata_CLASSFindAndSignUpWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFindAndSignUpWidgetENDCLASS = QtMocHelpers::stringData(
    "FindAndSignUpWidget",
    "onEnterKeyPushButtonclicked",
    "",
    "onEnterPushButtonclicked",
    "onShowPassword1clicked",
    "onShowPassword2clicked",
    "onHidePassword1clicked",
    "onHidePassword2clicked",
    "onSendKeyPushButtonclicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFindAndSignUpWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    0,   57,    2, 0x08,    2 /* Private */,
       4,    0,   58,    2, 0x08,    3 /* Private */,
       5,    0,   59,    2, 0x08,    4 /* Private */,
       6,    0,   60,    2, 0x08,    5 /* Private */,
       7,    0,   61,    2, 0x08,    6 /* Private */,
       8,    0,   62,    2, 0x08,    7 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FindAndSignUpWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSFindAndSignUpWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFindAndSignUpWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFindAndSignUpWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FindAndSignUpWidget, std::true_type>,
        // method 'onEnterKeyPushButtonclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEnterPushButtonclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onShowPassword1clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onShowPassword2clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onHidePassword1clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onHidePassword2clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSendKeyPushButtonclicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FindAndSignUpWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FindAndSignUpWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onEnterKeyPushButtonclicked(); break;
        case 1: _t->onEnterPushButtonclicked(); break;
        case 2: _t->onShowPassword1clicked(); break;
        case 3: _t->onShowPassword2clicked(); break;
        case 4: _t->onHidePassword1clicked(); break;
        case 5: _t->onHidePassword2clicked(); break;
        case 6: _t->onSendKeyPushButtonclicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *FindAndSignUpWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FindAndSignUpWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFindAndSignUpWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FindAndSignUpWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP