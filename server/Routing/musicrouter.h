#ifndef MUSICROUTER_H
#define MUSICROUTER_H

#include "baserouter.h"

class MusicRouter: public BaseRouter {
public:
    MusicRouter() = default;
    virtual ~MusicRouter() = default;

    QString getPath() override{

       return QString ("/Users/mac/Documents/Technopark/RhytmGame/MyServer/music/");

    }

    QString makePath(QString& music_name) {

        return getPath() + music_name;

    }

};

#endif // MUSICROUTER_H
