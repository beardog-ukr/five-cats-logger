QT += core
QT += testlib

TEMPLATE = app

CONFIG += console

TARGET = loggerTest

MOC_DIR = build/moc
OBJECTS_DIR = build/obj
DESTDIR = build/bin

INCLUDEPATH += "../../src/logger/cpp/"
LIBS += ../logger/build/bin/libFiveCatsLogger.a

HEADERS =
HEADERS += ../../src/loggerTest/cpp/TestFiveCatsLogger.h

SOURCES =  ../../src/loggerTest/cpp/TestMain.cpp
SOURCES += ../../src/loggerTest/cpp/TestFiveCatsLogger.cpp
SOURCES += ../../src/loggerTest/cpp/TestFiveCatsLoggerLevels.cpp
