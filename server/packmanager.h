#ifndef PACKMAHAGER_H
#define PACKMAHAGER_H

#include <iostream>
#include <QDataStream>
#include <QTextStream>
#include <QFile>
#include "response_struct.h"
#include "logging.h"
#include "Routing/musicrouter.h"
#include "Routing/parsedmusicrouter.h"
#include "Routing/playlistrouter.h"

class PackManager
{
public:
    PackManager() = default;
    ~PackManager() = default;
    ResponseStruct packToStruct(QDataStream& in);
public:

    void packMusic(QDataStream& in, ResponseStruct& out);
    void packParsedMusic(QDataStream& in, ResponseStruct& out);
    void packPlaylist(QDataStream &in, ResponseStruct& out);
    void packErrorMsg(ResponseStruct &out, quint8);

    void writeFileContentToByteArray(QFile& file, QByteArray& out);
    void writeBinaryFileToByteArray(QFile& file, QByteArray& out);

    QString getTrackNameFromStream(QDataStream& stream);
    QString createPathToMusic(QString& track);
    QString createPathToParsedMusic(QString& track);

};


#endif // PACKMAHAGER_H
