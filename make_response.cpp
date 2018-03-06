#include "make_response.h"
#include <iostream>


MakeResponse::MakeResponse(std::array<std::vector<int>, BANDS> dotsArray) {
    /*
    for(int line = 0; line < dotsArray.size(); ++line){
        std::for_each(dotsArray[line].begin(), dotsArray[line].end(),
                      [this, dotsArray, line](auto& elm){
                if(elm != 0) {
                //auto temp = std::make_pair((i+1)*TDIFF, band);
                    std::cout << (&elm - dotsArray[line][0])/sizeof(int*) << std::endl;
                    answer.push_back(
                                std::make_pair(
                                    static_cast<int>((&elm - &dotsArray[line][0] + 1) * TDIFF), line)
                                );
            };});
    }*/

    for(int i = 0; i < dotsArray[0].size(); ++i){
        for(int band = 0; band < BANDS; ++band){
            if(dotsArray[band][i]){
                auto temp = std::make_pair((i+1)*TDIFF, band);
                answer.push_back(temp);
            }
        }
    }
}

void MakeResponse::response(PhysicalResponse* responseManager){
    responseManager->buildPhysicalResponse(answer);
}
