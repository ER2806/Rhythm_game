#ifndef AUDIOHANDLER_HPP
#define AUDIOHANDLER_HPP
#include <vector>
#include <array>
#include <string>
#include <bass.h>
#include <audio_to_fft_bass.h>
#include <audio_to_fft.h>

const unsigned SPECHEIGHT = 1000;	// height (changing requires palette adjustments too)
const unsigned BANDS = 3;
const double TDIFF = 50; // setup update timer (20hz)

class AudioHandler{
public:
    AudioHandler(const std::string& filename);
    ~AudioHandler();
    void parse();
private:
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

#endif // AUDIOHANDLER_HPP
