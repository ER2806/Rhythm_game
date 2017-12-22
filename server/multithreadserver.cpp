#include "multithreadserver.h"
#include "mythread.h"
#include "../logging.h"

MultithreadServer::MultithreadServer(int port, QObject *parent) :
      QTcpServer(parent), BaseServer(port)
{}

void MultithreadServer::run()
{
    if(this->listen(QHostAddress::Any, BaseServer::port))
    {
        LOG(INFO) << "Server started in port" << port << std::endl;
        qDebug() << "Server started";
    }
    else
    {
        LOG(ERROR) << "Enable to start server in port "  << port << " " << errorString().toStdString();
        qDebug() << "Server did not start!";
        throw std::logic_error(errorString().toStdString());
    }
}

void MultithreadServer::incomingConnection(qintptr socketDescriptor)
{

    MyThread *thread = new MyThread(socketDescriptor, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();

}

