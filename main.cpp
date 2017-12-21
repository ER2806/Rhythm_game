#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

#include "graph.hpp"
#include "interface.hpp"
#include "text.hpp"
#include "eventanalyzer.hpp"
#include "loaderfromfile.hpp"

#define WIDTH 600
#define HEIGHT 600

std::vector<Line> createLines()
{
    std::vector<Line> lineList;
    for(int i = 0; i < 3; i++)
    {
        Line line(HEIGHT-VERTICAL_LINE_Y_INDENT*2, LINE_THICKNESS, WIDTH/2 + DISTANCE_BETWEEN_LINES*(i-1),
                  DISTANCE_BETWEEN_LINES, RIGHT_ANGLE);
        lineList.push_back(line);
    }
    Line lineh(HORIZONTAL_LINE_LENGTH, LINE_THICKNESS, WIDTH/2-HORIZONTAL_LINE_LENGTH/2, HORIZONTAL_LINE_Y_POSITION, 0);
    lineList.push_back(lineh);
    return lineList;
}

std::vector<Sphere> createNodes(std::vector<PointInTime>& PointList, sf::Texture& texture)
{
    std::vector<Sphere> SphereList;
    for(int i = 0; i < PointList.size(); i++)
    {
        Sphere sp(texture, BALL_RADIUS, WHITE,
                  WIDTH/2 - DISTANCE_BETWEEN_LINES*2 + DISTANCE_BETWEEN_LINES * PointList[i].line - BALL_RADIUS,
                  VERTICAL_LINE_Y_INDENT - BALL_RADIUS);
        if(PointList[i].time < CROSS_ROAD_TIME)
        {
            sp.setPosition(0,((double)(CROSS_ROAD_TIME-PointList[i].time))*HORIZONTAL_LINE_Y_POSITION/CROSS_ROAD_TIME);
            PointList[i].time = 0;
        }
        else
            PointList[i].time -= CROSS_ROAD_TIME;
        SphereList.push_back(sp);
    }
    return SphereList;
}

std::vector<PointInTime> getPoints(WebGetter& wg)
{
    std::vector<PointInTime> PointList;
    std::ifstream in;
 
    in.open(wg.getParsedTrack());
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

int keyboardReact(sf::Event& event, std::vector<Sphere>& SphereList, std::vector<PointInTime>& PointList)
{
    int line;
    EventAnalyser analyser;
    line = analyser.Analyze(event);
    if(line==-1)
        LOG(INFO) << "ANALYZER ERROR";

    int flag = 0;
    for(int i = 0; i < SphereList.size(); i++)
    {
        if((PointList[i].line == line) && (SphereList[i].getPositionY() >= ACTIVE_ZONE_TOP-BALL_RADIUS)
                                    && (SphereList[i].getPositionY() <= ACTIVE_ZONE_BOTTOM-BALL_RADIUS)
                                    && (SphereList[i].getColor() != BLUE))
            {
                SphereList[i].setColor(BLUE);
                return 1; //hit
            }
    }
    return -1; //miss    
}

int main(int argc, char* argv[])
{
    GraphicInterface mainInterface(WIDTH, HEIGHT, "rhythm game");
    WebGetter webgetter;

    Loader* loader = new LoaderFromFile();
    sf::Texture texture;
    sf::Font font;
    //try
    loader->LoadTexture("resourse/sphere.png", texture);
    // try -> show error
    loader->LoadFont("resourse/VoniqueBold.ttf", font);
    delete loader;

    std::vector<Line> linesList = createLines();
    //try
    std::vector<PointInTime> PointList = getPoints(webgetter);
    std::vector<Sphere> SphereList = createNodes(PointList,texture);
    
    sf::SoundBuffer buffer;
    //try -> show error
    if (!buffer.loadFromFile(webgetter.getTrack()))
        return -1;
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    float deltaTime = 0.0f;
    sf::Clock clock;
    clock.restart();
    int counterHit = 0;
    int counterMiss = 0;
    Text hit(font, FONTSIZE, WHITE, HIT_SCORE_HORIZONTAL_PADDING, SCORE_VERTICAL_PADDING);
    Text miss(font, FONTSIZE, WHITE, MISS_SCORE_HORIZONTAL_PADDING, SCORE_VERTICAL_PADDING);

    while (mainInterface.isGameOpen())
    {
        deltaTime = clock.getElapsedTime().asMilliseconds();
        sf::Event event;
        while (mainInterface.pollEvent(event))
        {
             switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    return 0;
                // key pressed
                case sf::Event::KeyPressed:
                {
                    if(keyboardReact(event, SphereList, PointList) == 1)
                        counterHit++;
                    else
                        counterMiss++;
                    break;
                }
            }
        }
        hit.setValue(counterHit);
        miss.setValue(counterMiss);

        mainInterface.clear();
        for(int i = 0; i < 4; i++)
            mainInterface.draw(linesList[i]);
        for(int i = 0; i < SphereList.size(); i++)
        {
            if((PointList[i].time <= deltaTime) && (SphereList[i].getPositionY() <= ACTIVE_ZONE_BOTTOM-BALL_RADIUS)) // 1.7 cекунд на всю линию, 1.5 - до плашки
            {
                SphereList[i].setPosition(0, 1);
                //if(!(((int)deltaTime)%4))
                //    SpriteList[i].move(0, 1);
                mainInterface.draw(SphereList[i]);
            }
        }
        mainInterface.draw(hit);
        mainInterface.draw(miss);
        mainInterface.render();
    }
    return 0;
}
