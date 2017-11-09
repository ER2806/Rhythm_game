#ifndef AUDIOHANDLER_HPP
#define AUDIOHANDLER_HPP
#include <bass.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <array>

#define SPECHEIGHT 1000	// height (changing requires palette adjustments too)
#define BANDS 3
#define TDIFF 50


// select a file to play, and play it
int playFile(const std::string& filename);
int updateSpectrum(std::vector<std::array<int, BANDS>>& array, int time);
void printArrayToFIle(const std::vector<std::array<int, BANDS>>& array);
void printArray(const std::vector<std::array<int, BANDS>>& array);
std::vector<std::array<int, BANDS>> filterArray(const std::vector<std::array<int, BANDS>>& array);
int writeFile(std::string filename, std::vector<std::array<int, BANDS>> array);
int parse(std::string filename);

#endif // AUDIOHANDLER_HPP
