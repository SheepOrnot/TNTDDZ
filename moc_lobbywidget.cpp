/****************************************************************************
** Meta object code from reading C++ file 'lobbywidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lobbywidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lobbywidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSLobbyWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSLobbyWidgetENDCLASS = QtMocHelpers::stringData(
    "LobbyWidget",
    "ChangeResolutions",
    "",
    "_Width",
    "_Height",
    "ResolutionChanged",
    "Transform_To_String",
    "Num",
    "onSettingBtnClicked",
    "onClassicModeBtnClicked",
    "onJoinRoomBtnClicked",
    "onExitGameBtnClicked",
    "onPersonalInfoBtnClicked",
    "RollImage",
    "onSingleModeBtnClicked",
    "onDiamondShopClicked",
    "onBeanShopClicked",
    "onRuleBtnClicked",
    "EnterGame",
    "doInfoInit",
    "doExitRoom"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSLobbyWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  110,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    2,  115,    2, 0x0a,    4 /* Public */,
       6,    1,  120,    2, 0x0a,    7 /* Public */,
       8,    0,  123,    2, 0x08,    9 /* Private */,
       9,    0,  124,    2, 0x08,   10 /* Private */,
      10,    0,  125,    2, 0x08,   11 /* Private */,
      11,    0,  126,    2, 0x08,   12 /* Private */,
      12,    0,  127,    2, 0x08,   13 /* Private */,
      13,    0,  128,    2, 0x08,   14 /* Private */,
      14,    0,  129,    2, 0x08,   15 /* Private */,
      15,    0,  130,    2, 0x08,   16 /* Private */,
      16,    0,  131,    2, 0x08,   17 /* Private */,
      17,    0,  132,    2, 0x08,   18 /* Private */,
      18,    0,  133,    2, 0x08,   19 /* Private */,
      19,    0,  134,    2, 0x08,   20 /* Private */,
      20,    0,  135,    2, 0x08,   21 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::QString, QMetaType::LongLong,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

Q_CONSTINIT const QMetaObject LobbyWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSLobbyWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSLobbyWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSLobbyWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LobbyWidget, std::true_type>,
        // method 'ChangeResolutions'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'ResolutionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'Transform_To_String'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<long long, std::false_type>,
        // method 'onSettingBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClassicModeBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onJoinRoomBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onExitGameBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPersonalInfoBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'RollImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSingleModeBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDiamondShopClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBeanShopClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRuleBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'EnterGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doInfoInit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doExitRoom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void LobbyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LobbyWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ChangeResolutions((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->ResolutionChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: { QString _r = _t->Transform_To_String((*reinterpret_cast< std::add_pointer_t<qlonglong>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->onSettingBtnClicked(); break;
        case 4: _t->onClassicModeBtnClicked(); break;
        case 5: _t->onJoinRoomBtnClicked(); break;
        case 6: _t->onExitGameBtnClicked(); break;
        case 7: _t->onPersonalInfoBtnClicked(); break;
        case 8: _t->RollImage(); break;
        case 9: _t->onSingleModeBtnClicked(); break;
        case 10: _t->onDiamondShopClicked(); break;
        case 11: _t->onBeanShopClicked(); break;
        case 12: _t->onRuleBtnClicked(); break;
        case 13: _t->EnterGame(); break;
        case 14: _t->doInfoInit(); break;
        case 15: _t->doExitRoom(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LobbyWidget::*)(int , int );
            if (_t _q_method = &LobbyWidget::ChangeResolutions; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *LobbyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LobbyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSLobbyWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LobbyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void LobbyWidget::ChangeResolutions(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
