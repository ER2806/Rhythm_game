#include "mythread.h"

MyThread::MyThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    next_block_size = 0;
    this->socketDescriptor = ID;
}

void MyThread::run()
{

    socket = new QTcpSocket();


    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << socketDescriptor << " Client connected";


    exec();
}

void MyThread::readyRead()
{

    if (!socket){
        LOG(ERROR) <<  "Wrong client connection";
        return;
    }

    QDataStream in(socket);

    for (;;){
        if (!next_block_size){
            if (socket->bytesAvailable() < sizeof(quint16))
                break;
            in >> next_block_size;
        }

        if (socket->bytesAvailable() < next_block_size){
            break;
        }

        next_block_size = 0;
        requestManager();

    }

}

void MyThread::requestManager() {

    QDataStream in(socket);
    PackManager manag;
    ResponseStruct str =  manag.packToStruct(in);
    sendResultToClient(str);

}

void MyThread::sendResultToClient(ResponseStruct &str) {

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << quint32(sizeof(str.comand) + str.data.size());
    out << str;
    socket->write(block);

}

void MyThread::disconnected() {

    LOG(INFO) << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);

}
