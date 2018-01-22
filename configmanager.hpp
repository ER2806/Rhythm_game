#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP
#include <string>
#include <fstream>
#include <iostream>

const std::string CONFIG_NAME = "resourse/gui.conf";


class SingletonConfigManager
{
public:
    static SingletonConfigManager& getInstance() {
        static SingletonConfigManager instance;
        instance.fillInstance();
        return instance;
    }

    int getWidth(){return WIDTH;}
    int getHeight(){return HEIGHT;}
    int getFontSize(){return FONTSIZE;}
    int getScoreVerticalPadding(){return SCORE_VERTICAL_PADDING;}
    int getHitScoreHorizontalPadding(){return HIT_SCORE_HORIZONTAL_PADDING;}
    int getMissScoreHorizontalPadding(){return MISS_SCORE_HORIZONTAL_PADDING;}
    int getBallRadius(){return BALL_RADIUS;}
    int getCrossRoadTime(){return CROSS_ROAD_TIME;}
    int getLineThickness(){return LINE_THICKNESS;}
    int getDistanceBetweenLines(){return DISTANCE_BETWEEN_LINES;}
    int getHorizontalLineYPosition(){return HORIZONTAL_LINE_Y_POSITION;}
    int getHorizontalLineLength(){return HORIZONTAL_LINE_LENGTH;}
    int getVerticalLineYIndent(){return VERTICAL_LINE_Y_INDENT;}
    int getActiveZoneTop(){return ACTIVE_ZONE_TOP;}
    int getActiveZoneBottom(){return ACTIVE_ZONE_BOTTOM;}
    int getRigtAngle(){return RIGHT_ANGLE;}
    int getButtonSizeX(){return BUTTON_SIZE_X;}
    int getButtonSizeY(){return BUTTON_SIZE_Y;}
    int getSpinboxWidth(){return SPINBOX_WIDTH;}
    int getSpinboxYOffset(){return SPINBOX_Y_OFFSET;}
    int getSpinboxLeft(){return SPINBOX_LEFT;}
    int getSpinboxRight(){return SPINBOX_RIGHT;}
    int getSpinboxUpperArrowTop(){return SPINBOX_UPPER_ARROW_TOP;}
    int getSpinboxBetweenArrows(){return SPINBOX_BETWEEN_ARROWS;}
    int getSpinboxLowerArrowBottom(){return SPINBOX_LOWER_ARROW_BOTTOM;}

private:
    int a;
    void fillInstance();
    int WIDTH;
    int HEIGHT;
    int FONTSIZE;
    int SCORE_VERTICAL_PADDING;
    int HIT_SCORE_HORIZONTAL_PADDING;
    int MISS_SCORE_HORIZONTAL_PADDING;
    int BALL_RADIUS;
    int CROSS_ROAD_TIME;
    int LINE_THICKNESS;
    int DISTANCE_BETWEEN_LINES;
    int HORIZONTAL_LINE_Y_POSITION;
    int HORIZONTAL_LINE_LENGTH;
    int VERTICAL_LINE_Y_INDENT;
    int ACTIVE_ZONE_TOP;
    int ACTIVE_ZONE_BOTTOM;
    int RIGHT_ANGLE;
    int BUTTON_SIZE_X;
    int BUTTON_SIZE_Y;
    int SPINBOX_WIDTH;
    int SPINBOX_Y_OFFSET;
    int SPINBOX_LEFT;
    int SPINBOX_RIGHT;
    int SPINBOX_UPPER_ARROW_TOP;
    int SPINBOX_BETWEEN_ARROWS;
    int SPINBOX_LOWER_ARROW_BOTTOM;


    SingletonConfigManager() {}
    SingletonConfigManager( const SingletonConfigManager&);
    SingletonConfigManager& operator=( SingletonConfigManager& );
};


#endif // CONFIGMANAGER_HPP
