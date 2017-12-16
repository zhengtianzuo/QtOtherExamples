#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += main.cpp

INCLUDEPATH += $$PWD/zlib

win32{
LIBS += -L$$PWD/zlib -lzlib
}

unix{
LIBS += -L$$PWD/zlib -lz
}
