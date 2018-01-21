#include "interface.hpp"

GraphicInterface::GraphicInterface(int width, int height, std::string window_name)
    : window(new sf::RenderWindow(sf::VideoMode(width, height), window_name))
{}

GraphicInterface::~GraphicInterface()
{
    window->close();
}

void GraphicInterface::render()
{
    window->display();
}

bool GraphicInterface::isGameOpen()
{
    return window->isOpen();
}

bool GraphicInterface::pollEvent(sf::Event &event)
{
    window->pollEvent(event);
}

void GraphicInterface::clear()
{
    window->clear();
}
