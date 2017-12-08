#ifndef PLAYLISTROUTER_H
#define PLAYLISTROUTER_H

#include "baserouter.h"

class PlaylistRouter: public BaseRouter {
public:
    PlaylistRouter() = default;
    virtual ~PlaylistRouter() = default;

    QString getPath() override{

       return QString ("/Users/mac/Documents/Technopark/RhytmGame/MyServer/music/playlist.txt");

    }

};


#endif // PLAYLISTROUTER_H
