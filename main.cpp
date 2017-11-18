/* for merging
#include <QCoreApplication>
#include <QApplication>
#include "utils.h"
#include "client.h"
*/
#include "graph.hpp"

#define WHITE (sf::Color(255, 255, 255, 250))
#define BLUE (sf::Color(0,174,255,250))
#define WIDTH 600
#define HEIGHT 600

void startGame() // cоздание клиента
{
    // Client NewClient();
}

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
        sf::RectangleShape line(sf::Vector2f(HEIGHT-100, 4));
        line.setPosition(WIDTH/2 + 50*(i-1),50);
        line.rotate(90);
        RectanglesList.push_back(line);
    }
    sf::RectangleShape lineh(sf::Vector2f(200, 4));
    lineh.setPosition(WIDTH/2-100,480);
    RectanglesList.push_back(lineh);
}

std::vector<sf::Sprite> createNodes(std::vector<PointInTime>& PointList, sf::Texture& texture)
{   
    std::vector<sf::Sprite> SpriteList;
    for(int i = 0; i < PointList.size(); i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
        sprite.setColor(WHITE);
        sprite.setPosition(WIDTH/2-100 + 50*PointList[i].line - 30, 20);
        if(PointList[i].time < 1500)
        {
            sprite.move(0,((double)(1500-PointList[i].time))*480/1500);
            PointList[i].time = 0;
        }
        else
            PointList[i].time -= 1500;
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
    hit.setCharacterSize(24);
    miss.setCharacterSize(24);
    hit.setFillColor(WHITE);
    miss.setFillColor(WHITE);
    hit.setPosition(10,10);
    miss.setPosition(550,10);
    return;
}

std::vector<PointInTime> getPoints()
{
    std::vector<PointInTime> PointList;
    std::ifstream in;
 
    in.open(getParsedTrack());
    int64_t ms;
    int num;
    while(in >> ms)
    {
        in >> num;
        std::cout << num << " " << ms << std::endl;
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
        if((PointList[i].line == line) && (SpriteList[i].getPosition().y >= 420)
                                    && (SpriteList[i].getPosition().y <= 520)
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
        if((PointList[i].time <= deltaTime) && (SpriteList[i].getPosition().y <= 520)) // 1.7 cекунд на всю линию, 1.5 - до плашки
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
    // big main try catch block
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
