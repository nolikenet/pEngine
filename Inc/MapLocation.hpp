//
//  MapLocation.hpp
//  pEngine
//
//  Created by Arthur on 13.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#ifndef MapLocation_hpp
#define MapLocation_hpp

#include <SDL2/SDL.h>
#include <stdio.h>

struct NodePosition
{
    NodePosition();
    NodePosition(int x, int y);
    int x;
    int y;
};

struct MapLocation
{
    MapLocation();
    MapLocation(NodePosition pos, SDL_Rect rect);
    
    SDL_Rect rect;
    NodePosition position; 
    bool isObstacle = false;
};

#endif /* MapLocation_hpp */
