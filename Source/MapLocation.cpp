//
//  MapLocation.cpp
//  pEngine
//
//  Created by Arthur on 13.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#include "../Inc/MapLocation.hpp"

NodePosition::NodePosition()
{

}

NodePosition::NodePosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

MapLocation::MapLocation()
{
    
}

MapLocation::MapLocation(NodePosition pos, SDL_Rect rect)
{
    this->rect = rect;
    this->position = pos;
    //this->position_index = pos_index;
}
