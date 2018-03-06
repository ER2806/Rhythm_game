#ifndef BASEPACKCOMMAND_H
#define BASEPACKCOMMAND_H

class PackManager;
class BasePackCommand {
public:
    BasePackCommand() = default;
    ~BasePackCommand() = default;
    virtual void execute(PackManager& pack, QDataStream& in, ResponseStruct& out) = 0;

};

#endif // BASEPACKCOMMAND_H
