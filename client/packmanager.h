#ifndef PACKMANAGER_H
#define PACKMANAGER_H

#include "../response_struct.h"
//#include "utils.h"
#include "utils/enumcommands.h"

class PackManager
{
public:
    PackManager() = default;
    ~PackManager() = default;

    static ResponseStruct packTrackName(std::string& track_name);
    static ResponseStruct packParsedTrackName(std::string& track_name);
    static ResponseStruct packPlaylist();

private:

    static void addCommandToResponseStruct(ResponseStruct& str, unsigned comm);
    static void addStringToByteArray(QByteArray& arr, std::string& str);
};

#endif // PACKMANAGER_H
