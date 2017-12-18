#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <SFML/Graphics.hpp>

class Sphere{
public:
    Sphere(sf::Texture& texture, int radius, sf::Color color, int posx, int posy);
    ~Sphere();
    sf::Sprite getSphere() const;
    int getPositionY() const;
    sf::Color getColor() const;
    void setColor(sf::Color);
    void setPosition(int posx, int posy);
private:
    sf::Sprite sphere;
};

#endif // SPHERE_HPP

