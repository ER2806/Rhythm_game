#ifndef PARSEDMUSICROUTER_H
#define PARSEDMUSICROUTER_H

#include "baserouter.h"

class ParsedMusicRouter: public BaseRouter {
public:
    ParsedMusicRouter() = default;
    virtual ~ParsedMusicRouter() = default;

    QString getPath() override{

       return QString ("/Users/mac/Documents/Technopark/RhytmGame/MyServer/music/");

    }

    QString makePath(QString& music_name) {

        return getPath() + music_name;

    }

};


#endif // PARSEDMUSICROUTER_H
