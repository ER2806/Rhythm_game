#ifndef PACKCOMMANDFACTORY_H
#define PACKCOMMANDFACTORY_H

#include <map>
#include "commandcreator.h"
#include "../commands/packparsedmusic.h"
#include "../commands/packmusiccomand.h"
#include "../commands/packplaylist.h"
#include "../utils.h"


class PackCommandFactory {
private:

    std::map<int, std::unique_ptr<AbstractPackCommandCreator>> commands;
    PackCommandFactory () {

        addCommand<PackMusic>(GET_MUSIC);
        addCommand<PackPlaylist>(GET_PLAYLIST);
        addCommand<PackParsedMusic>(GET_PARSED_MUSIC);

    }

public:

    PackCommandFactory(PackCommandFactory&) = delete;
    PackCommandFactory(PackCommandFactory&&) = delete;
    ~PackCommandFactory() = default;

    static PackCommandFactory& instance() {

        static PackCommandFactory obj;
        return obj;

    }


    BasePackCommand* getCommand(const int& key) {

        return commands[key]->create();

    }


    template <class C>
    void addCommand(const int& key) {

        std::map<int, std::unique_ptr<AbstractPackCommandCreator>>::iterator it = commands.find(key);

        if (it == commands.end()) {

            commands[key] = std::unique_ptr<AbstractPackCommandCreator>(new PackCommandCreator<C>());

        }
    }

};

#endif // PACKCOMMANDFACTORY_H
