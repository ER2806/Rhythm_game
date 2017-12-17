#define DEBUG
#include "audio_handler.h"
#include "audio_to_fft_bass.h"
#include "make_response.h"
#include "physical_response.h"
#include "physical_response_textfile.h"
#include "filter_interface.h"
#include "basic_filter.h"
#include "bass.h"
#include <math.h>
#include "audio_to_fft_bass.h"
#include "audio_to_fft.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <array>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#ifdef DEBUG
void printArray(const std::array<std::vector<int>, BANDS>& array){
    //std::cout << "SIZE " << array[0].size() << std::endl;
    for(int i = 0; i < array[0].size(); ++i){
        //std::cout << "i = " << i << std::endl;
        printf("\n%5.0f: ", (i+1)*TDIFF);
        for(int j = 0; j < BANDS; ++j){
            printf("%.3d ", array[j][i]);
        }
    }
}
#endif
class AudioHandler::Private {
public:
    Private(const std::string& filename, AudioToFFTBass *worker);
    ~Private();
    void buildDotsFromFreq();
    int updateSpectrumInTime();
    //std::vector<std::array<int, BANDS>> dotsArray;

    std::array<std::vector<int>, BANDS> dotsArray;
    std::array<std::vector<int>, BANDS> freqArray;
    std::string sourceFilename;
    std::string dotsFilename;
    DWORD channel;
    AudioToFFT* musicWorker;
};

AudioHandler::Private::Private(const std::string& filename, AudioToFFTBass* worker)
    : sourceFilename(filename), musicWorker(worker){
}

AudioHandler::AudioHandler(const std::string& filename){
    AudioToFFTBass* worker = new AudioToFFTBass(filename);
    private_group = new Private(filename, worker);
}

AudioHandler::~AudioHandler(){
    delete private_group;
}

AudioHandler::Private::~Private(){
    delete musicWorker;
}


int AudioHandler::Private::updateSpectrumInTime(){
    std::array<int, BANDS> temp;
    std::vector<float> fastFT = musicWorker->getFFT(CONVERSION_SAMPLING);
    int b0_coef = 0;
    for(int X = 0; X < BANDS; X++) {
        int Y = 0;
        int maxY = 0;
        float peak = 0;
        int b1_coef = pow(2, X * SCALE_FREQ_COEF/(BANDS - 1));
        b1_coef = (b1_coef > (CONVERSION_SAMPLING/2 - 1)) ? (CONVERSION_SAMPLING/2 - 1) : b1_coef;
        b1_coef = (b0_coef >= b1_coef) ? b0_coef + 1 : b1_coef;
        for (; b0_coef < b1_coef; b0_coef++){
            peak = (peak < fastFT[1 + b0_coef]) ? fastFT[1 + b0_coef] : peak;
            Y = sqrt(peak) * SPECHEIGHT; // scale it (sqrt to make low values more visible)
            if (Y > SPECHEIGHT) Y = SPECHEIGHT; // cap it
            maxY = std::max(maxY, Y);
        }
        freqArray[X].push_back(maxY);
        temp[X] = maxY;
    }
    //freqArray.push_back(temp);
    //printArray(dotsArray);
    return 0;
}

void AudioHandler::parse(){
    private_group->musicWorker->startChannelPlay();
    double musicLength = private_group->musicWorker->getLengthTimeInMsec();
#ifdef DEBUG
    std::cout << musicLength << std::endl;
#endif
    double lastUpdateTime = 0 - TDIFF - TDIFF/100;
    for(double playingTime = 0; playingTime < musicLength;
        playingTime = private_group->musicWorker->getPlayingTimeInMsec()){
        if ((playingTime - lastUpdateTime) >= TDIFF){
            std::cout << playingTime << std::endl;
            lastUpdateTime = playingTime;
            private_group->updateSpectrumInTime();
        }
    }
    //printArray(freqArray);
    private_group->buildDotsFromFreq();
    //printArray(dotsArray);
    FilterInterface* filter = new BasicFilter(private_group->dotsArray);
    private_group->dotsArray = filter->runFilters();
    delete filter;
    //runFilters();
    //printArray(dotsArray);


    PhysicalResponse* physResp = new PhysicalResponseTextfile(private_group->sourceFilename);
    MakeResponse responseHandler(private_group->dotsArray);
    responseHandler.response(physResp);

    delete physResp;
}

void AudioHandler::Private::buildDotsFromFreq(){
    //transform frq to dots where frq amp doubled
    dotsArray = freqArray;
    int lastmin = SPECHEIGHT;
    for(int band = 0; band < BANDS; ++band){
        for(int i = 0; i < freqArray[band].size(); ++i){
            if (freqArray[band][i] > lastmin * 2){
                dotsArray[band][i] = 1;
                lastmin = freqArray[band][i];
            }
            else{
                //std::cout << freqArray.size() << " " << i << " " << band << " " << freqArray[i][band] << std::endl;
                //printArray(freqArray);
                if (lastmin > freqArray[band][i]){
                    lastmin = freqArray[band][i];
                }
                dotsArray[band][i] = 0;
            }
        }
    }
}
