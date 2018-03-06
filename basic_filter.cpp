#include "basic_filter.h"
#include <functional>
#include <algorithm>
#include <iostream>


BasicFilter::BasicFilter(std::array<std::vector<int>, BANDS> dots) : dotsArray(dots){

}

// function on each group
// lambda test
void BasicFilter::forEachDotsArrayGroup(std::vector<int>& line, int startIdx, int groupsize, void (*Handler)(std::vector<int>& line, int groupStartIdx)){
    // million of index checks
    int lastGroupStartingIdx = (line.size() - startIdx - line.size() % groupsize) - groupsize - 1;
    for(int i = 0; i <= lastGroupStartingIdx; i += groupsize){
        Handler(line, i);
    }
}


std::array<std::vector<int>, BANDS> BasicFilter::runFilters(){
    for(int band = 0; band < BANDS; ++band){
        int groupsize = 2;
        int startpos = 0;

        /* at first filtrate each pair of dotsArray, killing the pair dots to one dot */
        forEachDotsArrayGroup(dotsArray[band], startpos, groupsize,
                              [](std::vector<int>& line, int groupStartIdx){
            if(line[groupStartIdx] == line[groupStartIdx + 1] && line[groupStartIdx] == 1){
                line[groupStartIdx + 1] = 0;
            }
        });

        groupsize = 2;
        startpos = 1;
        forEachDotsArrayGroup(dotsArray[band], startpos, groupsize,
                              [](std::vector<int>& line, int groupStartIdx){
            if(line[groupStartIdx] == line[groupStartIdx + 1] && line[groupStartIdx] == 1){
                line[groupStartIdx + 1] = 0;
            }
        });

        /* at second filtrate each 4 dots, (4 dots - 200 ms) to make them nonlagging*/
        groupsize = 4;
        startpos = 0;
        forEachDotsArrayGroup(dotsArray[band], startpos, groupsize,
                              [](std::vector<int>& line, int groupStartIdx){
                if(line[groupStartIdx] + line[groupStartIdx+1] + line[groupStartIdx+2] + line[groupStartIdx+3] > 1) {
                    /* make zeros in all points besides one */
                    if(line[groupStartIdx]){
                        line[groupStartIdx + 1] = 0;
                        line[groupStartIdx + 2] = 0;
                        line[groupStartIdx + 3] = 0;
                    }
                    else if(line[groupStartIdx + 1]){
                        line[groupStartIdx + 2] = 0;
                        line[groupStartIdx + 3] = 0;
                    }
                    else if(line[groupStartIdx + 2]){
                        line[groupStartIdx + 3] = 0;
                    }
                }
            }
        );
    }
    return dotsArray;
}
