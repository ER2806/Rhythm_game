#ifndef AUDIOTOFFTBASS_HPP
#define AUDIOTOFFTBASS_HPP
#include "audio_to_fft.h"
#include <bass.h>

class AudioToFFTBass : public AudioToFFT {
public:
    AudioToFFTBass(const std::string& filename);
    ~AudioToFFTBass();
    std::vector<float> getFFT(const int fftSize);
    void startChannelPlay();
    double getLengthTimeInMsec();
    double getPlayingTimeInMsec();
private:
    DWORD audioChannel;
    std::string audioFilename;
};

#endif // AUDIOTOFFTBASS_HPP
