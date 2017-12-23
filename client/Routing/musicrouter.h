#ifndef MUSICROUTER_H
#define MUSICROUTER_H

#include "baserouter.h"
#include "configvalues.h"

class MusicRouter: public BaseRouter {
public:
    MusicRouter() = default;
    virtual ~MusicRouter() = default;

    QString getPath() override{

        return ConfigValues::music_path;


    }

};

#endif // MUSICROUTER_H
