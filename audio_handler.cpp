#define DEBUG
#include "audio_handler.h"
#include "audio_to_fft_bass.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <array>

#ifdef DEBUG
void printArray(const std::vector<std::array<int, BANDS>>& array){
    for(int i = 0; i < array.size(); ++i){
        printf("\n%.5d: ", (i+1)*TDIFF);
        for(int j = 0; j < BANDS; ++j){
            printf("%.3d ", array[i][j]);
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
        temp[X] = maxY;
    }
    freqArray.push_back(temp);
    return 0;
}

void AudioHandler::parse(){
    musicWorker->startChannelPlay();

    double musicLength = musicWorker->getLengthTimeInSeconds();
#ifdef DEBUG
    std::cout << musicLength << std::endl;
#endif
    for(double playingTime = 0; playingTime < musicLength;
        updateSpectrumInTime(), playingTime += TDIFF * 0.001, usleep(TDIFF*1000));
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
