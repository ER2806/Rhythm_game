#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>


enum Commands {
    ERROR, GET_MUSIC, GET_PLAYLIST
};

enum ErrorCodes {
    ALL_OK, TRACK_NOT_FOUND, PLAYLIST_NOT_FOUND, ERR3, ERR4
};


int getPort();

QString getIpAddr();

QString getPathToMusicsFile();

void delay(int msec_to_wait);

#endif // UTILS_H
