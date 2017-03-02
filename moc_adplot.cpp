/****************************************************************************
** Meta object code from reading C++ file 'adplot.h'
**
** Created: Wed May 14 18:13:26 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "adplot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AdPlot[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      22,    7,    7,    7, 0x0a,
      37,    7,    7,    7, 0x0a,
      54,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AdPlot[] = {
    "AdPlot\0\0plotAdCurve()\0plotPsdCurve()\0"
    "plotRatioCurve()\0start()\0"
};

void AdPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AdPlot *_t = static_cast<AdPlot *>(_o);
        switch (_id) {
        case 0: _t->plotAdCurve(); break;
        case 1: _t->plotPsdCurve(); break;
        case 2: _t->plotRatioCurve(); break;
        case 3: _t->start(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AdPlot::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AdPlot::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AdPlot,
      qt_meta_data_AdPlot, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AdPlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AdPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AdPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AdPlot))
        return static_cast<void*>(const_cast< AdPlot*>(this));
    return QWidget::qt_metacast(_clname);
}

int AdPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
