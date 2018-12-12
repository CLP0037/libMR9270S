#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T16:00:22
#
#-------------------------------------------------

QT       -= gui

TARGET = libMR9270S
TEMPLATE = lib

DEFINES += LIBMR9270S_LIBRARY

SOURCES += libmr9270s.cpp

HEADERS += libmr9270s.h\
        libmr9270s_global.h

win32:CONFIG(release, debug|release): DESTDIR =../lib/release
else:win32:CONFIG(debug, debug|release): DESTDIR =../lib/debug
else:unix:DESTDIR =../lib

win32{
HEADERS  += mainwindow.h \
    ../include/modbus.h \
    ../include/modbus-private.h \
    ../include/modbus-rtu.h \
    ../include/modbus-rtu-private.h \
    ../include/modbus-tcp.h \
    ../include/modbus-tcp-private.h \
    ../include/modbus-version.h
INCLUDEPATH += ../include
LIBS     += -Ldll -lws2_32
LIBS     += -L$$PWD/../lib/ -lmodbus

}
unix {
    HEADERS += /usr/include/modbus/modbus.h  \
               /usr/include/modbus/modbus-rtu.h  \
               /usr/include/modbus/modbus-tcp.h
    INCLUDEPATH += /usr/include/modbus
    LIBS += -L/usr/lib -lmodbus
}


unix {
    target.path = /usr/lib
    INSTALLS += target
}
