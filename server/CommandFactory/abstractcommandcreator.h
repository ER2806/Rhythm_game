#ifndef ABSTRACTCOMMANDCREATOR_H
#define ABSTRACTCOMMANDCREATOR_H

#include "../commands/basepackcommand.h"


class AbstractPackCommandCreator
{
public:

    virtual ~AbstractPackCommandCreator() = default;
    virtual BasePackCommand * create() const = 0;

};

#endif // ABSTRACTCOMMANDCREATOR_H
