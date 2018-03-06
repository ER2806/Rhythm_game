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


std::vector<Line> createLines()
{
    SingletonConfigManager& confInst(SingletonConfigManager::getInstance());
    std::vector<Line> lineList;
    for(int i = 0; i < 3; i++)
    {
        Line line(confInst.getHeight()-confInst. getVerticalLineYIndent()*2, confInst.getLineThickness(),
                  confInst.getWidth()/2 + confInst.getDistanceBetweenLines()*(i-1),
                  confInst.getDistanceBetweenLines(), confInst.getRigtAngle());
        lineList.push_back(line);
    }
    Line lineh(confInst.getHorizontalLineLength(), confInst.getLineThickness(),
               confInst.getWidth()/2-confInst.getHorizontalLineLength()/2, confInst.getHorizontalLineYPosition(), 0);
    lineList.push_back(lineh);
    return lineList;
}

std::vector<Sphere> createNodes(std::vector<PointInTime>& PointList, sf::Texture& texture)
{
    SingletonConfigManager& confInst(SingletonConfigManager::getInstance());
    std::vector<Sphere> SphereList;
    for(int i = 0; i < PointList.size(); i++)
    {
        Sphere sp(texture, confInst.getBallRadius(), WHITE,
                  confInst.getWidth()/2 - confInst.getDistanceBetweenLines()*2 + confInst.getDistanceBetweenLines() * PointList[i].line - confInst.getBallRadius(),
                  confInst.getVerticalLineYIndent() - confInst.getBallRadius());
        if(PointList[i].time < confInst.getCrossRoadTime())
        {
            sp.setPosition(0,((double)(confInst.getCrossRoadTime()-PointList[i].time))*confInst.getHorizontalLineYPosition()/confInst.getCrossRoadTime());
            PointList[i].time = 0;
        }
        else
            PointList[i].time -= confInst.getCrossRoadTime();
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
    SingletonConfigManager& confInst(SingletonConfigManager::getInstance());
    int line;
    EventAnalyser analyser;
    line = analyser.Analyze(event);
    if(line==-1)
        LOG(INFO) << "ANALYZER ERROR";

    int flag = 0;
    for(int i = 0; i < SphereList.size(); i++)
    {
        if((PointList[i].line == line) && (SphereList[i].getPositionY() >= confInst.getActiveZoneTop()-confInst.getBallRadius())
                                    && (SphereList[i].getPositionY() <= confInst.getActiveZoneBottom()-confInst.getBallRadius())
                                    && (SphereList[i].getColor() != BLUE))
            {
                SphereList[i].recieveSignal();
                return 1; //hit
            }
    }
    return -1; //miss    
}

int gameManager(GraphicInterface& mainInterface, WebGetter& webgetter, std::shared_ptr<Loader> loader)
{
    SingletonConfigManager& confInst(SingletonConfigManager::getInstance());

    sf::Font font;
    // try -> show error
    loader->LoadFont("resourse/gothic.ttf", font);

    //button
    sf::Texture btnTexture;
    //try
    loader->LoadTexture("resourse/btn1.png", btnTexture);
    Button btn(btnTexture, "start game", font, confInst.getWidth()/2 - confInst.getButtonSizeX()/2,
               confInst.getHeight()/2 - confInst.getButtonSizeY()/2);

    //spinbox
    sf::Texture spnTexture;
    //try
    loader->LoadTexture("resourse/spn1.png", spnTexture);
    Button btn2(btnTexture, "play", font, confInst.getWidth()/2 -  confInst.getButtonSizeX()/2, confInst.getHeight()/2 - confInst.getButtonSizeY()/2);
    SpinBox spnbx(spnTexture, confInst.getWidth()/2 - confInst.getSpinboxWidth()/2, confInst.getHeight()/2 - confInst.getSpinboxYOffset(),
                  webgetter.getTrackList(), font);

    sf::Texture texture;
    //try
    loader->LoadTexture("resourse/sphere.png", texture);

    std::vector<Line> linesList = createLines();
    //try
    std::vector<PointInTime> PointList = getPoints(webgetter);
    std::vector<Sphere> SphereList = createNodes(PointList,texture);
    
    sf::SoundBuffer buffer;
    sf::Sound sound;

    int counterHit = 0;
    int counterMiss = 0;
    Text hit(font, confInst.getFontSize(), WHITE, confInst.getHitScoreHorizontalPadding(), confInst.getScoreVerticalPadding());
    Text miss(font, confInst.getFontSize(), WHITE, confInst.getMissScoreHorizontalPadding(), confInst.getScoreVerticalPadding());

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
                        if(analyser.MouseAnalyze(event, confInst.getWidth()/2 - confInst.getButtonSizeX()/2, confInst.getWidth()/2 + confInst.getButtonSizeX()/2,
                                        confInst.getHeight()/2 - confInst.getButtonSizeY()/2, confInst.getHeight()/2 + confInst.getButtonSizeY()/2))
                            GameMode = 1;
                    }
                    else if(GameMode == 1)
                    {
                        EventAnalyser analyser;
                        if(analyser.MouseAnalyze(event, confInst.getWidth()/2 - confInst.getButtonSizeX()/2, confInst.getWidth()/2 + confInst.getButtonSizeX()/2,
                                        confInst.getHeight()/2 - confInst.getButtonSizeY()/2, confInst.getHeight()/2 + confInst.getButtonSizeY()/2))
                        {
                            GameMode = 2;
                            if (!buffer.loadFromFile(webgetter.getTrack(spnbx.getNumber())))
                                return -1;
                            sound.setBuffer(buffer);
                            sound.play();
                            clock.restart();
                        }
                        else if(analyser.MouseAnalyze(event, confInst.getSpinboxLeft(), confInst.getSpinboxRight(),
                                                      confInst.getSpinboxUpperArrowTop(), confInst.getSpinboxBetweenArrows()))
                            spnbx.next();
                        else if(analyser.MouseAnalyze(event, confInst.getSpinboxLeft(), confInst.getSpinboxRight(),
                                                      confInst.getSpinboxBetweenArrows(), confInst.getSpinboxLowerArrowBottom()))
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
                if((PointList[i].time <= deltaTime) && (SphereList[i].getPositionY() <= confInst.getActiveZoneBottom()-confInst.getBallRadius())) // 1.7 cекунд на всю линию, 1.5 - до плашки
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