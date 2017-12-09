#include "client.h"
#include "logging.h"

Client::Client(const std::string& host, int port, QObject* parent): QObject(parent), next_block_size(0)
{
    this->is_executed_response = false;

    client = std::make_unique<QTcpSocket>(new QTcpSocket(this));
    client->connectToHost(QString::fromStdString(host), port);
    connect(client.get(), SIGNAL(connected()), SLOT(slotConnected()));
    connect(client.get(), SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(client.get(), SIGNAL(error(QAbstractSocket::SocketError)),
                                     this, SLOT(slotError(QAbstractSocket::SocketError)));

}

Client::~Client(){

    client->close();

}


void Client::slotReadyRead() {

    QDataStream in(client.get());
    in.setVersion(QDataStream::Qt_5_7);

    if (!client) {
        LOG(INFO) << "client closed";
        return;
    }


    for (;;) {

        if (!next_block_size) {
            if (client->bytesAvailable() < static_cast<qint64>(sizeof(quint32))) {
                break;
            }
            in >> next_block_size;
        }

        if (client->bytesAvailable() < next_block_size) {
            break;
        }

        next_block_size = 0;
        responseManager(client, in);

    }

}


void Client::responseManager(std::unique_ptr<QTcpSocket>& client, QDataStream& in){

    ResponseStruct res;
    in >> res;

    if (res.comand == ERROR) {

        err_code = ResponseParser::getErrorMsg(res.data);
        LOG(ERROR) << "from server returned Error code: " << err_code;

        is_executed_response = true;

    } else {

        tmp_data = res.data;
        is_executed_response = true;

    }

}

void Client::slotError(QAbstractSocket::SocketError err){

    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(client->errorString())
                    );
    LOG(ERROR)  << strError.toStdString();
    err_code = ERR4;

}


void Client::slotConnected() {

    LOG(INFO) << "client connected to Server";

}


void Client::sendGetTrack(std::string& track_name) {

    LOG(INFO) << "sended Get track: track_name: " << track_name;
    is_executed_response = false;
    err_code = ErrorCodes::ALL_OK;
    ResponseStruct str = PackManager::packTrackName(track_name);
    sendStructToServer(str);

}

void Client::sendGetParsedTrack(std::string& track_name) {

    LOG(INFO) << "sended Get Parsed track: parsed track name: " << track_name;
    is_executed_response = false;
    err_code = ErrorCodes::ALL_OK;
    ResponseStruct str = PackManager::packParsedTrackName(track_name);
    sendStructToServer(str);

}

void Client::sendGetPlaylist() {

    LOG(INFO) << "sended Get Playlist";
    is_executed_response = false;
    err_code = ErrorCodes::ALL_OK;
    ResponseStruct str = PackManager::packPlaylist();
    sendStructToServer(str);

}


void Client::sendStructToServer(ResponseStruct& str) {

    LOG(INFO) << "struct sended to server";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << quint16(sizeof(str.comand) + str.data.size());
    out << str;
    client->write(block);

}

std::string Client::getTrackFromServer(uint8_t& error_code, std::string& track_name) {

    LOG(INFO) << track_name;
    sendGetTrack(track_name);

    wait_response();

    error_code = err_code;
    std::string res;

    if (error_code == ALL_OK) {
        error_code = ResponseParser::getMusic(tmp_data, res);
    }

    LOG(INFO) << "returned" << res;
    return res;

}

std::string Client::getParsedTrackFromServer(uint8_t& error_code, std::string& track_name) {

    LOG(INFO) << track_name;
    sendGetParsedTrack(track_name);

    wait_response();

    error_code = err_code;
    std::string res;

    if (error_code == ALL_OK) {

        error_code = ResponseParser::getParsedMusic(tmp_data, res);

    }

    LOG(INFO) << "returned" << res;
    return res;

}

std::vector<std::string> Client::getPlaylistFromServer(uint8_t& error_code) {

    sendGetPlaylist();

    wait_response();

    error_code = err_code;
    std::vector<std::string> res;
    if (error_code == ALL_OK) {
        error_code = ResponseParser::getPlaylist(tmp_data, res);
    }

    return res;

}

void Client::wait_response() {

    while(!is_executed_response && err_code == ErrorCodes::ALL_OK){

        delay(100);

    }

}
