#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


struct PointInTime{
    int64_t time; // время в милисекундах с начала игры
    int line; // номер "струны" (1,2,3)
    PointInTime(int64_t t, int l){
        time = t;
        line = l;
    }
};

int main()
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("tune.wav"))
        return -1;
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

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
    PointList.push_back(PointInTime(1000,3));
    PointList.push_back(PointInTime(0,2));
    PointList.push_back(PointInTime(2000,3));
    PointList.push_back(PointInTime(1500,1));
    PointList.push_back(PointInTime(2500,2));
    PointList.push_back(PointInTime(2500,1));
    PointList.push_back(PointInTime(3000,1));

    std::vector<sf::Sprite> SpriteList;
    for(int i = 0; i < PointList.size(); i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
        sprite.setColor(sf::Color(255, 255, 255, 250));
        sprite.setPosition(width/2-100 + 50*PointList[i].line - 30, 20);
        SpriteList.push_back(sprite);
    }

    sf::Sprite PressedSprite;
    PressedSprite.setTexture(texture);
    PressedSprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
    PressedSprite.setColor(sf::Color(0, 174, 255, 250));
    PressedSprite.setPosition(218, 150);

    float deltaTime = 0.0f;
    sf::Clock clock;
    clock.restart();

    while (window.isOpen())
    {
        //deltaTime = clock.restart().asMilliseconds();
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
                    if (event.key.code == sf::Keyboard::A)
                         for(int i = 0; i < SpriteList.size(); i++)
                             if((PointList[i].line == 1) && (SpriteList[i].getPosition().y >= 400) && (SpriteList[i].getPosition().y <= 520))
                                SpriteList[i].setColor(sf::Color(0, 174, 255, 250));
                    if (event.key.code == sf::Keyboard::S)
                        for(int i = 0; i < SpriteList.size(); i++)
                             if((PointList[i].line == 2) && (SpriteList[i].getPosition().y >= 400) && (SpriteList[i].getPosition().y <= 520))
                                SpriteList[i].setColor(sf::Color(0, 174, 255, 250));
                    if (event.key.code == sf::Keyboard::D)  
                        for(int i = 0; i < SpriteList.size(); i++)
                             if((PointList[i].line == 3) && (SpriteList[i].getPosition().y >= 400) && (SpriteList[i].getPosition().y <= 520))
                                SpriteList[i].setColor(sf::Color(0, 174, 255, 250));              
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
            if((PointList[i].time <= deltaTime) && (SpriteList[i].getPosition().y <= 520))
            {
                if(!(((int)deltaTime) % 4))
                    SpriteList[i].move(0, 1);
                window.draw(SpriteList[i]);
            } 
            if(i == 1) 
                std::cout << deltaTime << " " << SpriteList[i].getPosition().y << std::endl;        
        }
        //window.draw(PressedSprite);
        window.display();
    }

    return 0;
}
