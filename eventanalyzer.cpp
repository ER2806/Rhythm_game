#include "eventanalyzer.hpp"

EventAnalyser::EventAnalyser()
{}

EventAnalyser::~EventAnalyser()
{}

int EventAnalyser::Analyze(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::A)
        return A;
    else if(event.key.code == sf::Keyboard::S)
        return S;
    else if(event.key.code == sf::Keyboard::D)
        return D;
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
