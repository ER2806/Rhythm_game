#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP
#include <string>
#include <fstream>

class ConfigurationManager{
public:
    ConfigurationManager(std::string configname);
    ~ConfigurationManager();
    int getWidth();
    int getHeight();
private:
    int width;
    int height;
};

#endif // CONFIGMANAGER_HPP
