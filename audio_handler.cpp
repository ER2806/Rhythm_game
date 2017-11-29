#define DEBUG
#include "audio_handler.h"
#include "audio_to_fft_bass.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <array>

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

AudioHandler::AudioHandler(const std::string& filename) : sourceFilename(filename){
    musicWorker = new AudioToFFTBass(filename);
}

AudioHandler::~AudioHandler(){
    delete musicWorker;
}

int AudioHandler::updateSpectrumInTime(){
    std::array<int, BANDS> temp;
    std::vector<float> fastFT = musicWorker->getFFT(2048);
    int b0_coef = 0;
    for(int X = 0; X < BANDS; X++) {
        int Y = 0;
        int maxY = 0;
        float peak = 0;
        int b1_coef = pow(2, X * 10.0/(BANDS-1));
        b1_coef = (b1_coef > 1023) ? 1023 : b1_coef;
        b1_coef = (b0_coef >= b1_coef) ? b0_coef + 1 : b1_coef;
        for (; b0_coef < b1_coef; b0_coef++){
            peak = (peak < fastFT[1 + b0_coef]) ? fastFT[1 + b0_coef] : peak;
            Y = sqrt(peak) * SPECHEIGHT; // scale it (sqrt to make low values more visible)
            if (Y > SPECHEIGHT) Y = SPECHEIGHT; // cap it
            maxY = std::max(maxY, Y);
        }
        freqArray[X].push_back(maxY); //
        temp[X] = maxY;
    }
    //freqArray.push_back(temp);
    //printArray(dotsArray);
    return 0;
}

void AudioHandler::parse(){
    musicWorker->startChannelPlay();

    double musicLength = musicWorker->getLengthTimeInMsec();
#ifdef DEBUG
    std::cout << musicLength << std::endl;
#endif
    double lastUpdateTime = 0 - TDIFF - TDIFF/100;
    for(double playingTime = 0; playingTime < musicLength;
        playingTime = musicWorker->getPlayingTimeInMsec()){
        if ((playingTime - lastUpdateTime) >= TDIFF){
            std::cout << playingTime << std::endl;
            lastUpdateTime = playingTime;
            updateSpectrumInTime();
        }
    }
    printArray(freqArray);
    buildDotsArray();
    printArray(dotsArray);
    runFilters();
    printArray(dotsArray);
    writeToFile();
}

void AudioHandler::buildDotsArray(){
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

void AudioHandler::runFilters(){
    for(int band = 0; band < BANDS; ++band){
        for(int i = 0; i < dotsArray[band].size() - 2; i += 2){
            if(dotsArray[band][i] == dotsArray[band][i+1] && dotsArray[band][i] == 1){
                dotsArray[band][i+1] = 0;
            }
        }
        for(int i = 1; i < dotsArray[band].size() - 2; i += 2){
            if(dotsArray[band][i] == dotsArray[band][i+1] && dotsArray[band][i] == 1){
                dotsArray[band][i+1] = 0;
            }
        }
        for(int i = 0; i < dotsArray[band].size() - 4; ++i){
            if(dotsArray[band][i] + dotsArray[band][i+1] + dotsArray[band][i+2] + dotsArray[band][i+3] > 1) {
                if(dotsArray[band][i]){
                    dotsArray[band][i+1] = 0;
                    dotsArray[band][i+2] = 0;
                    dotsArray[band][i+3] = 0;
                }
                else if(dotsArray[band][i+1]){
                    dotsArray[band][i] = 0;
                    dotsArray[band][i+2] = 0;
                    dotsArray[band][i+3] = 0;
                }
                else if(dotsArray[band][i+2]){ dotsArray[band][i+1] = 0;
                    dotsArray[band][i] = 0;
                    dotsArray[band][i+3] = 0;
                }
                else{
                    dotsArray[band][i+1] = 0;
                    dotsArray[band][i+2] = 0;
                    dotsArray[band][i] = 0;
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
    for(int i = 0; i < dotsArray[0].size(); ++i){
        for(int band = 0; band < BANDS; ++band){
            if(dotsArray[band][i]){
                auto temp = std::make_pair((i+1)*TDIFF, band);
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
#ifdef DEBUG
        std::cout << answer[i].first << " " << answer[i].second << std::endl;
#endif
    }
    //std::cout << dotsFilename << std::endl;
}
