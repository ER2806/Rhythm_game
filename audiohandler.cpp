#include "audiohandler.hpp"

DWORD chan;

// select a file to play, and play it
int playFile(const std::string& filename){
    if (!(chan=BASS_StreamCreateFile(FALSE,filename.c_str(),0,0,0))//BASS_SAMPLE_LOOP))
        && !(chan=BASS_MusicLoad(FALSE,filename.c_str(),0,0,BASS_MUSIC_RAMP,1))){//|BASS_SAMPLE_LOOP,1))) {
        return 0;
    }
    else {
        BASS_ChannelPlay(chan,FALSE);
        //std::cout << "GREAT" << std::endl;
        return -1;
    }
}

// update the spectrum display - the interesting bit :)
int UpdateSpectrum(std::vector<std::array<int, BANDS>>& array, int time){
    std::array<int, BANDS> temp;
    float fft[2048];
    int returnval = BASS_ChannelGetData(chan,fft,BASS_DATA_FFT2048); // get the FFT data
    int b0 = 0;
    for (int x = 0; x < BANDS; x++) {
        int y;
        int maxy = 0;
        float peak = 0;
        int b1 = pow(2, x*10.0/(BANDS-1));
        if (b1 > 1023) b1 = 1023;
        if (b1 <= b0) b1 = b0 + 1; // make sure it uses at least 1 FFT bin
        for ( ; b0 < b1; b0++){
            if (peak < fft[1 + b0]) peak = fft[1 + b0];
            y = sqrt(peak) * SPECHEIGHT; // scale it (sqrt to make low values more visible)
            if (y > SPECHEIGHT) y = SPECHEIGHT; // cap it
            maxy = std::max(maxy, y);
        }
        temp[x] = maxy;
    }
    array.push_back(temp);

    return returnval != -1;
}

void printArrayToFIle(const std::vector<std::array<int, BANDS>>& array){
    FILE* f = fopen("output.txt", "w");
    for(int i = 0; i < array.size(); ++i){
        fprintf(f, "\n%.5d: ", (i+1)*TDIFF);
        for(int j = 0; j < BANDS; ++j){
            fprintf(f, "%.3d ", array[i][j]);
        }
    }
}

void printArray(const std::vector<std::array<int, BANDS>>& array){
    for(int i = 0; i < array.size(); ++i){
        printf("\n%.5d: ", (i+1)*TDIFF);
        for(int j = 0; j < BANDS; ++j){
            printf("%.3d ", array[i][j]);
        }
    }
}

std::vector<std::array<int, BANDS>> filterArray(const std::vector<std::array<int, BANDS>>& array){
    std::vector<std::array<int, BANDS>> dotsOnBands = array;
    int lastmin = SPECHEIGHT;
    for(int band = 0; band < BANDS; ++band){
        for(int i = 0; i < array.size(); ++i){
            if (array[i][band] > lastmin*2){
                dotsOnBands[i][band] = 1;
                lastmin = array[i][band];
            }
            else{
                if (lastmin > array[i][band]){
                    lastmin = array[i][band];
                }
                dotsOnBands[i][band] = 0;
            }
        }
    }
    for(int band = 0; band < BANDS; ++band){
        for(int i = 0; i < dotsOnBands.size() - 2; i += 2){
            if(dotsOnBands[i][band] == dotsOnBands[i+1][band] && dotsOnBands[i][band] == 1){
                dotsOnBands[i+1][band] = 0;
            }
        }
        for(int i = 1; i < dotsOnBands.size() - 2; i += 2){
            if(dotsOnBands[i][band] == dotsOnBands[i+1][band] && dotsOnBands[i][band] == 1){
                dotsOnBands[i+1][band] = 0;
            }
        }
        for(int i = 0; i < dotsOnBands.size() - 4; ++i){
            if(dotsOnBands[i][band] + dotsOnBands[i+1][band] + dotsOnBands[i+2][band] + dotsOnBands[i+3][band] > 1) {
                if(dotsOnBands[i][band]){
                    dotsOnBands[i+1][band] = 0;
                    dotsOnBands[i+2][band] = 0;
                    dotsOnBands[i+3][band] = 0;
                }
                else if(dotsOnBands[i+1][band]){
                    dotsOnBands[i][band] = 0;
                    dotsOnBands[i+2][band] = 0;
                    dotsOnBands[i+3][band] = 0;
                }
                else if(dotsOnBands[i+2][band]){
                    dotsOnBands[i+1][band] = 0;
                    dotsOnBands[i][band] = 0;
                    dotsOnBands[i+3][band] = 0;
                }
                else{
                    dotsOnBands[i+1][band] = 0;
                    dotsOnBands[i+2][band] = 0;
                    dotsOnBands[i][band] = 0;
                }

            }
        }
    }
    printArray(dotsOnBands);
    return dotsOnBands;
}

int writeFile(std::string filename, std::vector<std::array<int, BANDS>> array){
    std::vector<std::pair<int, int>> answer;
    for(int i = 0; i < array.size(); ++i){
        for(int band = 0; band < BANDS; ++band){
            if(array[i][band]){
                std::pair<int, int> temp;
                temp.first = (i+1)*TDIFF;
                temp.second = band;
                answer.push_back(temp);
            }
        }
    }
    std::cout << "\n";
    std::cout << answer.size() << std::endl;
    for(int i = 0; i < answer.size(); ++i){
        std::cout << answer[i].first << answer[i].second << std::endl;
    }

    int pointInd = filename.find_last_of('/');
    filename.erase(0, pointInd+1);
    //std::cout << filename << std::endl;
    pointInd = filename.find_first_of('.');
    filename.erase(pointInd, pointInd+3);
    filename = filename.append(".txt");

    FILE* f = fopen(filename.c_str(), "w");
    for(int i = 0; i < answer.size(); ++i){
        fprintf(f, "%d %d\n", answer[i].first, answer[i].second);
    }
    fclose(f);
}

int parse(std::string filename){
    if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
        std::cout << "An incorrect version of BASS was loaded" << std::endl;
        return -1;
    }

    // initialize BASS
    if (!BASS_Init(-1,44100,0,NULL,NULL)) {
        std::cout << "Can't initialize device" << std::endl;
        return -1;
    }

    if (!playFile(filename)) { // start a file playing
        std::cout << "Can't play" << std::endl;
        BASS_Free();
        return -1;
    }

    std::vector<std::array<int, BANDS>> array;

    // setup update timer (20hz)
    bool returnval = true;
    int i = 0;
    while(returnval){
        i += 50;
        usleep(TDIFF*1000);
        returnval = UpdateSpectrum(array, i);
    }

    printArray(array);
    std::vector<std::array<int, BANDS>> result = filterArray(array);
    printArray(result);

    writeFile(filename, result);

    BASS_Free();
    return 0;

}

