#ifndef GRAPH_MODULE
#define GRAPH_MODULE

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>

struct PointInTime{
    int64_t time; // время в милисекундах с начала игры
    int line; // номер "струны" (1,2,3)
    PointInTime(int64_t t, int l) : time(t), line(l){
    }
};

void startGame();
std::string getTrack();
std::string getParsedTrack();
void createLines(std::vector<sf::RectangleShape>& RectanglesList);
std::vector<sf::Sprite> createNodes(std::vector<PointInTime>& PointList, sf::Texture& texture);
void createText(sf::Text& hit, sf::Text& miss);
std::vector<PointInTime> getPoints();
int keyboardReact(sf::Event& event, std::vector<sf::Sprite>& SpriteList, std::vector<PointInTime>& PointList);
void drawAll(std::vector<sf::RectangleShape>& RectanglesList, std::vector<sf::Sprite>& SpriteList, 
    std::vector<PointInTime>& PointList, float deltaTime, sf::RenderWindow& window, sf::Text& hit, sf::Text& miss);

#endif
