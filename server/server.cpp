#include "server.h"
#include <QTextStream>
#include <QVector>
//#include "server_commands.h"

Server::Server(int port, QWidget* parent/* = 0*/) : QWidget(parent), next_block_size(0) {

    tcp_server = new QTcpServer(this);
    if (!tcp_server->listen(QHostAddress::Any, port)) {
        std::cerr << "Enable to start server " << tcp_server->errorString().toStdString() << std::endl;
        return;
    }

    connect(tcp_server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
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

    //std::cout << "Slot Read Client" << std::endl;
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
    quint8 command;
    in >> command;
    switch (command){
        /* case 1: args QString track_name or id */
        case (Commands::GET_MUSIC) /*GETTRACK*/: {
            //std::cout << "server case 1" << std::endl;
            //sendTrackToClient(client, in);
            SendTrack comm(client, in);
            comm.execute(*this);
            break;
        }

        case (Commands::GET_PLAYLIST) /*GEtPlalist*/: {
            //std::cout << "server case 2" << std::endl;
            //sendPlaylistToClient(client, in);
            SendPlaylist comm(client, in);
            comm.execute(*this);
            break;
        }

        case (Commands::GET_PARSED_MUSIC): {
            //std::cout << "server case 3" << std::endl;
            //sendParsedMusicToClient(client, in);
            SendParsedTrack comm(client, in);
            comm.execute(*this);
            break;
        }
        default: break;

    }
}

void Server::sendTrackToClient(QTcpSocket* client, QDataStream& in) {

    QString track;
    in >> track;
    QString path = getPathToMusicsFile() + track;
    //std::cout << path.toStdString() << std::endl;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
        std::cout << "music not found" << std::endl;
        sendErrorMsgToClient(client, ErrorCodes::TRACK_NOT_FOUND);
        return;
    }
    QByteArray track_bytes = file.readAll();
    //std::cout << "music size = " << track_bytes.size() << std::endl;

    QByteArray tmp;
    QDataStream out(&tmp, QIODevice::WriteOnly);
    out.device()->seek(0);
    out << quint32(track_bytes.size() + sizeof(quint8));
    out << quint8(Commands::GET_MUSIC);
    out << QByteArray(track_bytes.data(), track_bytes.size());
    client->write(tmp);

}

void Server::sendPlaylistToClient(QTcpSocket *client, QDataStream &in) {

    QFile file(getPathToPlaylist());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Playlists is not found" << std::endl;
        sendErrorMsgToClient(client, ErrorCodes::PLAYLIST_NOT_FOUND);
        return;
    }

    QTextStream in2(&file);
    QString line = in2.readAll();
    file.close();
    //std::cout << line.toStdString() << std::endl;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.device()->seek(0);
    out << quint32(0);
    out << quint8(Commands::GET_PLAYLIST);

    //out << QByteArray((char*)line.data(), line.size()*2);
    out << line.toUtf8();
    out.device()->seek(0);
    out<< quint32(block.size() - sizeof(quint32));
    //std::cout << "server client -> write" << std::endl;
    client->write(block);

}

void Server::sendParsedMusicToClient(QTcpSocket *client, QDataStream &in) {

    QString track;
    in >> track;
    QString path = getPathToParsedMusic() + track;
    //std::cout << path.toStdString() << std::endl;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
        // audio_handler.parse_music( ... )
        //std::cout << "Parsed Track is not found" << std::endl;
        sendErrorMsgToClient(client, ErrorCodes::PARSED_MUSIC_ERROR);
        return;
    }

    QTextStream in2(&file);
    QString line = in2.readAll();
    file.close();
//    std::cout << line.toStdString() << std::endl;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.device()->seek(0);
    out << quint32(0);
    out << quint8(Commands::GET_PARSED_MUSIC);

//    out << QByteArray((char*)line.data(), line.size()*2);
    out << line.toUtf8();
    out.device()->seek(0);
    out<< quint32(block.size() - sizeof(quint32));
    //std::cout << "server client -> write" << std::endl;
    client->write(block);

}

void Server::sendErrorMsgToClient(QTcpSocket *client, quint8 err_code) {

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << quint32(sizeof(quint8)*2);
    out << quint8(Commands::ERROR);
    out << err_code;
    client->write(block);

}
