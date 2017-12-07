#ifndef BASEPACKCOMMAND_H
#define BASEPACKCOMMAND_H

class PackManager;
class BasePackCommand {
public:
    BasePackCommand() = default;
    ~BasePackCommand() = default;
    virtual void execute(PackManager& pack, QDataStream& in, ResponseStruct& out) = 0;

};

//class PackMusic: public BasePackCommand {
//public:
//    PackMusic() = default;
//    ~PackMusic() = default;

//    static BasePackCommand* createCommand() {
//        return new PackMusic();
//    }

//    void execute(PackManager& pack, QDataStream& in, ResponseStruct& out) override {
//        pack.packMusic(in, out);
//    }
//};

//class PackParsedMusic: public BasePackCommand {
//public:
//    PackParsedMusic() = default;
//    ~PackParsedMusic() = default;

//    static BasePackCommand* createCommand() {
//        return new PackParsedMusic();
//    }

//    void execute(PackManager& pack, QDataStream& in, ResponseStruct& out) override {
//        pack.packParsedMusic(in, out);
//    }
//};


//class PackPlaylist: public BasePackCommand {
//public:
//    PackPlaylist() = default;
//    ~PackPlaylist() = default;

//    static BasePackCommand* createCommand() {
//        return new PackPlaylist();
//    }

//    void execute(PackManager& pack, QDataStream& in, ResponseStruct& out) override {
//        pack.packPlaylist(in, out);
//    }
//};



#endif // BASEPACKCOMMAND_H
