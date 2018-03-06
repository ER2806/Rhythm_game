QT += core
QT -= gui
QT += widgets
QT += network

CONFIG += c++14

TARGET = client
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

#INCLUDEPATH += /Users/mac/Documents/Technopark/RhytmGame/RhytmGame
INCLUDEPATH += $$PWD ../

SOURCES += main.cpp \
    client.cpp \
    packmanager.cpp \
    responseparser.cpp \
    ../libs/easylogging++.cpp \
    utils/delay.cpp \
    test.cpp \
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
    client.h \
    ../response_struct.h \
    packmanager.h \
    responseparser.h \
    ../libs/easylogging++.h \
    Routing/baserouter.h \
    Routing/musicrouter.h \
    Routing/parsedmusicrouter.h \
    utils/enumcommands.h \
    utils/delay.h \
    test.h \
    baseclient.h \
    ../logging.h \
    configvalues.h

DISTFILES += \
    config.json
