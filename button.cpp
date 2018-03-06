#include "button.hpp"

Button::Button(sf::Texture &texture, std::string t, sf::Font& font, int posx, int posy) {
    button.setTexture(texture, true);
    button.setTextureRect(sf::IntRect(0, 0, 240, 56));
    button.setColor(sf::Color(255, 255, 255, 255));
    button.setPosition(posx, posy);
    text.setFont(font);
    text.setCharacterSize(24);
    text.setString(t);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    text.setPosition(posx + (8-t.length()/2)*15, posy+10);
}

Button::~Button()
{}

sf::Sprite Button::get() const
{
    return button;
}

sf::Text Button::getText() const
{
    return text;
}
