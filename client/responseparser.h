#ifndef RESPONSEPARSING_H
#define RESPONSEPARSING_H

#include <QDataStream>
#include <QFile>
#include <string>
#include <sstream>
#include "utils.h"

class ResponseParser
{
public:
    ResponseParser() = default;
    ~ResponseParser() = default;

    static quint8 getErrorMsg(QByteArray& in);
    static quint8 getPlaylist(QByteArray& in, std::vector<std::string>&);
    static quint8 getMusic(QByteArray& in, std::string&);
    static quint8 getParsedMusic(QByteArray& in, std::string&);

};


#endif // RESPONSEPARSING_H
