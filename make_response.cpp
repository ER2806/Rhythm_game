#include "make_response.h"


MakeResponse::MakeResponse(std::array<std::vector<int>, BANDS> dotsArray) {
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
