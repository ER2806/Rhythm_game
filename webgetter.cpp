#include "webgetter.hpp"

WebGetter::WebGetter()
{}

WebGetter::~WebGetter()
{}

std::string WebGetter::getTrack() //получение адеса аудио
{
    #ifndef NON_MERGING
    QApplication a(argc, argv);
    Client webClient(getIpAddr(), getPort());
    uint8_t errorCode;
    std::string request = "haddawa.wav";
    std::string audioFilename = webClient.getTrackFromServer(errorCode, request);
    #endif
    return "haddawa.wav";
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
