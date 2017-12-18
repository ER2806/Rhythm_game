#ifndef LINE_HPP
#define LINE_HPP
#include <SFML/Graphics.hpp>

class Line{
public:
    Line(int length, int thickness,int posx, int posy, int rotationAngle);
    ~Line();
    sf::RectangleShape getLine() const;
private:
    sf::RectangleShape line;
};

#endif // LINE_HPP
