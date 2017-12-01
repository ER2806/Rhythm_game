#ifndef BASIC_FILTER_HPP
#define BASIC_FILTER_HPP
#include "filter_interface.h"
#include "audio_handler.h"
#include <vector>
#include <array>

class BasicFilter : public FilterInterface
{
public:
    BasicFilter(std::array<std::vector<int>, BANDS> dots);
    std::array<std::vector<int>, BANDS> runFilters();
private:
    std::array<std::vector<int>, BANDS> dotsArray;
};

#endif // BASIC_FILTER_HPP
