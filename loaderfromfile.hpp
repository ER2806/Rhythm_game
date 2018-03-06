#ifndef LOADERFROMFILE_HPP
#define LOADERFROMFILE_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "loader.hpp"

class LoaderFromFile: public Loader{
public:
    LoaderFromFile();
    ~LoaderFromFile();
    void LoadFont(std::string filename, sf::Font &font);
    void LoadTexture(std::string filename, sf::Texture& texture);
};

#endif // LOADERFROMFILE_HPP


