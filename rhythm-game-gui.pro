QT += core
QT -= gui

CONFIG += c++11

TARGET = rhythm-game-gui
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    easylogging++.cc


LIBS += -L/home/daria/Downloads/SFML-master/lib -lsfml-audio -lsfml-system -lsfml-window -lsfml-graphics

INCLUDEPATH += /home/daria/Downloads/SFML-master/include
DEPENDPATH += /home/daria/Downloads/SFML-master/include

HEADERS += \
    graph.hpp \
    easylogging++.h

