#include "physical_response_textfile.h"

std::string makeDotsFilename(std::string sourceFilename){
    std::string dotsFilename = sourceFilename;
    int pointInd = dotsFilename.find_last_of('.');
    //if incorrect -> throw
    dotsFilename.erase(pointInd, pointInd + 3);
    dotsFilename = dotsFilename.append(".txt");
    return dotsFilename;
}


PhysicalResponseTextfile::PhysicalResponseTextfile(std::string filename)
    : filename(filename){
}

void PhysicalResponseTextfile::buildPhysicalResponse(std::vector<std::pair<int, int>> data){
    std::string dotsFilename = makeDotsFilename(filename);
    std::ofstream offile;
    offile.open(dotsFilename.c_str(), std::ofstream::out);
    //check file open
    for(int i = 0; i < data.size(); ++i){
        offile << data[i].first << " " << data[i].second << std::endl;
#ifdef DEBUG
        std::cout << dataToWrite[i].first << " " << dataToWrite[i].second << std::endl;
#endif
    }
}





