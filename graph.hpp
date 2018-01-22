#ifndef GRAPH_MODULE
#define GRAPH_MODULE

#define NON_MERGING

#ifndef NON_MERGING
#include <QCoreApplication>
#include <QApplication>
#include "utils.h"
#include "client.h"
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "line.hpp"
#include "sphere.hpp"
#include "webgetter.hpp"
#include "configmanager.hpp"


const sf::Color WHITE = (sf::Color(255, 255, 255, 250));
const sf::Color BLUE = (sf::Color(0,174,255,250));

struct PointInTime{
    int64_t time; // время в милисекундах с начала игры
    int line; // номер "струны" (1,2,3)
    PointInTime(int64_t t, int l) : time(t), line(l){
    }
};

void startGame();
std::string getTrack();
std::string getParsedTrack();
std::vector<Line> createLines();
std::vector<Sphere> createNodes(std::vector<PointInTime>& PointList, sf::Texture& texture);
void createText(sf::Text& hit, sf::Text& miss);
std::vector<PointInTime> getPoints(WebGetter &wg);
int keyboardReact(sf::Event& event, std::vector<Sphere> &SphereList, std::vector<PointInTime>& PointList);

#endif

