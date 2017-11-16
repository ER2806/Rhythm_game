/* for merging
#include <QCoreApplication>
#include <QApplication>
#include "utils.h"
#include "client.h"
*/
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

int main(int argc, char* argv[])
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(getTrack()))
        return -1;
    sf::Sound sound;
    sound.setBuffer(buffer);
    //sound.play();

    int width = 600, height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "rhythm game");
    sf::RectangleShape line1(sf::Vector2f(height-100, 4));
    line1.setPosition(width/2-50,50);
    line1.rotate(90);
    sf::RectangleShape line2(sf::Vector2f(height-100, 4));
    line2.setPosition(width/2,50);
    line2.rotate(90);
    sf::RectangleShape line3(sf::Vector2f(height-100, 4));
    line3.setPosition(width/2+50,50);
    line3.rotate(90);
    sf::RectangleShape lineh(sf::Vector2f(200, 4));
    lineh.setPosition(width/2-100,480);

    // Declare and load a texture
    sf::Texture texture;
    texture.loadFromFile("sphere.png");

    std::vector<PointInTime> PointList;
    std::ifstream in;
 
    in.open(getParsedTrack());
    int64_t ms;
    int num;
    sound.play();
    while(in >> ms)
    {
        in >> num;
        std::cout << num << " " << ms << std::endl;
        PointList.push_back(PointInTime(ms,num+1));
    }

    std::vector<sf::Sprite> SpriteList;
    for(int i = 0; i < PointList.size(); i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
        sprite.setColor(sf::Color(255, 255, 255, 250));
        sprite.setPosition(width/2-100 + 50*PointList[i].line - 30, 20);
        if(PointList[i].time < 1500)
        {
            sprite.move(0,((double)(1500-PointList[i].time))*480/1500);
            PointList[i].time = 0;
        }
        else
            PointList[i].time -= 1500;
        SpriteList.push_back(sprite);
    }

    float deltaTime = 0.0f;
    sf::Clock clock;
    clock.restart();
    int counterHit = 0;
    int counterMiss = 0;
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
                    if (event.key.code == sf::Keyboard::A){
                        int flag = 0;
                        for(int i = 0; i < SpriteList.size(); i++)
                        {
                            if((PointList[i].line == 1) && (SpriteList[i].getPosition().y >= 420)
                                    && (SpriteList[i].getPosition().y <= 520)
                                    && (SpriteList[i].getColor() != sf::Color(0,174,255,250)))
                            {
                                SpriteList[i].setColor(sf::Color(0, 174, 255, 250));
                                flag = 1;
                                counterHit++;

                            }
                        }
                        if(!flag)
                        {
                            counterMiss++;
                        }
                    }
                    if (event.key.code == sf::Keyboard::S)
                    {
                        int flag = 0;
                        for(int i = 0; i < SpriteList.size(); i++)
                        {
                            if((PointList[i].line == 2) && (SpriteList[i].getPosition().y >= 420)
                                    && (SpriteList[i].getPosition().y <= 520)
                                    && (SpriteList[i].getColor() != sf::Color(0,174,255,250)))
                            {
                                SpriteList[i].setColor(sf::Color(0, 174, 255, 250));
                                flag = 1;
                                counterHit++;
                            }
                        }
                        if(!flag)
                        {
                            counterMiss++;
                        }
                    }
                    if (event.key.code == sf::Keyboard::D)
                    {
                        int flag = 0;
                        for(int i = 0; i < SpriteList.size(); i++)
                        {
                            if((PointList[i].line == 3) && (SpriteList[i].getPosition().y >= 420)
                                    && (SpriteList[i].getPosition().y <= 520)
                                    && (SpriteList[i].getColor() != sf::Color(0,174,255,250)))
                            {
                                SpriteList[i].setColor(sf::Color(0, 174, 255, 250));
                                flag = 1;
                                counterHit++;
                            }
                        }
                        if(!flag)
                        {
                            counterMiss++;
                        }
                    }
                    break;
                }
            }
        }

        window.clear();
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(lineh);

        for(int i = 0; i < SpriteList.size(); i++)
        {
            if((PointList[i].time <= deltaTime) && (SpriteList[i].getPosition().y <= 520)) // 1.7 cекунд на всю линию, 1.5 - до плашки
            {
                SpriteList[i].move(0, 1);
                if(!(((int)deltaTime)%4))
                    SpriteList[i].move(0, 1);
                window.draw(SpriteList[i]);
            }
        }
        window.display();
    }
    std::cout << "\nmiss counter = " << counterMiss << "\nhit counter = " << counterHit << std::endl;

    return 0;
}
