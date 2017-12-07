#ifndef PACKCOMMANDSTORAGE_H
#define PACKCOMMANDSTORAGE_H
#include "commands/packmusiccomand.h"
#include "commands/packparsedmusic.h"
#include "commands/packplaylist.h"
#include "utils.h"
#include <map>


class PackCommandStorage {
private:
    std::map<int, std::function<BasePackCommand*()>> commands;

    PackCommandStorage () {

        commands[GET_MUSIC] = PackMusic::createCommand;
        commands[GET_PLAYLIST] = PackPlaylist::createCommand;
        commands[GET_PARSED_MUSIC] = PackParsedMusic::createCommand;

    }


public:
    PackCommandStorage(PackCommandStorage&) = delete;
    PackCommandStorage(PackCommandStorage&&) = delete;
    ~PackCommandStorage() = default;

    static PackCommandStorage& instance() {
        static PackCommandStorage obj;
        return obj;
    }

    std::function<BasePackCommand*()>& getCommand(const int& key) {
        return commands[key];
    }
};

#endif // PACKCOMMANDSTORAGE_H
