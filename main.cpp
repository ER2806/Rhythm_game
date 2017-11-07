#include <SFML/Graphics.hpp>
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

    // Declare and load a texture
    sf::Texture texture;
    texture.loadFromFile("sphere.png");

    std::vector<PointInTime> PointList;
    PointList.push_back(PointInTime(1000,3));
    PointList.push_back(PointInTime(0,2));
    PointList.push_back(PointInTime(2000,3));

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

    // Create a sprite
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
    sprite.setColor(sf::Color(255, 255, 255, 250));
    sprite.setPosition(218, 350);

    sf::Sprite sprite2;
    sprite2.setTexture(texture);
    sprite2.setTextureRect(sf::IntRect(0, 0, 60, 60));
    sprite2.setColor(sf::Color(255, 255, 255, 250));
    sprite2.setPosition(268, 550);

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
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //sprite2.move(0,-0.1*deltaTime);

        window.clear();
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);

        for(int i = 0; i < SpriteList.size(); i++)
        {
            std::cout << deltaTime << " " << i << " " << PointList[i].time << std::endl;
            if((PointList[i].time <= deltaTime)) //&& ())
            {
                //SpriteList[i].move(0, -0.1*(deltaTime - PointList[i].time));
                SpriteList[i].move(0, 1);
                window.draw(SpriteList[i]);
            }

            /*SpriteList[i].move(0, -0.001*(deltaTime - PointList[i].time)); // разность должна быть от 0 до 500000
            if((deltaTime - PointList[i].time > 0) && (deltaTime - PointList[i].time < 5000))
                window.draw(SpriteList[i]);*/
        }

        //window.draw(sprite);
        //window.draw(sprite2);
        //window.draw(PressedSprite);
        window.display();
    }

    return 0;
}
