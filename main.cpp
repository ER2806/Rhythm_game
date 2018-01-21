#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#include <memory>
#include <string>
#include "graph.hpp"
#include "interface.hpp"
#include "text.hpp"
#include "eventanalyzer.hpp"
#include "loaderfromfile.hpp"
#include "spinbox.hpp"


std::vector<Line> createLines(ConfigurationManager confg)
{
    std::vector<Line> lineList;
    for(int i = 0; i < 3; i++)
    {
        Line line(confg.getHeight()-VERTICAL_LINE_Y_INDENT*2, LINE_THICKNESS, confg.getWidth()/2 + DISTANCE_BETWEEN_LINES*(i-1),
                  DISTANCE_BETWEEN_LINES, RIGHT_ANGLE);
        lineList.push_back(line);
    }
    Line lineh(HORIZONTAL_LINE_LENGTH, LINE_THICKNESS, confg.getWidth()/2-HORIZONTAL_LINE_LENGTH/2, HORIZONTAL_LINE_Y_POSITION, 0);
    lineList.push_back(lineh);
    return lineList;
}

std::vector<Sphere> createNodes(std::vector<PointInTime>& PointList, sf::Texture& texture,  ConfigurationManager confg)
{
    std::vector<Sphere> SphereList;
    for(int i = 0; i < PointList.size(); i++)
    {
        Sphere sp(texture, BALL_RADIUS, WHITE,
                  confg.getWidth()/2 - DISTANCE_BETWEEN_LINES*2 + DISTANCE_BETWEEN_LINES * PointList[i].line - BALL_RADIUS,
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
                SphereList[i].recieveSignal();
                return 1; //hit
            }
    }
    return -1; //miss    
}

int gameManager(ConfigurationManager& config, GraphicInterface& mainInterface, WebGetter& webgetter, std::shared_ptr<Loader> loader)
{
    sf::Font font;
    // try -> show error
    loader->LoadFont("resourse/gothic.ttf", font);

    //button
    sf::Texture btnTexture;
    //try
    loader->LoadTexture("resourse/btn1.png", btnTexture);
    Button btn(btnTexture, "start game", font, config.getWidth()/2 - BUTTON_SIZE_X/2, config.getHeight()/2 - BUTTON_SIZE_Y/2);

    //spinbox
    sf::Texture spnTexture;
    //try
    loader->LoadTexture("resourse/spn1.png", spnTexture);
    Button btn2(btnTexture, "play", font, config.getWidth()/2 - BUTTON_SIZE_X/2, config.getHeight()/2 - BUTTON_SIZE_Y/2);
    SpinBox spnbx(spnTexture, config.getWidth()/2 - SPINBOX_WIDTH/2, config.getHeight()/2 - SPINBOX_Y_OFFSET,
                  webgetter.getTrackList(), font);

    sf::Texture texture;
    //try
    loader->LoadTexture("resourse/sphere.png", texture);

    std::vector<Line> linesList = createLines(config);
    //try
    std::vector<PointInTime> PointList = getPoints(webgetter);
    std::vector<Sphere> SphereList = createNodes(PointList,texture,config);
    
    sf::SoundBuffer buffer;
    sf::Sound sound;

    int counterHit = 0;
    int counterMiss = 0;
    Text hit(font, FONTSIZE, WHITE, HIT_SCORE_HORIZONTAL_PADDING, SCORE_VERTICAL_PADDING);
    Text miss(font, FONTSIZE, WHITE, MISS_SCORE_HORIZONTAL_PADDING, SCORE_VERTICAL_PADDING);

    int GameMode = 0; // 0 - start screen, 1 - choose and play screen, 3 - action screen
    sf::Clock clock;
    while (mainInterface.isGameOpen())
    {
        float deltaTime = clock.getElapsedTime().asMilliseconds();
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
                    if(GameMode != 2)
                        break;
                    if(keyboardReact(event, SphereList, PointList) == 1)
                        counterHit++;
                    else
                        counterMiss++;
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    if(GameMode == 2)
                        break;
                    else if(GameMode == 0)
                    {
                        EventAnalyser analyser;
                        if(analyser.MouseAnalyze(event, config.getWidth()/2 - BUTTON_SIZE_X/2, config.getWidth()/2 + BUTTON_SIZE_X/2,
                                        config.getHeight()/2 - BUTTON_SIZE_Y/2, config.getHeight()/2 + BUTTON_SIZE_Y/2))
                            GameMode = 1;
                    }
                    else if(GameMode == 1)
                    {
                        EventAnalyser analyser;
                        if(analyser.MouseAnalyze(event, config.getWidth()/2 - BUTTON_SIZE_X/2, config.getWidth()/2 + BUTTON_SIZE_X/2,
                                        config.getHeight()/2 - BUTTON_SIZE_Y/2, config.getHeight()/2 + BUTTON_SIZE_Y/2))
                        {
                            GameMode = 2;
                            if (!buffer.loadFromFile(webgetter.getTrack(spnbx.getNumber())))
                                return -1;
                            sound.setBuffer(buffer);
                            sound.play();
                            clock.restart();
                        }
                        else if(analyser.MouseAnalyze(event, SPINBOX_LEFT, SPINBOX_RIGHT, SPINBOX_UPPER_ARROW_TOP, SPINBOX_BETWEEN_ARROWS))
                            spnbx.next();
                        else if(analyser.MouseAnalyze(event, SPINBOX_LEFT, SPINBOX_RIGHT, SPINBOX_BETWEEN_ARROWS, SPINBOX_LOWER_ARROW_BOTTOM))
                            spnbx.prev();
                    }
                    break;
                }

            }
        }
        mainInterface.clear();
        if(GameMode == 2)
        {
            hit.setValue(counterHit);
            miss.setValue(counterMiss);

            for(int i = 0; i < 4; i++)
                mainInterface.drawObj(linesList[i]);
            for(int i = 0; i < SphereList.size(); i++)
            {
                if((PointList[i].time <= deltaTime) && (SphereList[i].getPositionY() <= ACTIVE_ZONE_BOTTOM-BALL_RADIUS)) // 1.7 cекунд на всю линию, 1.5 - до плашки
                {
                    SphereList[i].setPosition(0, 1);
                    //if(!(((int)deltaTime)%4))
                    //    SpriteList[i].move(0, 1);
                    mainInterface.drawObj(SphereList[i]);
                }
            }
            mainInterface.drawObj(hit);
            mainInterface.drawObj(miss);
        }
        if(GameMode == 1)
        {
            mainInterface.drawObjWText(spnbx);
            mainInterface.drawObjWText(btn2);
        }
        if(GameMode == 0)
            mainInterface.drawObjWText(btn);
        mainInterface.render();
    }
    return 0;
}

int main(int argc, char* argv[])
{
    std::string configPath;
    if (argc > 1)// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
    {
          configPath = argv[1];
          LOG(INFO) << "CONFIGURATION FILE PATH: " << configPath;
    }
    else
    {
        LOG(INFO) << "NO CONFIGURATION FILE PATH";
        return 0;
    }
    //ConfigurationManager config("resourse/gui.conf");
    ConfigurationManager config(configPath);
    GraphicInterface mainInterface(config.getWidth(), config.getHeight(), "rhythm game");
    WebGetter webgetter;
    std::shared_ptr<Loader> loader(new LoaderFromFile());
    return gameManager(config, mainInterface, webgetter, loader);
 }
