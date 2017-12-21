#include "sphere.hpp"

Sphere::Sphere(sf::Texture& texture, int radius, sf::Color color, int posx, int posy)
{
    sphere.setTexture(texture);
    sphere.setTextureRect(sf::IntRect(0, 0, radius*2, radius*2));
    sphere.setColor(color);
    sphere.setPosition(posx, posy);
}

Sphere::~Sphere()
{}

void Sphere::setPosition(int posx, int posy)
{
    sphere.move(posx, posy);
}

int Sphere::getPositionY() const
{
    return sphere.getPosition().y;
}

sf::Color Sphere::getColor() const
{
    return sphere.getColor();
}

void Sphere::setColor(sf::Color color)
{
    sphere.setColor(color);
}

sf::Sprite Sphere::getSphere() const
{
    return sphere;
}

void Sphere::recieveSignal()
{
    sphere.setColor(activeColor);
}
