#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <SFML/Graphics.hpp>

class Button {
public:
    Button (sf::Texture& texture, std::string text, sf::Font &font, int posx, int posy);
    ~Button();
    sf::Sprite get() const;
    sf::Text getText() const;
private:
    sf::Sprite button;
    sf::Text text;
};


#endif // BUTTON_HPP
