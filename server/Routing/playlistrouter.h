#ifndef PLAYLISTROUTER_H
#define PLAYLISTROUTER_H

#include "baserouter.h"
#include "configvalues.h"

class PlaylistRouter: public BaseRouter {
public:
    PlaylistRouter() = default;
    virtual ~PlaylistRouter() = default;

    QString getPath() override{

        return ConfigValues::playlist_path;

    }

};


#endif // PLAYLISTROUTER_H
