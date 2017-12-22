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

    QString makePath(QString& music_name) {

        return getPath() + music_name;

    }

};


#endif // PARSEDMUSICROUTER_H
