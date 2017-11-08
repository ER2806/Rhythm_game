#include <string>
#include "audiohandler.hpp"

int main(int argc, char* argv[]){
    std::string filename = "/home/qskwx/Music/haddawa.wav";
    std::cout << parse(filename) << std::endl;
    return 0;
}

