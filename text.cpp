#include "text.hpp"

Text::Text(sf::Font &font, int size, sf::Color color, int posx, int posy)
{
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(posx,posy);
}

Text::~Text()
{}

void Text::setValue(int value)
{
    text.setString(std::to_string(value));
}

sf::Text Text::get() const
{
    return text;
}
