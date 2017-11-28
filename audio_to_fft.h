#ifndef AUDIO_TO_FFT_HPP
#define AUDIO_TO_FFT_HPP
#include <string>
#include <vector>

class AudioToFFT{
public:
    //AudioToFFT(const std::string& filename);
    //virtual ~AudioToFFT();
    virtual std::vector<float> getFFT(const int fftSize) = 0;
    virtual void startChannelPlay() = 0;
    virtual double getLengthTimeInMsec() = 0;
    virtual double getPlayingTimeInMsec() = 0;
};

#endif // AUDIO_TO_FFT_HPP
