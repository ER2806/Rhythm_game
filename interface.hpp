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

    template<class T> void drawObj(T& obj)
    {
        window->draw(obj.get());
    }
    template<class T> void drawObjWText(T& obj)
    {
        window->draw(obj.get());
        window->draw(obj.getText());
    }
    void render();
    bool isGameOpen();
    void clear();
    bool pollEvent(sf::Event &event);
private:
    sf::RenderWindow* window;
};

#endif // INTERFACE_H
