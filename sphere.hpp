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
    void recieveSignal();
private:
    sf::Sprite sphere;
    const sf::Color inactiveColor = (sf::Color(255, 255, 255, 250));
    const sf::Color activeColor = (sf::Color(0,174,255,250));
};

#endif // SPHERE_HPP

