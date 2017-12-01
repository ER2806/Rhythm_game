#include "basic_filter.h"



BasicFilter::BasicFilter(std::array<std::vector<int>, BANDS> dots) : dotsArray(dots){

}




std::array<std::vector<int>, BANDS> BasicFilter::runFilters(){
    for(int band = 0; band < BANDS; ++band){
        for(int i = 0; i < dotsArray[band].size() - 2; i += 2){
            if(dotsArray[band][i] == dotsArray[band][i+1] && dotsArray[band][i] == 1){
                dotsArray[band][i+1] = 0;
            }
        }
        for(int i = 1; i < dotsArray[band].size() - 2; i += 2){
            if(dotsArray[band][i] == dotsArray[band][i+1] && dotsArray[band][i] == 1){
                dotsArray[band][i+1] = 0;
            }
        }
        for(int i = 0; i < dotsArray[band].size() - 4; ++i){
            if(dotsArray[band][i] + dotsArray[band][i+1] + dotsArray[band][i+2] + dotsArray[band][i+3] > 1) {
                if(dotsArray[band][i]){
                    dotsArray[band][i+1] = 0;
                    dotsArray[band][i+2] = 0;
                    dotsArray[band][i+3] = 0;
                }
                else if(dotsArray[band][i+1]){
                    dotsArray[band][i] = 0;
                    dotsArray[band][i+2] = 0;
                    dotsArray[band][i+3] = 0;
                }
                else if(dotsArray[band][i+2]){ dotsArray[band][i+1] = 0;
                    dotsArray[band][i] = 0;
                    dotsArray[band][i+3] = 0;
                }
                else{
                    dotsArray[band][i+1] = 0;
                    dotsArray[band][i+2] = 0;
                    dotsArray[band][i] = 0;
                }
            }
        }
    }
    return dotsArray;
}
