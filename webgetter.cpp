#include "webgetter.hpp"

WebGetter::WebGetter()
{}

WebGetter::~WebGetter()
{}

std::string WebGetter::getTrack(int number) //получение адеса аудио
{
    #ifndef NON_MERGING
    QApplication a(argc, argv);
    Client webClient(getIpAddr(), getPort());
    uint8_t errorCode;
    std::string request = "haddawa.wav";
    std::string audioFilename = webClient.getTrackFromServer(errorCode, request);
    #endif
    switch(number)
    {
        case 0:
            return "haddawa.wav";
        case 1:
            return "haddawa2.wav";
        default:
            return "haddawa.wav";
    }
}

std::string WebGetter::getParsedTrack()
{
    #ifndef NON_MERGING
    request = "haddawa.wav";
    std::string textFilename = webClient.getParsedTrackFromServer(errorCode, request);
    std::cout << textFilename << std::endl;
    #endif
    return "test.txt";
}

std::vector<std::string> WebGetter::getTrackList()
{
    #ifndef NON_MERGING
    // что-то с сервера
    #endif
    std::vector<std::string> temp;
    temp.push_back("Haddaway - what is love");
    temp.push_back("Haddaway - what is love2");
    temp.push_back("There is no song yet");
    return temp;
}
