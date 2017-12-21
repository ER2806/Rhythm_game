#include "configmanager.hpp"
#include <iostream>

ConfigurationManager::ConfigurationManager(std::string configname)
{
    std::ifstream in;
    in.open(configname, std::ios_base::in);
    in >> width;
    in >> height;
}

ConfigurationManager::~ConfigurationManager(){}

int ConfigurationManager::getWidth()
{
    return width;
}

int ConfigurationManager::getHeight()
{
    return height;
}
