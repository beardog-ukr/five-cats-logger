QT += core

TEMPLATE = app

CONFIG += console

TARGET = demoApp

MOC_DIR = build/moc
OBJECTS_DIR = build/obj
DESTDIR = build/bin

INCLUDEPATH += "../../src/logger/cpp/"
LIBS += ../logger/build/bin/libFiveCatsLogger.a

HEADERS =
HEADERS += ../../src/demoApp/cpp/DemoApp.h

SOURCES =  ../../src/demoApp/cpp/main.cpp
SOURCES += ../../src/demoApp/cpp/DemoApp.cpp
