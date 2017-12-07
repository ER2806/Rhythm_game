#include "server.h"
#include <QTextStream>
#include <QVector>
#include "packmanager.h"
#include "logging.h"

Server::Server(int port, QObject* parent/* = 0*/) : QObject(parent), BaseServer(port), next_block_size(0),
                                                    tcp_server(std::make_unique<QTcpServer>(nullptr)) {}

Server::~Server(){

    if (tcp_server)
        tcp_server->close();

}

void Server::run() {

    tcp_server = std::make_unique<QTcpServer>(new QTcpServer(this));
    if (!tcp_server->listen(QHostAddress::Any, port)) {
        LOG(ERROR) << "Enable to start server in port " << port;
        //std::cerr << "Enable to start server " << tcp_server->errorString().toStdString() << std::endl;
        throw std::logic_error(tcp_server->errorString().toStdString());
        return;
    }

    connect(tcp_server.get(), SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    LOG(INFO) << "Server started in port" << port << std::endl;
    //std::cout << "Server started" << std::endl;

}

void Server::slotNewConnection() {

    LOG(INFO) << "new_connection to serv";
    //std::cout << "new_connection " << std::endl;
    QTcpSocket* client = tcp_server->nextPendingConnection();
    if (!client) {
        LOG(ERROR) <<  "Wrong client connection" << std::endl;
        //std::cerr << "Wrong client connection" << std::endl;
        return;
    }

    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
    connect(client, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
}

void Server::slotReadClient() {

    QTcpSocket* client = (QTcpSocket*)sender();
    if (!client){
        LOG(ERROR) <<  "Wrong client connection" << std::endl;
        //std::cout << "Wrong Connection" << std::endl;
        return;
    }

    QDataStream in(client);

    for (;;){
        if (!next_block_size){
            if (client->bytesAvailable() < sizeof(quint16))
                break;
            in >> next_block_size;
        }

        if (client->bytesAvailable() < next_block_size)
            break;
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
    //std::cout << "Send Result To Client" << std::endl;
    client->write(block);

}
