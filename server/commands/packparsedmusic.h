#ifndef PACKPARSEDMUSIC_H
#define PACKPARSEDMUSIC_H

#include "commands/basepackcommand.h"

class PackParsedMusic: public BasePackCommand {
public:
    PackParsedMusic() = default;
    ~PackParsedMusic() = default;


    void execute(PackManager& pack, QDataStream& in, ResponseStruct& out) override {
        pack.packParsedMusic(in, out);
    }
};


#endif // PACKPARSEDMUSIC_H
