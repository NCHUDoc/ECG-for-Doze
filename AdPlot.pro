#-------------------------------------------------
#
# Project created by QtCreator 2014-01-24T11:24:30
#
#-------------------------------------------------

QT       += core gui

TARGET = AdPlot
TEMPLATE = app


SOURCES += main.cpp\
    so.cpp \
    Adplot.cpp \
    RRI_mean.cpp \
    resample.cpp \
    remove.cpp \
    PSD.cpp \
    determine.cpp

HEADERS  += adplot.h \
    define.h

FORMS    += adplot.ui

INCLUDEPATH += /usr/local/qwt-6.0.1/include
LIBS += -L "/usr/local/qwt-6.0.1/lib" -lqwt
QT       += phonon

