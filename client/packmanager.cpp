#include "packmanager.h"

ResponseStruct PackManager::packTrackName(std::string &track_name) {

    ResponseStruct str;
    addCommandToResponseStruct(str, Commands::GET_MUSIC);
    addStringToByteArray(str.data, track_name);

    return str;

}


ResponseStruct PackManager::packParsedTrackName(std::string &track_name) {

    ResponseStruct str;
    addCommandToResponseStruct(str, Commands::GET_PARSED_MUSIC);
    addStringToByteArray(str.data, track_name);

    return str;

}


ResponseStruct PackManager::packPlaylist() {

    ResponseStruct str;
    addCommandToResponseStruct(str, Commands::GET_PLAYLIST);

    return str;

}


void PackManager::addCommandToResponseStruct(ResponseStruct &str, unsigned comm) {

    str.comand = comm;

}


void PackManager::addStringToByteArray(QByteArray &arr, std::string &str) {

    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << QString::fromStdString(str);

}
