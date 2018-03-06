#ifndef PARSEDMUSICROUTER_H
#define PARSEDMUSICROUTER_H

#include "baserouter.h"
#include "configvalues.h"

class ParsedMusicRouter: public BaseRouter {
public:
    ParsedMusicRouter() = default;
    virtual ~ParsedMusicRouter() = default;

    QString getPath() override{

       return ConfigValues::parsed_music_path;

    }

};


#endif // PARSEDMUSICROUTER_H
