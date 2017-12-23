#ifndef PACKPLAYLIST_H
#define PACKPLAYLIST_H

#include "commands/basepackcommand.h"

class PackPlaylist: public BasePackCommand {
public:
    PackPlaylist() = default;
    ~PackPlaylist() = default;


    void execute(PackManager& pack, QDataStream& in, ResponseStruct& out) override {
        pack.packPlaylist(in, out);
    }
};

#endif // PACKPLAYLIST_H
