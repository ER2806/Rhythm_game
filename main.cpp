#define NON_MERGING

#ifndef NON_MERGING
#include <QCoreApplication>
#include <QApplication>
#include "utils.h"
#include "client.h"
#endif

#include "graph.hpp"
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

#define WIDTH 600
#define HEIGHT 600

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
const sf::Color WHITE = (sf::Color(255, 255, 255, 250));
const sf::Color BLUE = (sf::Color(0,174,255,250));



std::string getTrack() //получение адеса аудио
{
    /* for merging
    QApplication a(argc, argv);
    Client webClient(getIpAddr(), getPort());
    uint8_t errorCode;
    std::string request = "haddawa.wav";
    std::string audioFilename = webClient.getTrackFromServer(errorCode, request);
    */
    return "haddawa.wav";
}

std::string getParsedTrack()
{
    /* for merging
    request = "haddawa.wav";
    std::string textFilename = webClient.getParsedTrackFromServer(errorCode, request);
    std::cout << textFilename << std::endl;
    */
    return "test.txt";
}
            
void createLines(std::vector<sf::RectangleShape>& RectanglesList)
{
    for(int i = 0; i < 3; i++)
    {
        sf::RectangleShape line(sf::Vector2f(HEIGHT-VERTICAL_LINE_Y_INDENT*2, LINE_THICKNESS));
        line.setPosition(WIDTH/2 + DISTANCE_BETWEEN_LINES*(i-1),DISTANCE_BETWEEN_LINES);
        line.rotate(90);
        RectanglesList.push_back(line);
    }
    sf::RectangleShape lineh(sf::Vector2f(HORIZONTAL_LINE_LENGTH, LINE_THICKNESS));
    lineh.setPosition(WIDTH/2-HORIZONTAL_LINE_LENGTH/2,HORIZONTAL_LINE_Y_POSITION);
    RectanglesList.push_back(lineh);
}

std::vector<sf::Sprite> createNodes(std::vector<PointInTime>& PointList, sf::Texture& texture)
{   
    std::vector<sf::Sprite> SpriteList;
    for(int i = 0; i < PointList.size(); i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, BALL_RADIUS*2, BALL_RADIUS*2));
        sprite.setColor(WHITE);
        sprite.setPosition(WIDTH/2 - DISTANCE_BETWEEN_LINES*2 + DISTANCE_BETWEEN_LINES * PointList[i].line - BALL_RADIUS,
                           VERTICAL_LINE_Y_INDENT-BALL_RADIUS);
        if(PointList[i].time < CROSS_ROAD_TIME)
        {
            sprite.move(0,((double)(CROSS_ROAD_TIME-PointList[i].time))*HORIZONTAL_LINE_Y_POSITION/CROSS_ROAD_TIME);
            PointList[i].time = 0;
        }
        else
            PointList[i].time -= CROSS_ROAD_TIME;
        SpriteList.push_back(sprite);
    }
    return SpriteList;
}

void createText(sf::Text& hit, sf::Text& miss, sf::Font& font)
{    
    hit.setString("0");
    miss.setString("0");
    hit.setFont(font);
    miss.setFont(font);
    hit.setCharacterSize(FONTSIZE);
    miss.setCharacterSize(FONTSIZE);
    hit.setFillColor(WHITE);
    miss.setFillColor(WHITE);
    hit.setPosition(HIT_SCORE_HORIZONTAL_PADDING, SCORE_VERTICAL_PADDING);
    miss.setPosition(MISS_SCORE_HORIZONTAL_PADDING, SCORE_VERTICAL_PADDING);
    return;
}

std::vector<PointInTime> getPoints()
{
    std::vector<PointInTime> PointList;
    std::ifstream in;
 
    in.open(getParsedTrack());
    size_t ms;
    int num;
    LOG(INFO) << "point array (line; time):";
    while(in >> ms)
    {
        in >> num;
        LOG(INFO) << num << " " << ms;
        PointList.push_back(PointInTime(ms,num+1));
    }
    return PointList;
}

int keyboardReact(sf::Event& event, std::vector<sf::Sprite>& SpriteList, std::vector<PointInTime>& PointList)
{
    int line;
    if (event.key.code == sf::Keyboard::A)
        line = 1;
    else if(event.key.code == sf::Keyboard::S)
        line = 2;
    else if(event.key.code == sf::Keyboard::D)
        line = 3;

    int flag = 0;
    for(int i = 0; i < SpriteList.size(); i++)
    {
        if((PointList[i].line == line) && (SpriteList[i].getPosition().y >= ACTIVE_ZONE_TOP-BALL_RADIUS)
                                    && (SpriteList[i].getPosition().y <= ACTIVE_ZONE_BOTTOM-BALL_RADIUS)
                                    && (SpriteList[i].getColor() != BLUE))
            {
                SpriteList[i].setColor(BLUE);
                return 1; //hit
            }
    }
    return -1; //miss    
}

void drawAll(std::vector<sf::RectangleShape>& RectanglesList, std::vector<sf::Sprite>& SpriteList, 
    std::vector<PointInTime>& PointList, float deltaTime, sf::RenderWindow& window, sf::Text& hit, sf::Text& miss) 
{
    window.clear();
    for(int i = 0; i < 4; i++)
        window.draw(RectanglesList[i]);

    for(int i = 0; i < SpriteList.size(); i++)
    {
        if((PointList[i].time <= deltaTime) && (SpriteList[i].getPosition().y <= ACTIVE_ZONE_BOTTOM-BALL_RADIUS)) // 1.7 cекунд на всю линию, 1.5 - до плашки
        {
            SpriteList[i].move(0, 1);
            //if(!(((int)deltaTime)%4))
            //    SpriteList[i].move(0, 1);
            window.draw(SpriteList[i]);
        }
    }

    window.draw(hit);
    window.draw(miss);    
    return;
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "rhythm game");

    std::vector<sf::RectangleShape> RectanglesList;    
    createLines(RectanglesList);   
    //try
    std::vector<PointInTime> PointList = getPoints();  
    //show error
    sf::Texture texture;
    //try
    texture.loadFromFile("sphere.png");
    std::vector<sf::Sprite> SpriteList = createNodes(PointList,texture);
    
    sf::SoundBuffer buffer;
    //try -> show error
    if (!buffer.loadFromFile(getTrack()))
        return -1;
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    float deltaTime = 0.0f;
    sf::Clock clock;
    clock.restart();
    int counterHit = 0;
    int counterMiss = 0;
    sf::Text hit, miss;
    sf::Font font;
    // try -> show error
    font.loadFromFile("VoniqueBold.ttf");
    createText(hit, miss, font);
    while (window.isOpen())
    {
        deltaTime = clock.getElapsedTime().asMilliseconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
             switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                // key pressed
                case sf::Event::KeyPressed:
                {
                    if(keyboardReact(event, SpriteList, PointList) == 1)
                        counterHit++;
                    else
                        counterMiss++;
                    break;
                }
            }
        }
        hit.setString(std::to_string(counterHit));
        miss.setString(std::to_string(counterMiss));
        drawAll(RectanglesList, SpriteList, PointList, deltaTime, window, hit, miss);
        window.display();
    }
    return 0;
}
