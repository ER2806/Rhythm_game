#ifndef FILTER_INTERFACE_H
#define FILTER_INTERFACE_H
#include <array>
#include <vector>
#include "audio_handler.h"

class FilterInterface
{
public:
    virtual std::array<std::vector<int>, BANDS> runFilters() = 0;
};

#endif // FILTER_INTERFACE_H
