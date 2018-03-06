#ifndef COMMANDCREATOR_H
#define COMMANDCREATOR_H

#include "abstractcommandcreator.h"


template <class C>
class PackCommandCreator : public AbstractPackCommandCreator {
public:

    virtual ~PackCommandCreator() = default;
    virtual BasePackCommand * create() const {
        return new C();
    }

};

#endif // COMMANDCREATOR_H
