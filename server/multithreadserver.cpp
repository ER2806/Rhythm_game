#include "multithreadserver.h"
#include "mythread.h"


MultithreadServer::MultithreadServer(int port, QObject *parent) :
      QTcpServer(parent), BaseServer(port)
{}

void MultithreadServer::run()
{
    if(this->listen(QHostAddress::Any, BaseServer::port))
    {
        qDebug() << "Server started";
    }
    else
    {
        qDebug() << "Server did not start!";
    }
}

void MultithreadServer::incomingConnection(qintptr socketDescriptor)
{

    qDebug() << socketDescriptor << " Connecting...";

    MyThread *thread = new MyThread(socketDescriptor, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

