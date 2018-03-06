#ifndef EVENTANALYZER_HPP
#define EVENTANALYZER_HPP
#include <SFML/Graphics.hpp>

enum keyValue {A = 1, S, D};

class EventAnalyser{
public:
    EventAnalyser();
    ~EventAnalyser();
    int Analyze(sf::Event& event);
    int MouseAnalyze(sf::Event& event, int xleft, int xright, int yup, int ydown);
};
#endif // EVENTANALYZER_HPP

