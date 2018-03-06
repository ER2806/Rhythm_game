#ifndef BASESERVER_H
#define BASESERVER_H


class BaseServer
{

public:

    BaseServer(int port): port(port) {}
    virtual ~BaseServer() = default;
    virtual void run() = 0;

protected:

    int port;

};

#endif // BASESERVER_H
