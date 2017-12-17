#ifndef BASECLIENT_H
#define BASECLIENT_H

#include <QDataStream>
#include <../response_struct.h>

class BaseClient {
public:
    BaseClient() = default;
    virtual ~BaseClient() = default;

protected:
    virtual void responseManager(QDataStream& in) = 0;
    virtual void sendStructToServer(ResponseStruct&) = 0;
};

#endif // BASECLIENT_H
