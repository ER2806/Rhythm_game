#include "audio_handler.h"

/*
void printArray(const std::vector<std::array<int, BANDS>>& array){
    for(int i = 0; i < array.size(); ++i){
        printf("\n%.5d: ", (i+1)*TDIFF);
        for(int j = 0; j < BANDS; ++j){
            printf("%.3d ", array[i][j]);
        }
    }
}
*/

AudioHandler::AudioHandler(const std::string& filename) : sourceFilename(filename){
    if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
        std::cout << "An incorrect version of BASS was loaded" << std::endl;
        // throw
    }

    // initialize BASS
    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        std::cout << "Can't initialize device" << std::endl;
        //throw
    }
}

AudioHandler::~AudioHandler(){
    BASS_Free();
}

int AudioHandler::updateSpectrumInTime(){
    std::array<int, BANDS> temp;
    float fastFT[2048];
    if(BASS_ChannelGetData(channel, fastFT, BASS_DATA_FFT2048) == -1){ // get the FFT data
        return 1;
    }
    int b0_coef = 0;
    for(int x = 0; x < BANDS; x++) {
        int y;
        int maxy = 0;
        float peak = 0;
        int b1_coef = pow(2, x * 10.0/(BANDS-1));
        b1_coef = (b1_coef > 1023) ? 1023 : b1_coef;
        b1_coef = (b0_coef >= b1_coef) ? b0_coef + 1 : b1_coef;
        for (; b0_coef < b1_coef; b0_coef++){
            peak = (peak < fastFT[1 + b0_coef]) ? fastFT[1 + b0_coef] : peak;
            y = sqrt(peak) * SPECHEIGHT; // scale it (sqrt to make low values more visible)
            if (y > SPECHEIGHT) y = SPECHEIGHT; // cap it
            maxy = std::max(maxy, y);
        }
        temp[x] = maxy;
    }
    freqArray.push_back(temp);
    return 0;
}

void AudioHandler::startChannelPlay(){
    channel = BASS_StreamCreateFile(FALSE, sourceFilename.c_str(), 0, 0, 0);
    //std::cout << sourceFilename << " " << channel << " " << BASS_ErrorGetCode() << std::endl;
    //channel = BASS_MusicLoad(FALSE, sourceFilename.c_str(), 0, 0, BASS_MUSIC_RAMP, 1);
    //channel = BASS_MusicLoad(FALSE, "haddawa.wav", 0, 0, BASS_MUSIC_RAMP, 1);
    //std::cout << sourceFilename << " " << channel << " " << BASS_ErrorGetCode() << std::endl;
    if (!BASS_ChannelPlay(channel, FALSE)){
        std::cout << "FAAAAAAAAAALSE" << std::endl;
        BASS_Free();
        //throw
    }
}

void AudioHandler::parse(){
    // big try catches
    startChannelPlay();
    while(!updateSpectrumInTime()){
        usleep(TDIFF*1000);
    }
    //printArray(freqArray);
    buildDotsArray();
    runFilters();
    writeToFile();
}

void AudioHandler::buildDotsArray(){
    dotsArray = freqArray;
    int lastmin = SPECHEIGHT;
    for(int band = 0; band < BANDS; ++band){
        for(int i = 0; i < freqArray.size(); ++i){
            if (freqArray[i][band] > lastmin * 2){
                dotsArray[i][band] = 1;
                lastmin = freqArray[i][band];
            }
            else{
                //std::cout << freqArray.size() << " " << i << " " << band << " " << freqArray[i][band] << std::endl;
                //printArray(freqArray);
                if (lastmin > freqArray[i][band]){
                    lastmin = freqArray[i][band];
                }
                dotsArray[i][band] = 0;
            }
        }
    }
}

void AudioHandler::runFilters(){
    for(int band = 0; band < BANDS; ++band){
        for(int i = 0; i < dotsArray.size() - 2; i += 2){
            if(dotsArray[i][band] == dotsArray[i+1][band] && dotsArray[i][band] == 1){
                dotsArray[i+1][band] = 0;
            }
        }
        for(int i = 1; i < dotsArray.size() - 2; i += 2){
            if(dotsArray[i][band] == dotsArray[i+1][band] && dotsArray[i][band] == 1){
                dotsArray[i+1][band] = 0;
            }
        }
        for(int i = 0; i < dotsArray.size() - 4; ++i){
            if(dotsArray[i][band] + dotsArray[i+1][band] + dotsArray[i+2][band] + dotsArray[i+3][band] > 1) {
                if(dotsArray[i][band]){
                    dotsArray[i+1][band] = 0;
                    dotsArray[i+2][band] = 0;
                    dotsArray[i+3][band] = 0;
                }
                else if(dotsArray[i+1][band]){
                    dotsArray[i][band] = 0;
                    dotsArray[i+2][band] = 0;
                    dotsArray[i+3][band] = 0;
                }
                else if(dotsArray[i+2][band]){ dotsArray[i+1][band] = 0;
                    dotsArray[i][band] = 0;
                    dotsArray[i+3][band] = 0;
                }
                else{
                    dotsArray[i+1][band] = 0;
                    dotsArray[i+2][band] = 0;
                    dotsArray[i][band] = 0;
                }
            }
        }
    }
    //printArray(dotsArray);
}


void AudioHandler::makeDotsFilename(){
    dotsFilename = sourceFilename;
    int pointInd = dotsFilename.find_last_of('.');
    //if incorrect -> throw
    dotsFilename.erase(pointInd, pointInd + 3);
    dotsFilename = dotsFilename.append(".txt");
}

void AudioHandler::writeToFile(){
    //file signature (time band) ... (time band)
    std::vector<std::pair<int, int>> answer;
    for(int i = 0; i < dotsArray.size(); ++i){
        for(int band = 0; band < BANDS; ++band){
            if(dotsArray[i][band]){
                std::pair<int, int> temp;
                temp.first = (i+1)*TDIFF;
                temp.second = band;
                answer.push_back(temp);
            }
        }
    }

    makeDotsFilename();
    std::ofstream offile;
    offile.open(dotsFilename.c_str(), std::ofstream::out);
    //check file open
    for(int i = 0; i < answer.size(); ++i){
        offile << answer[i].first << " " << answer[i].second << std::endl;
    }
    //std::cout << dotsFilename << std::endl;
}
