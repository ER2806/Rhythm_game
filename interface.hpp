#ifndef INTERFACE_H
#define INTERFACE_H
#include <SFML/Graphics.hpp>
#include "line.hpp"
#include "sphere.hpp"
#include "text.hpp"
#include "button.hpp"
#include "spinbox.hpp"

class GraphicInterface{
public:
    GraphicInterface(int width, int height, std::string window_name);
    ~GraphicInterface();

    void draw(sf::Drawable* object);
    void draw(const Line& object);
    void draw(const Sphere& sphere);
    void draw(const Text& text);
    void draw(const Button& button);
    void draw(const SpinBox& spinbox);
    void render();
    bool isGameOpen();
    void clear();
    bool pollEvent(sf::Event &event);
private:
    sf::RenderWindow* window;
};

#endif // INTERFACE_H
