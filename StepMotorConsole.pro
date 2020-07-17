#-------------------------------------------------
#
# Project created by QtCreator 2020-06-23T16:13:43
#
#-------------------------------------------------

QT       += core gui serialport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StepMotorConsole
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#LIBS += ./GaugeCarPlugin.lib ./AngleGaugePlugin.lib
INCLUDEPATH += $$PWD/include ../AngleGauge ../GaugeCar

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        ../GaugeCar/GaugeCar.cpp \
        ../AngleGauge/AngleGauge.cpp \
        slavethread.cpp

HEADERS += \
        mainwindow.h \
        ../GaugeCar/GaugeCar.h \
        ../AngleGauge/AngleGauge.h \
        slavethread.h

TRANSLATIONS += StepMotorConsole.ts

FORMS += \
        mainwindow.ui

RESOURCES += \
    stepmotorconsole.qrc

OTHER_FILES += myapp.rc

RC_FILE += myapp.rc

DISTFILES += \
    stepmotor.xml
