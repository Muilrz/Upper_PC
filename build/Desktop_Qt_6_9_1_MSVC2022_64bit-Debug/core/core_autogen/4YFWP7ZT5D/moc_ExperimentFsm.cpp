/****************************************************************************
** Meta object code from reading C++ file 'ExperimentFsm.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../core/fsm/ExperimentFsm.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExperimentFsm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
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
struct qt_meta_tag_ZN13ExperimentFsmE_t {};
} // unnamed namespace

template <> constexpr inline auto ExperimentFsm::qt_create_metaobjectdata<qt_meta_tag_ZN13ExperimentFsmE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ExperimentFsm",
        "requestScanStart",
        "",
        "requestScanPause",
        "requestScanResume",
        "requestScanStop",
        "requestReset",
        "sigConnected",
        "userStart",
        "userPause",
        "userContinue",
        "userStop",
        "userReset"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'requestScanStart'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'requestScanPause'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'requestScanResume'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'requestScanStop'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'requestReset'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sigConnected'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'userStart'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'userPause'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'userContinue'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'userStop'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'userReset'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ExperimentFsm, qt_meta_tag_ZN13ExperimentFsmE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ExperimentFsm::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ExperimentFsmE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ExperimentFsmE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13ExperimentFsmE_t>.metaTypes,
    nullptr
} };

void ExperimentFsm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ExperimentFsm *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->requestScanStart(); break;
        case 1: _t->requestScanPause(); break;
        case 2: _t->requestScanResume(); break;
        case 3: _t->requestScanStop(); break;
        case 4: _t->requestReset(); break;
        case 5: _t->sigConnected(); break;
        case 6: _t->userStart(); break;
        case 7: _t->userPause(); break;
        case 8: _t->userContinue(); break;
        case 9: _t->userStop(); break;
        case 10: _t->userReset(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ExperimentFsm::*)()>(_a, &ExperimentFsm::requestScanStart, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExperimentFsm::*)()>(_a, &ExperimentFsm::requestScanPause, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExperimentFsm::*)()>(_a, &ExperimentFsm::requestScanResume, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExperimentFsm::*)()>(_a, &ExperimentFsm::requestScanStop, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExperimentFsm::*)()>(_a, &ExperimentFsm::requestReset, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ExperimentFsm::*)()>(_a, &ExperimentFsm::sigConnected, 5))
            return;
    }
}

const QMetaObject *ExperimentFsm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExperimentFsm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13ExperimentFsmE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ExperimentFsm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ExperimentFsm::requestScanStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ExperimentFsm::requestScanPause()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ExperimentFsm::requestScanResume()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ExperimentFsm::requestScanStop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ExperimentFsm::requestReset()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ExperimentFsm::sigConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
