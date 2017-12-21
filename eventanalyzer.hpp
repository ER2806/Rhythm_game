#ifndef EVENTANALYZER_HPP
#define EVENTANALYZER_HPP
#include <SFML/Graphics.hpp>

class EventAnalyser{
public:
    EventAnalyser();
    ~EventAnalyser();
    int Analyze(sf::Event& event);
};
#endif // EVENTANALYZER_HPP

