#include "interface.hpp"

GraphicInterface::GraphicInterface(int width, int height, std::string window_name)
    : window(new sf::RenderWindow(sf::VideoMode(width, height), window_name))
{}

GraphicInterface::~GraphicInterface()
{
    window->close();
}

void GraphicInterface::draw(sf::Drawable* object)
{
    window->draw(*object);
}

void GraphicInterface::draw(const Line& line)
{
    window->draw(line.getLine());
}

void GraphicInterface::draw(const Sphere& sphere)
{
    window->draw(sphere.getSphere());
}

void GraphicInterface::draw(const Text& text)
{
    window->draw(text.getText());
}

void GraphicInterface::draw(const Button& button)
{
    window->draw(button.getButton());
    window->draw(button.getText());
}

void GraphicInterface::draw(const SpinBox& spinbox)
{
    window->draw(spinbox.getSpinBox());
    window->draw(spinbox.getText());
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
