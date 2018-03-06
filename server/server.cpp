#include "server.h"

Server::Server(int port, QObject* parent/* = 0*/) : QObject(parent), BaseServer(port), next_block_size(0),
                                                    tcp_server(std::make_unique<QTcpServer>(nullptr)) {}


Server::~Server(){

    if (tcp_server)
        tcp_server->close();

}

void Server::run() {

    tcp_server = std::make_unique<QTcpServer>(this);
    if (!tcp_server->listen(QHostAddress::Any, port)) {
        LOG(ERROR) << "Enable to start server in port "  << port << " " << tcp_server->errorString().toStdString();
        throw std::logic_error(tcp_server->errorString().toStdString());
        return;
    }

    connect(tcp_server.get(), SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    LOG(INFO) << "Server started in port" << port << std::endl;

}

void Server::slotNewConnection() {

    LOG(INFO) << "new_connection to serv";
    QTcpSocket* client = tcp_server->nextPendingConnection();
    if (!client) {
        LOG(ERROR) <<  "Wrong client connection";
        return;
    }

    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
    connect(client, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

}

void Server::slotReadClient() {

    QTcpSocket* client = (QTcpSocket*)sender();
    if (!client){
        LOG(ERROR) <<  "Wrong client connection";
        return;
    }

    QDataStream in(client);

    for (;;){
        if (!next_block_size){
            if (client->bytesAvailable() < sizeof(quint16))
                break;
            in >> next_block_size;
        }

        if (client->bytesAvailable() < next_block_size){
            break;
        }

        next_block_size = 0;
        requestManager(client);

    }

}

void Server::requestManager(QTcpSocket* client) {

    QDataStream in(client);
    PackManager manag;
    ResponseStruct str =  manag.packToStruct(in);
    sendResultToClient(client, str);

}


void Server::sendResultToClient(QTcpSocket* client, ResponseStruct &str) {

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << quint32(sizeof(str.comand) + str.data.size());
    out << str;
    client->write(block);

}
