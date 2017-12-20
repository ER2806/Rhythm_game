#ifndef WEBGETTER_HPP
#define WEBGETTER_HPP

#define NON_MERGING
#include <string>

class WebGetter{
public:
    WebGetter();
    ~WebGetter();
    std::string getTrack(); //получение адеса аудио
    std::string getParsedTrack();
};

#endif // WEBGETTER_HPP
