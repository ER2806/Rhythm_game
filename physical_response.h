#ifndef PHYSICALL_RESPONSE_HPP
#define PHYSICALL_RESPONSE_HPP
#include <vector>

class PhysicalResponse
{
public:
    virtual void buildPhysicalResponse(std::vector<std::pair<int, int>> data) = 0;
};

#endif // PHYSICALL_RESPONSE_HPP
