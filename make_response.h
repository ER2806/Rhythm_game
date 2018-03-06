#ifndef MAKE_RESPONSE_HPP
#define MAKE_RESPONSE_HPP
#include "audio_handler.h"
#include "physical_response.h"
#include <algorithm>

class MakeResponse
{
public:
    MakeResponse(std::array<std::vector<int>, BANDS> dotsArray);
    void response(PhysicalResponse* responseManager);
private:
    std::vector<std::pair<int, int>> answer;
};

#endif // MAKE_RESPONSE_HPP
