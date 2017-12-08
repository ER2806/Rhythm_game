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
};


#endif // PARSEDMUSICROUTER_H
