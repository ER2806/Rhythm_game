#ifndef SERVER_COMMANDS_H
#define SERVER_COMMANDS_H

//class Server;
//class ServerCommands {
//public:
//    ServerCommands() = default;
//    ServerCommands(ServerCommands&) = delete;
//    ServerCommands(const ServerCommands&) = delete;
//    ~ServerCommands() = default;

//    virtual void execute(Server&) = 0;

//};

//class SendErrorMsg: public ServerCommands {
//public:
//    SendErrorMsg(QTcpSocket *client, quint8 error_code): client(client), error_code(error_code) {}
//    SendErrorMsg(SendErrorMsg&) = delete;
//    SendErrorMsg(const SendErrorMsg&) = delete;
//    ~SendErrorMsg() = default;

//    void execute(Server& serv) override{
//        serv.sendErrorMsgToClient(this->client, this->error_code);
//    }

//private:
//    QTcpSocket* client;
//    quint8 error_code;
//};

//class SendPlaylist : public ServerCommands {
//public:
//    SendPlaylist(QTcpSocket *client, QDataStream &in): client(client), in(in) {}
//    SendPlaylist(SendPlaylist&) = delete;
//    SendPlaylist(const SendPlaylist&) = delete;
//    ~SendPlaylist() = default;

//    void execute(Server& serv) override {
//        serv.sendPlaylistToClient(client, in);
//    }

//private:
//    QTcpSocket *client;
//    QDataStream &in;
//};

//class SendTrack : public ServerCommands {
//public:
//    SendTrack(QTcpSocket *client, QDataStream &in): client(client), in(in) {}
//    SendTrack(SendTrack&) = delete;
//    SendTrack(const SendTrack&) = delete;
//    ~SendTrack() = default;

//    void execute(Server& serv) override {
//        serv.sendTrackToClient(client, in);
//    }

//private:
//    QTcpSocket *client;
//    QDataStream &in;
//};

//class SendParsedTrack : public ServerCommands {
//public:
//    SendParsedTrack(QTcpSocket *client, QDataStream &in): client(client), in(in) {}
//    SendParsedTrack(SendParsedTrack&) = delete;
//    SendParsedTrack(const SendParsedTrack&) = delete;
//    ~SendParsedTrack() = default;

//    void execute(Server& serv) override {
//        serv.sendParsedMusicToClient(client, in);
//    }

//private:
//    QTcpSocket *client;
//    QDataStream &in;
//};

#endif // SERVER_COMMANDS_H
