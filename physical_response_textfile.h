#ifndef PHYSICALL_RESPONSE_TEXTFILE_HPP
#define PHYSICALL_RESPONSE_TEXTFILE_HPP
#include "physical_response.h"
#include <string>
#include <iostream>
#include <fstream>
class PhysicalResponseTextfile : public PhysicalResponse
{
public:
    //PhysicalResponseTextfile();
    PhysicalResponseTextfile(std::string filename);
    void buildPhysicalResponse(std::vector<std::pair<int, int>> data);
private:
    std::string filename;
};

#endif // PHYSICALL_RESPONSE_TEXTFILE_HPP
