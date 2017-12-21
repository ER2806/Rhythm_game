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
#include "line.hpp"
#include "sphere.hpp"
#include "webgetter.hpp"
#include "configmanager.hpp"

const int FONTSIZE = 24;
const int SCORE_VERTICAL_PADDING = 10;
const int HIT_SCORE_HORIZONTAL_PADDING = 10;
const int MISS_SCORE_HORIZONTAL_PADDING = 550;
const int BALL_RADIUS = 30;
const int CROSS_ROAD_TIME = 1500;
const int LINE_THICKNESS = 4;
const int DISTANCE_BETWEEN_LINES = 50;
const int HORIZONTAL_LINE_Y_POSITION = 480;
const int HORIZONTAL_LINE_LENGTH = 200;
const int VERTICAL_LINE_Y_INDENT = 50;
const int ACTIVE_ZONE_TOP = 450;
const int ACTIVE_ZONE_BOTTOM = 550;
const int RIGHT_ANGLE = 90;
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
std::vector<Line> createLines( ConfigurationManager confg);
std::vector<Sphere> createNodes(std::vector<PointInTime>& PointList, sf::Texture& texture, ConfigurationManager confg);
void createText(sf::Text& hit, sf::Text& miss);
std::vector<PointInTime> getPoints(WebGetter &wg);
int keyboardReact(sf::Event& event, std::vector<Sphere> &SphereList, std::vector<PointInTime>& PointList);

#endif

