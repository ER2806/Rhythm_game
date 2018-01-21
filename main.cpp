#include <string>
#include <iostream>
#include "audio_handler.h"
#include "audio_to_fft_bass.h"

int main(int argc, char* argv[]){
    if (argc == 3){
        if (argv[1] == "-t"){
            std::string filename = argv[2];
            std::cout << TDIFF << std::endl;
            //std::cout << parse(filename) << std::endl;

            AudioToFFTBass* musicWorker = new AudioToFFTBass(filename);
            AudioHandler testHandle(filename, musicWorker);
            testHandle.parse();
            delete musicWorker;
        }
    }
    return 0;
}

