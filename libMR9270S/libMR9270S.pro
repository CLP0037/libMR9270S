#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T16:00:22
#
#-------------------------------------------------

QT       -= gui

include(gitversion.pri)

win32{
    TARGET = libMR9270S
}
TEMPLATE = lib
CONFIG += skip_target_version_ext
unix{
    TARGET = MR9270S  # auto add lib
    CONFIG += staticlib #编译选项，使用静态库staticlib，默认是动态库
}
DEFINES += LIBMR9270S_LIBRARY

SOURCES += libmr9270s.cpp

HEADERS += libmr9270s.h\
        libmr9270s_global.h

win32:CONFIG(release, debug|release): DESTDIR =../lib/release
else:win32:CONFIG(debug, debug|release): DESTDIR =../lib/debug
else:unix:DESTDIR =../lib_linux

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
#LIBS     += -Ldll -lws2_32
LIBS     += -L$$PWD/../lib/win/ -lws2_32
LIBS     += -L$$PWD/../lib/win/ -lmodbus

}
unix {
#https://github.com/stephane/libmodbus
#install automake, autoconf, libtool and a C compiler (gcc or clang) to compile the library and asciidoc and xmlto to generate the documentation (optional).
#./configure && make install. Run ./autogen.sh first to generate the configure script if required.
    HEADERS += /usr/local/include/modbus/modbus.h  \
               /usr/local/include/modbus/modbus-rtu.h  \
               /usr/local/include/modbus/modbus-tcp.h
    #
    # INCLUDEPATH += /usr/include/modbus
    # LIBS += -L/usr/lib -lmodbus
    # ubuntu
    INCLUDEPATH += /usr/local/include/modbus
    LIBS += -L/usr/local/lib -lmodbus
}


#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}

OTHER_FILES += gitversion.pri
