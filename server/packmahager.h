#ifndef PACKMAHAGER_H
#define PACKMAHAGER_H

#include <iostream>
#include <QDataStream>
#include <QTextStream>
#include <QFile>
#include "../response_struct.h"
#include "utils.h"
class PackManager
{
public:
    PackManager() = default;
    ~PackManager() = default;
    ResponseStruct packToStruct(QDataStream& in);
private:
    void packMusic(QDataStream& in, ResponseStruct& out);
    void packParsedMusic(QDataStream& in, ResponseStruct& out);
    void packPlaylist(ResponseStruct& out);
    void packErrorMsg(ResponseStruct &out, quint8);
};


#endif // PACKMAHAGER_H
