#include "physical_response_textfile.h"
#define DEBUG

std::string makeDotsFilename(std::string sourceFilename){
    std::string dotsFilename = sourceFilename;
    int pointInd = dotsFilename.find_last_of('.');
    //if incorrect -> throw
    dotsFilename.erase(pointInd, pointInd + 3); // 3 letters crutch for extension
    dotsFilename = dotsFilename.append(".txt");
    return dotsFilename;
}


PhysicalResponseTextfile::PhysicalResponseTextfile(std::string filename)
    : filename(filename){
}

void PhysicalResponseTextfile::buildPhysicalResponse(std::vector<std::pair<int, int>> data){
    std::string dotsFilename = makeDotsFilename(filename);
    std::ofstream offile;
    //check file open
    offile.open(dotsFilename.c_str(), std::ofstream::out);
    for(const auto elm: data){
#ifdef DEBUG
        std::cout << elm.first << " " << elm.second << std::endl;
#endif
        offile << elm.first << " " << elm.second << std::endl;
    }
}





