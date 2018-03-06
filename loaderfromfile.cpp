#include "loaderfromfile.hpp"

LoaderFromFile::LoaderFromFile(){}

LoaderFromFile::~LoaderFromFile(){}

void LoaderFromFile::LoadFont(std::string filename, sf::Font& font)
{
    font.loadFromFile(filename);
}

void LoaderFromFile::LoadTexture(std::string filename, sf::Texture& texture)
{
    texture.loadFromFile(filename);
}
