#include "configmanager.hpp"
#include <iostream>

void SingletonConfigManager::fillInstance()
    {
        std::ifstream in;
        in.open(CONFIG_NAME, std::ios_base::in);
        std::string temp;
        in >> temp;
        in >> WIDTH;
        in >> temp;
        in >> HEIGHT;
        in >> temp;
        in >> FONTSIZE;
        in >> temp;
        in >> SCORE_VERTICAL_PADDING;
        in >> temp;
        in >> HIT_SCORE_HORIZONTAL_PADDING;
        in >> temp;
        in >> MISS_SCORE_HORIZONTAL_PADDING;
        in >> temp;
        in >> BALL_RADIUS;
        in >> temp;
        in >> CROSS_ROAD_TIME;
        in >> temp;
        in >> LINE_THICKNESS;
        in >> temp;
        in >> DISTANCE_BETWEEN_LINES;
        in >> temp;
        in >> HORIZONTAL_LINE_Y_POSITION;
        in >> temp;
        in >> HORIZONTAL_LINE_LENGTH;
        in >> temp;
        in >> VERTICAL_LINE_Y_INDENT;
        in >> temp;
        in >> ACTIVE_ZONE_TOP;
        in >> temp;
        in >> ACTIVE_ZONE_BOTTOM;
        in >> temp;
        in >> RIGHT_ANGLE;
        in >> temp;
        in >> BUTTON_SIZE_X;
        in >> temp;
        in >> BUTTON_SIZE_Y;
        in >> temp;
        in >> SPINBOX_WIDTH;
        in >> temp;
        in >> SPINBOX_Y_OFFSET;
        in >> temp;
        in >> SPINBOX_LEFT;
        in >> temp;
        in >> SPINBOX_RIGHT;
        in >> temp;
        in >> SPINBOX_UPPER_ARROW_TOP;
        in >> temp;
        in >> SPINBOX_BETWEEN_ARROWS;
        in >> temp;
        in >> SPINBOX_LOWER_ARROW_BOTTOM;

    }
