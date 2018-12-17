#-------------------------------------------------
#
# Project created by QtCreator 2018-12-12T14:35:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_libMR9270S
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
HEADERS  += ../libMR9270S/libmr9270s.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../include


unix {
    HEADERS += INCLUDEPATH += /usr/include/modbus
    #LIBS += -L/usr/lib -lmodbus
}
LIBS     += -L$$PWD/../lib/debug/ -llibMR9270S
#win32:CONFIG(release, debug|release): LIBS     += -L$$PWD/../lib/release/ -llibMR9270S
#else:win32:CONFIG(debug, debug|release): LIBS     += -L$$PWD/../lib/debug/ -llibMR9270S
#else:unix:LIBS     += -L$$PWD/../lib/ -llibMR9270S