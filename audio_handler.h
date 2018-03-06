#ifndef AUDIOHANDLER_HPP
#define AUDIOHANDLER_HPP
#include <vector>
#include <array>
#include <string>
#include <audio_to_fft_bass.h>

const unsigned SPECHEIGHT = 1000;	// height (changing requires palette adjustments too)
const unsigned BANDS = 3;
const double TDIFF = 50; // setup update timer (20hz)
const unsigned CONVERSION_SAMPLING = 2048;
const unsigned SCALE_FREQ_COEF = 10.0;

class AudioHandler{
public:
    AudioHandler(const std::string& filename, AudioToFFTBass* worker);
    ~AudioHandler();
    void parse();
private:
    class Private;
    Private* private_group;
};

#endif // AUDIOHANDLER_HPP
