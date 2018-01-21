#ifndef TEXT_HPP
#define TEXT_HPP
#include <SFML/Graphics.hpp>

class Text{
public:
    Text(sf::Font& font, int size, sf::Color color, int posx, int posy);
    ~Text();
    sf::Text get() const;
    void setValue(int value);
private:
    sf::Text text;
};

#endif // TEXT_HPP

