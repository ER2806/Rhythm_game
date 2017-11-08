#ifndef UTILS_H
#define UTILS_H

#include <QString>

enum Commands {
    ERROR, GET_MUSIC, GET_PLAYLIST
};

enum ErrorCodes {
    ALL_OK, TRACK_NOT_FOUND, PLAYLIST_NOT_FOUND, ERR3, ERR4
};

int getPort();

QString getPathToMusicsFile();

#endif // UTILS_H
