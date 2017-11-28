#include "audio_to_fft_bass.h"

AudioToFFTBass::AudioToFFTBass(const std::string& filename) : audioFilename(filename){
    if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
        //std::cout << "An incorrect version of BASS was loaded" << std::endl;
        // throw
    }

    // initialize BASS
    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        //std::cout << "Can't initialize device" << std::endl;
        //throw
    }
}

AudioToFFTBass::~AudioToFFTBass(){
    BASS_Free();
}

double AudioToFFTBass::getLengthTimeInMsec(){
    QWORD len = BASS_ChannelGetLength(audioChannel, BASS_POS_BYTE); // the length in bytes
    return BASS_ChannelBytes2Seconds(audioChannel, len) * 1000; // the length in seconds
}

double AudioToFFTBass::getPlayingTimeInMsec(){
    QWORD len = BASS_ChannelGetPosition(audioChannel, BASS_POS_BYTE);
    return BASS_ChannelBytes2Seconds(audioChannel, len) * 1000;
}



std::vector<float> AudioToFFTBass::getFFT(const int size){
    float fastFT[2048];
    if(BASS_ChannelGetData(audioChannel, fastFT, BASS_DATA_FFT2048) == -1){ // get the FFT data
        // how to return -1??
    }
    std::vector<float> temp;
    for(int i = 0; i < 2048; ++i){
        temp.push_back(fastFT[i]);
    }
    return temp;
}


void AudioToFFTBass::startChannelPlay(){
    audioChannel = BASS_StreamCreateFile(FALSE, audioFilename.c_str(), 0, 0, 0);
    //std::cout << sourceFilename << " " << channel << " " << BASS_ErrorGetCode() << std::endl;
    //channel = BASS_MusicLoad(FALSE, sourceFilename.c_str(), 0, 0, BASS_MUSIC_RAMP, 1);
    //channel = BASS_MusicLoad(FALSE, "haddawa.wav", 0, 0, BASS_MUSIC_RAMP, 1);
    //std::cout << sourceFilename << " " << channel << " " << BASS_ErrorGetCode() << std::endl;
    if (!BASS_ChannelPlay(audioChannel, FALSE)){
        //std::cout << "FAAAAAAAAAALSE" << std::endl;
        BASS_Free();
        //throw
    }
}
