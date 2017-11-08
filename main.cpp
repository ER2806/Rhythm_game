#include <bass.h>

#include <gtk/gtk.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include "bass.h"
#include "iostream"
#include "stdio.h"
#include "unistd.h"
#include <vector>

#define SPECWIDTH 368	// display width (should be multiple of 4)
#define SPECHEIGHT 1000	// height (changing requires palette adjustments too)
#define BANDS 3
#define TDIFF 50
/*
*/
DWORD chan;

struct quantum{
    int* y_line;

    quantum(){
        y_line = new int[BANDS];
    }
    quantum(const quantum& other){
        y_line = new int[BANDS];
        for(int i = 0; i < BANDS; ++i){
            y_line[i] = other.y_line[i];
        }
    }
    ~quantum(){
        delete[] y_line;
    }
};

// select a file to play, and play it
BOOL PlayFile(const std::string& filename){
    char* file = new char[100];
    //strcpy(file, "/home/qskwx/Music/Skrillexfeat.mp3");
    //strcpy(file, filename.c_str());//"/home/qskwx/Music/stilldre.mp3");
    //strcpy(file, "/home/qskwx/Music/haddawa.wav");

    if (!(chan=BASS_StreamCreateFile(FALSE,filename.c_str(),0,0,0))//BASS_SAMPLE_LOOP))
        && !(chan=BASS_MusicLoad(FALSE,filename.c_str(),0,0,BASS_MUSIC_RAMP,1))){//|BASS_SAMPLE_LOOP,1))) {
            //Error("Can't play file");
    }
    else {
        BASS_ChannelPlay(chan,FALSE);
    }
}

// update the spectrum display - the interesting bit :)
bool UpdateSpectrum(std::vector<quantum>& array, int time){
    quantum temp;
    int x,y;
    float fft[2048];
    int returnval = BASS_ChannelGetData(chan,fft,BASS_DATA_FFT2048); // get the FFT data
    int b0 = 0;
    for (x = 0; x < BANDS; x++) {
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
        //printf("%.4d ", maxy);
        temp.y_line[x] = maxy;
    }
    array.push_back(temp);
    //std::cout << std::endl;

    return returnval != -1;
}

void printArrayToFIle(std::vector<quantum> array){
    FILE* f = fopen("output.txt", "w");
    for(int i = 0; i < array.size(); ++i){
        fprintf(f, "\n%.5d: ", (i+1)*TDIFF);
        for(int j = 0; j < BANDS; ++j){
            fprintf(f, "%.3d ", array[i].y_line[j]);
        }
    }
}

void printArray(std::vector<quantum> array){
    for(int i = 0; i < array.size(); ++i){
        printf("\n%.5d: ", (i+1)*TDIFF);
        for(int j = 0; j < BANDS; ++j){
            printf("%.3d ", array[i].y_line[j]);
        }
    }
}

std::vector<quantum> filterArray(std::vector<quantum> array){
    std::vector<quantum> dotsOnBands = array;
    int lastmin = SPECHEIGHT;
    for(int band = 0; band < BANDS; ++band){
        for(int i = 0; i < array.size(); ++i){
            if (array[i].y_line[band] > lastmin*1.5){
                dotsOnBands[i].y_line[band] = 1;
                lastmin = array[i].y_line[band];
            }
            else{
                if (lastmin > array[i].y_line[band]){
                    lastmin = array[i].y_line[band];
                }
                dotsOnBands[i].y_line[band] = 0;
            }
        }
    }
    for(int band = 0; band < BANDS; ++band){
        for(int i = 0; i < dotsOnBands.size() - 2; i += 2){
            if(dotsOnBands[i].y_line[band] == dotsOnBands[i+1].y_line[band] && dotsOnBands[i].y_line[band] == 1){
                dotsOnBands[i+1].y_line[band] = 0;
            }
        }
        for(int i = 1; i < dotsOnBands.size() - 2; i += 2){
            if(dotsOnBands[i].y_line[band] == dotsOnBands[i+1].y_line[band] && dotsOnBands[i].y_line[band] == 1){
                dotsOnBands[i+1].y_line[band] = 0;
            }
        }
    }
    printArray(dotsOnBands);
}

std::vector<std::pair<int, int>> generateAnswer(std::vector<quantum> array){
    std::vector<std::pair<int, int>> result;
    for(int i = 0; i < array.size(); ++i){
        for(int band = 0; band < BANDS; ++band){
            if(array[i].y_line[band]){
                std::pair<int, int> temp;
                temp.first = (i+1)*TDIFF;
                temp.second = band;
                result.push_back(temp);
            }
        }
    }
    return result;
}

bool parse(std::string filename){
    if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
        //Error("An incorrect version of BASS was loaded");
        return -1;
    }

    // initialize BASS
    if (!BASS_Init(-1,44100,0,NULL,NULL)) {
        //Error("Can't initialize device");
        return -1;
    }

    if (!PlayFile(filename)) { // start a file playing
        BASS_Free();
        return -1;
    }

    std::vector<quantum> array;

    // setup update timer (20hz)
    bool returnval = true;
    int i = 0;
    while(returnval){
        i += 50;
        usleep(TDIFF*1000);
        returnval = UpdateSpectrum(array, i);
    }

    printArray(array);
    std::vector<quantum> result = filterArray(array);


    BASS_Free();
    return 0;

}


int main(int argc, char* argv[]){
    std::string filename = "/home/qskwx/Music/haddawa.wav";
    parse(filename);

    return 0;
}

