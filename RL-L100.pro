#-------------------------------------------------
#
# Project created by QtCreator 2018-05-29T14:07:28
#
#-------------------------------------------------

QT       += core gui serialport
QT       += printsupport
QT       += gui

#QT       += qaxcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RL-L100_FILLING
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        Qcustomplot/qcustomplot.cpp \
    Log/Log.cpp \
    common/CRC16.c \
    editsize.cpp

HEADERS += \
        Qcustomplot/qcustomplot.h \
        mainwindow.h \
    Log/Log.h \
    command.h \
    common/Common.h \
    common/CRC16.h \
    editsize.h

FORMS += \
        mainwindow.ui \
    editsize.ui
INCLUDEPATH += Qcustomplot/

TRANSLATIONS += i18n/Lidar_fr.ts \
        i18n/Lidar_en.ts \
        i18n/Lidar_ja.ts \
        i18n/Lidar_zh.ts

RESOURCES += \
    translations.qrc \
    ver.qrc
RC_ICONS +=Image/realy.ico
