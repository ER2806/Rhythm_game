#include "eventanalyzer.hpp"

EventAnalyser::EventAnalyser()
{}

EventAnalyser::~EventAnalyser()
{}

int EventAnalyser::Analyze(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::A)
        return 1;
    else if(event.key.code == sf::Keyboard::S)
        return 2;
    else if(event.key.code == sf::Keyboard::D)
        return 3;
    return -1;
}

int EventAnalyser::MouseAnalyze(sf::Event& event, int xleft, int xright, int yup, int ydown)
{
    if((event.mouseButton.x > xleft) && (event.mouseButton.x < xright)
            && (event.mouseButton.y > yup) && (event.mouseButton.y < ydown))
        return 1;
    else
        return 0;
}
