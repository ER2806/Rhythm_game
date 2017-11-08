#ifndef UTILS_H
#define UTILS_H

#include <QString>

enum Commands {
    ERROR, GET_MUSIC, GET_PLAYLIST, GET_PARSED_MUSIC
};

enum ErrorCodes {
    ALL_OK, TRACK_NOT_FOUND, PLAYLIST_NOT_FOUND, PARSED_MUSIC_ERROR, ERR4
};

int getPort();

QString getPathToMusicsFile();

QString getPathToPlaylist();

QString getPathToParsedMusic();

#endif // UTILS_H
