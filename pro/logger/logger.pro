QT += core

TEMPLATE = lib

CONFIG += console
CONFIG += static
CONFIG += release

TARGET = FiveCatsLogger

MOC_DIR = build/moc
OBJECTS_DIR = build/obj
DESTDIR = build/bin

INCLUDEPATH += "../../src/logger/cpp/"

HEADERS =
HEADERS += ../../src/logger/cpp/FiveCatsLogger.h

SOURCES =
SOURCES += ../../src/logger/cpp/FiveCatsLogger.cpp
