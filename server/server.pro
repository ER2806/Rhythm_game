QT += core
QT -= gui
QT += widgets
QT += network

CONFIG += c++14

TARGET = server
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD ../

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    packmanager.cpp \
    ../libs/easylogging++.cpp \
    multithreadserver.cpp \
    mythread.cpp \
    configvalues.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    server.h \
    ../response_struct.h \
    baseserver.h \
    commands/basepackcommand.h \
    commands/packmusiccomand.h \
    commands/packplaylist.h \
    commands/packparsedmusic.h \
    packmanager.h \
    ../libs/easylogging++.h \
    CommandFactory/abstractcommandcreator.h \
    CommandFactory/commandcreator.h \
    CommandFactory/packcommandfactory.h \
    utils/enumcommands.h \
    Routing/baserouter.h \
    Routing/musicrouter.h \
    Routing/parsedmusicrouter.h \
    Routing/playlistrouter.h \
    multithreadserver.h \
    mythread.h \
    configvalues.h \
    ../logging.h

DISTFILES += \
    test.json
