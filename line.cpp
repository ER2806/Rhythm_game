#include "line.hpp"

Line::Line(int length, int thickness,int posx, int posy, int rotationAngle)
{
    sf::RectangleShape l(sf::Vector2f(length, thickness));
    l.setPosition(posx, posy);
    l.rotate(rotationAngle);
    line = l;
}

Line::~Line()
{}

sf::RectangleShape Line::getLine() const
{
    return line;
}
