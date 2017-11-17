#include <string>
#include "audio_handler.h"

int main(int argc, char* argv[]){
    std::string filename = "/home/qskwx/Music/haddawa.wav";
    //std::cout << parse(filename) << std::endl;
    AudioHandler testHandle(filename);
    testHandle.parse();
    return 0;
}

