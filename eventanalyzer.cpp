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
