#ifndef PACKMUSICCOMAND_H
#define PACKMUSICCOMAND_H

#include "commands/basepackcommand.h"

class PackMusic: public BasePackCommand {
public:
    PackMusic() = default;
    ~PackMusic() = default;


    void execute(PackManager& pack, QDataStream& in, ResponseStruct& out) override {

        pack.packMusic(in, out);

    }
};

#endif // PACKMUSICCOMAND_H
