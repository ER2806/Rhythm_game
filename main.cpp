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
/*
*/
DWORD chan;

struct quantum{
    int x;
    int* y_line;

    quantum(){
        y_line = new int[BANDS];
    }
    quantum(const quantum& other){
        y_line = new int[BANDS];
        for(int i = 0; i < BANDS; ++i){
            y_line[i] = other.y_line[i];
        }
        x = other.x;
    }

    ~quantum(){
        delete[] y_line;
    }
};

// select a file to play, and play it
BOOL PlayFile(){
    char* file = new char[100];
    //strcpy(file, "/home/qskwx/Music/Skrillexfeat.mp3");
    //strcpy(file, "/home/qskwx/Music/stilldre.mp3");
    strcpy(file, "/home/qskwx/Music/haddawa.wav");

    if (!(chan=BASS_StreamCreateFile(FALSE,file,0,0,0))//BASS_SAMPLE_LOOP))
        && !(chan=BASS_MusicLoad(FALSE,file,0,0,BASS_MUSIC_RAMP,1))){//|BASS_SAMPLE_LOOP,1))) {
            //Error("Can't play file");
    }
    else {
        BASS_ChannelPlay(chan,FALSE);
    }
}

// update the spectrum display - the interesting bit :)
bool UpdateSpectrum(std::vector<quantum>& array, int time){
    quantum temp;
    temp.x = time;
    int x,y,y1;
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

int main(int argc, char* argv[])
{
    if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
        //Error("An incorrect version of BASS was loaded");
        return 0;
    }

    // initialize BASS
    if (!BASS_Init(-1,44100,0,NULL,NULL)) {
        //Error("Can't initialize device");
        return 0;
    }

    if (!PlayFile()) { // start a file playing
        BASS_Free();
        return 0;
    }

    // setup update timer (40hz)

    std::vector<quantum> array;

    bool returnval = true;
    int i = 0;
    while(returnval){
        i += 50;
        usleep(50000);
        returnval = UpdateSpectrum(array, i);
    }
    for(int i = 0; i < array.size(); ++i){
        printf("\n%.5d: ", array[i].x);
        for(int j = 0; j < BANDS; ++j){
            printf("%.3d ", array[i].y_line[j]);
        }
    }


    BASS_Free();
    return 0;
}
