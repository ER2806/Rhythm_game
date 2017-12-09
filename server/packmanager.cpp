#include "packmanager.h"
#include "CommandFactory/packcommandfactory.h"

ResponseStruct PackManager::packToStruct(QDataStream& dstream) {

    ResponseStruct out;
    ResponseStruct str_in;
    dstream >> str_in;
    quint8 comm = str_in.comand;
    QDataStream in(str_in.data);

    out.comand = comm;

    PackCommandFactory &factory = PackCommandFactory::instance();
    std::unique_ptr<BasePackCommand> command(factory.getCommand(comm));

    if (command) {
        command->execute(*this, in, out);

    } else {
        LOG(ERROR) << "Incorrect type of command from client socket. Command = " << comm;
    }

    return out;

}


void PackManager::packMusic(QDataStream &in, ResponseStruct &res) {

    QString track = getTrackNameFromStream(in);
    QString path = createPathToMusic(track);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
        LOG(ERROR) << "Music not fount. Music finding here: " << path.toStdString();
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
        LOG(ERROR) << "Parsed music not fount. Finding here: " << path.toStdString();
        packErrorMsg(res, ErrorCodes::PARSED_MUSIC_ERROR);
        return;
    }

    writeFileContentToByteArray(file, res.data);

}


void PackManager::packPlaylist(QDataStream &in, ResponseStruct &res) {

    PlaylistRouter rout;
    QFile file(rout.getPath());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        LOG(ERROR) << "Playlist is not found. Playlist finding here: "  << (rout.getPath()).toStdString();
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

    MusicRouter rout;
    return rout.makePath(track);

}


QString PackManager::createPathToParsedMusic(QString& track) {

    ParsedMusicRouter rout;
    return rout.makePath(track);

}
