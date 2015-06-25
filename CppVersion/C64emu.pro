#-------------------------------------------------
#
# Project created by QtCreator 2015-06-08T09:20:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = C64emu
TEMPLATE = app


SOURCES += main.cpp \
    AssemblyInstructions.cpp \
    Emulator.cpp \
    FastConsole.cpp \
    KeyboardWatcher.cpp \
    Memory.cpp \
    Prg.cpp \
    Stack.cpp \
    C64CharConverter.cpp \
    mainwindow.cpp \
    menuwrapper.cpp \
    RuntimeLogger.cpp

HEADERS  += \
    Emulator.h \
    FastConsole.h \
    KeyboardWatcher.h \
    Memory.h \
    Prg.h \
    Registers.h \
    Stack.h \
    AssemblyInstructions.h \
    C64CharConverter.h \
    C64ColorConverter.h \
    utils.h \
    mainwindow.h \
    menuwrapper.h \
    RuntimeLogger.h

FORMS    += \
    mainwindow.ui
