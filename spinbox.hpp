#ifndef SPINBOX_HPP
#define SPINBOX_HPP
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

class SpinBox {
public:
    SpinBox (sf::Texture& texture, int posx, int posy, std::vector<std::string> values, sf::Font &font);
    ~SpinBox();
    sf::Sprite get() const;
    sf::Text getText() const;
    void setText(std::string t);
    void next();
    void prev();
    int getNumber();
private:
    sf::Sprite spinbox;
    sf::Text text;
    int px, py;
    int current = 0;
    std::vector<std::string> ValuesArray;
};

#endif // SPINBOX_HPP


