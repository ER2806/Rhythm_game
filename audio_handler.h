#ifndef AUDIOHANDLER_HPP
#define AUDIOHANDLER_HPP
#include <bass.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <array>

#define SPECHEIGHT 1000	// height (changing requires palette adjustments too)
#define BANDS 3
#define TDIFF 50 // setup update timer (20hz)

class AudioHandler{
public:
    AudioHandler(const std::string& filename);
    ~AudioHandler();
    void parse();
private:
    void writeToFile();
    void buildDotsArray();
    void runFilters();
    void startChannelPlay();
    void makeDotsFilename();
    int updateSpectrumInTime();
    std::vector<std::array<int, BANDS>> dotsArray;
    std::vector<std::array<int, BANDS>> freqArray;
    std::string sourceFilename;
    std::string dotsFilename;
    DWORD channel;
};

#endif // AUDIOHANDLER_HPP
