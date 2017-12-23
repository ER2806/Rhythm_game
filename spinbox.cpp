#include "spinbox.hpp"

SpinBox::SpinBox(sf::Texture &texture, int posx, int posy, std::vector<std::string> values, sf::Font &font): px(posx), py(posy), ValuesArray(values)
{
    spinbox.setTexture(texture, true);
    spinbox.setTextureRect(sf::IntRect(0, 0, 500, 80));
    spinbox.setColor(sf::Color(255, 255, 255, 255));
    spinbox.setPosition(px, py);
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    text.setPosition(px+40, py+10);
    if(ValuesArray.size() != 0)
        text.setString(ValuesArray[0]);
}

SpinBox::~SpinBox()
{}

void SpinBox::setText(std::string t)
{
    text.setString(t);
}

sf::Sprite SpinBox::getSpinBox() const
{
    return spinbox;
}

sf::Text SpinBox::getText() const
{
    return text;
}

void SpinBox::next()
{
    if(current < ValuesArray.size())
    {
        current++;
        text.setString(ValuesArray[current]);
    }
}

void SpinBox::prev()
{
    if(current > 0)
    {
        current--;
        text.setString(ValuesArray[current]);
    }
}

int SpinBox::getNumber()
{
    return current;
}
