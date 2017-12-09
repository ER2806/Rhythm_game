#include "responseparser.h"

quint8 ResponseParser::getErrorMsg(QByteArray &in) {

    QDataStream ss(in);
    quint8 err_code;
    ss >> err_code;
    return err_code;

}

quint8 ResponseParser::getMusic(QByteArray &in, std::string &res) {

    QByteArray music = in;
    QString track_name("new.vaw"); // На стороне клиента запрошенная музыка будет сохранена под именем  new.vaw
    QString path = createPathToMusic(track_name);

    res = path.toStdString();
    return createFileFromByteArray(music, path);

}

quint8 ResponseParser::getParsedMusic(QByteArray &in, std::string &res) {

    QByteArray parsed_music = in;
    QString file_name("parsed.txt");
    QString path = createPathToParsedMusic(file_name);

    res = path.toStdString();

    return createFileFromByteArray(parsed_music, path);

}

quint8 ResponseParser::getPlaylist(QByteArray &in, std::vector<std::string> &res) {

    QByteArray playlist = in;
    std::string str = playlist.toStdString();
    std::replace(str.begin(), str.end(), '\n', ' ');
    std::stringstream ss(str);
    res.clear();
    std::string tmp;
    while(ss >> tmp){
        res.push_back(tmp);
    }

    return ALL_OK;

}


QString ResponseParser::createPathToMusic(QString& track){

    MusicRouter rout;
    return rout.getPath() + track;


}


QString ResponseParser::createPathToParsedMusic(QString& track) {

    ParsedMusicRouter rout;
    return rout.getPath() + track;

}

quint8 ResponseParser::createFileFromByteArray(QByteArray &data, QString &path) {

    QFile file(path);

    if (!file.open(QIODevice::WriteOnly))
        return ErrorCodes::FILE_NOT_CREAT;

    // Проверяем записались ли все данные
    quint8 err_code = (file.write(data, data.size()) == data.size()) ?
                                                    ErrorCodes::ALL_OK : ErrorCodes::FILE_NOT_CREAT;

    file.close();

    return err_code;

}
