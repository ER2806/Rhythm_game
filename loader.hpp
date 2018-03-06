#ifndef LOADER_HPP
#define LOADER_HPP

class Loader{
public:
    virtual void LoadFont(std::string filename, sf::Font &font) = 0;
    virtual void LoadTexture(std::string filename, sf::Texture& texture) = 0;
};

#endif // LOADER_HPP
