#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>


enum Commands {
    ERROR, GET_MUSIC, GET_PLAYLIST, GET_PARSED_MUSIC
};

enum ErrorCodes {
    ALL_OK, TRACK_NOT_FOUND, PLAYLIST_NOT_FOUND, FILE_NOT_CREAT, ERR4
};


int getPort();

std::string getIpAddr();

QString getPathToMusicsFile();

QString getPathToParsedMusicsFile();

void delay(int msec_to_wait);

#endif // UTILS_H
