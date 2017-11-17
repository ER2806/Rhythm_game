#ifndef CLIENT_COMMANDS_H
#define CLIENT_COMMANDS_H

class ClientCommands {
public:

    ClientCommands() = default;
    ClientCommands(ClientCommands&) = delete;
    ClientCommands(const ClientCommands&) = delete;
    ~ClientCommands() = default;

    virtual void execute(Client&, QDataStream& in) = 0;
};


class ParsedGetErrorMsg : public ClientCommands {
public:

    ParsedGetErrorMsg() = default;
    ~ParsedGetErrorMsg() = default;

    void execute(Client& c, QDataStream& in) override {
        c.parseResponseGetErrorMsg(in);
    }
};


class ParseGetMusic : public ClientCommands {
public:
    ParseGetMusic() = default;
    ~ParseGetMusic() = default;

    void execute(Client& c, QDataStream& in) override {
        c.parseResponseGetMusic(in);
    }
};


class ParseGetParsedMusic : public ClientCommands {
public:
    ParseGetParsedMusic() = default;
    ~ParseGetParsedMusic() = default;

    void execute(Client& c, QDataStream& in) override {
        c.parseResponseGetParsedMusic(in);
    }
};


class ParseGetPlaylist : public ClientCommands {
public:
    ParseGetPlaylist() = default;
    ~ParseGetPlaylist() = default;

    void execute(Client& c, QDataStream& in) override {
        c.parseResponseGetPlaylist(in);
    }
};


#endif // CLIENT_COMMANDS_H
