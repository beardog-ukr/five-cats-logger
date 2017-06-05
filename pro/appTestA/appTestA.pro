QT = core

TEMPLATE = app

CONFIG += console

TARGET = AppTestA

MOC_DIR = build/moc
OBJECTS_DIR = build/obj
DESTDIR = build/bin

QMAKE_CXXFLAGS += "-std=c++11"

INCLUDEPATH += "../../src/appTestA/cpp/"

INCLUDEPATH += "../../src/logger/cpp/"
LIBS += "../logger/build/bin/libFiveCatsLogger.a"

HEADERS =
HEADERS += ../../src/appTestA/cpp/AppTestA.h
HEADERS += ../../src/appTestA/cpp/Functions.h

SOURCES =  ../../src/appTestA/cpp/main.cpp
SOURCES += ../../src/appTestA/cpp/AppTestA.cpp
SOURCES += ../../src/appTestA/cpp/Functions.cpp
