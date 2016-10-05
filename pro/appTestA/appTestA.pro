QT = core

TEMPLATE = app

CONFIG += console

TARGET = AppTestA

MOC_DIR = build/moc
OBJECTS_DIR = build/obj
DESTDIR = build/bin

INCLUDEPATH += "../../src/appTestA/cpp/"

INCLUDEPATH += "../../src/logger/cpp/"
LIBS += "../logger/build/bin/libFiveCatsLogger.a"

HEADERS =
HEADERS += ../../src/appTestA/cpp/AppTestA.h

SOURCES =  ../../src/appTestA/cpp/main.cpp
SOURCES += ../../src/appTestA/cpp/AppTestA.cpp
