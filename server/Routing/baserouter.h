#ifndef BASEROUTER_H
#define BASEROUTER_H

#include <QString>
#include "configvalues.h"

class BaseRouter {
public:

    BaseRouter() = default;
    virtual ~BaseRouter() = default;
    virtual QString getPath() = 0;

};

#endif // BASEROUTER
