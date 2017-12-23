#ifndef WEBGETTER_HPP
#define WEBGETTER_HPP

#define NON_MERGING
#include <string>
#include <vector>

class WebGetter{
public:
    WebGetter();
    ~WebGetter();
    std::vector<std::string> getTrackList(); // список названий аудиодорожек
    std::string getTrack(); //получение адеса аудио
    std::string getParsedTrack();
};

#endif // WEBGETTER_HPP
