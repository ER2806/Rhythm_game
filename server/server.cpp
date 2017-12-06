#include "server.h"
#include <QTextStream>
#include <QVector>
#include "packmahager.h"

Server::Server(int port, QObject* parent/* = 0*/) : QObject(parent), next_block_size(0) {

    tcp_server = std::move(std::unique_ptr<QTcpServer>(new QTcpServer(this)));
    if (!tcp_server->listen(QHostAddress::Any, port)) {
        std::cerr << "Enable to start server " << tcp_server->errorString().toStdString() << std::endl;
        return;
    }

    connect(tcp_server.get(), SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    std::cout << "Server started" << std::endl;

}

Server::~Server(){

    tcp_server->close();

}

void Server::slotNewConnection() {

    std::cout << "new_connection " << std::endl;
    QTcpSocket* client = tcp_server->nextPendingConnection();

    if (!client) {
        std::cerr << "Wrong client connection" << std::endl;
        return;
    }
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
    connect(client, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

}

void Server::slotReadClient() {

    QTcpSocket* client = (QTcpSocket*)sender();
    QDataStream in(client);
    in.setVersion(QDataStream::Qt_5_7);
    for (;;){
        if (!next_block_size){
            if (client->bytesAvailable() < sizeof(quint16))
                break;
            in >> next_block_size;
        }

        if (client->bytesAvailable() < next_block_size)
            break;
        next_block_size = 0;
        requestManager(client, in);
    }

}

void Server::requestManager(QTcpSocket *client, QDataStream &in) {
    PackManager manag;
    ResponseStruct str =  manag.packToStruct(in);
    sendResultToClient(client, str);
}


void Server::sendResultToClient(QTcpSocket *client, ResponseStruct &str) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << quint32(sizeof(str.comand) + str.data.size());
    out << str;
    std::cout << "Send Result To Client" << std::endl;
    client->write(block);
}
