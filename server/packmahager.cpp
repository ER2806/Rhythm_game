#include "packmahager.h"


ResponseStruct PackManager::packToStruct(QDataStream& in) {

    ResponseStruct out;
    quint8 comm;
    in >> comm;
    out.comand = comm;
    switch(comm) {
        case(GET_MUSIC) :{
            packMusic(in, out);
            break;
        }

        case(GET_PARSED_MUSIC): {
            packParsedMusic(in, out);
            break;
        }

        case(GET_PLAYLIST): {
            packPlaylist(out);
            break;
        }
    }

    return out;

}


void PackManager::packMusic(QDataStream &in, ResponseStruct &res) {

    QString track = getTrackNameFromStream(in);
    QString path = createPathToMusic(track);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){

        packErrorMsg(res, ErrorCodes::TRACK_NOT_FOUND);

        return;
    }

    writeBinaryFileToByteArray(file, res.data);

}


void PackManager::packParsedMusic(QDataStream &in, ResponseStruct &res) {

    QString track = getTrackNameFromStream(in);
    QString path = createPathToParsedMusic(track);

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        packErrorMsg(res, ErrorCodes::PARSED_MUSIC_ERROR);
        return;
    }

    writeFileContentToByteArray(file, res.data);

}


void PackManager::packPlaylist(ResponseStruct &res) {

    QFile file(getPathToPlaylist());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Playlists is not found" << std::endl;
        packErrorMsg(res, ErrorCodes::PLAYLIST_NOT_FOUND);
        return;
    }

    writeFileContentToByteArray(file, res.data);

}


void PackManager::packErrorMsg(ResponseStruct &res, quint8 err_code) {

    res.comand = Commands::ERROR;
    QDataStream out(&(res.data), QIODevice::WriteOnly);
    out << quint8(err_code);

}


void PackManager::writeFileContentToByteArray(QFile &file, QByteArray &res) {

    QTextStream in2(&file);
    QString line = in2.readAll();
    file.close();
    QDataStream out(&res, QIODevice::WriteOnly);
    out << line.toUtf8();

}


void PackManager::writeBinaryFileToByteArray(QFile &file, QByteArray &res) {

    QByteArray track_bytes = file.readAll();
    QDataStream out(&res, QIODevice::WriteOnly);
    out << QByteArray(track_bytes.data(), track_bytes.size());

}


QString PackManager::getTrackNameFromStream(QDataStream &stream) {

    QString track;
    stream >> track;
    return track;

}


QString PackManager::createPathToMusic(QString& track){

    QString tmp = getPathToMusicsFile();
    std::cout << tmp.toStdString() << std::endl;
    std::cout<< (tmp.append(track)).toStdString() << std::endl;
    return getPathToMusicsFile() + track;

}


QString PackManager::createPathToParsedMusic(QString& track) {

    return getPathToParsedMusic() + track;

}
