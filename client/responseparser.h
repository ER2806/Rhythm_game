#ifndef RESPONSEPARSING_H
#define RESPONSEPARSING_H

#include <QDataStream>
#include <QFile>
#include <string>
#include <sstream>
#include "Routing/musicrouter.h"
#include "Routing/parsedmusicrouter.h"
#include "utils/enumcommands.h"
#include <QString>

class ResponseParser
{
public:
    ResponseParser() = default;
    ~ResponseParser() = default;

    static quint8 getErrorMsg(QByteArray& in);
    static quint8 getPlaylist(QByteArray& in, std::vector<std::string>&);
    static quint8 getMusic(QByteArray& in, std::string&);
    static quint8 getParsedMusic(QByteArray& in, std::string&);

private:

    static QString createPathToMusic(QString&);
    static QString createPathToParsedMusic(QString&);
    static quint8 createFileFromByteArray(QByteArray& data, QString& path);
};


#endif // RESPONSEPARSING_H
