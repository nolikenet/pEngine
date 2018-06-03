//
//  Renderer.hpp
//  pEngine
//
//  Created by Arthur on 05.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <queue>
#include <functional>

#include "MapLocation.hpp"
#include "Graph.hpp"
#include "LTimer.hpp"
#include "Utility.hpp"
#include "SpriteSheetRenderer.hpp"

using namespace std;

enum RGBColor
{
    red,
    green,
    blue,
    black,
    white,
    swamp,
    lightBlue
};

class ColorRect
{
public:
    
    ColorRect();
    ColorRect(SDL_Rect rect, int r, int g, int b, int a);
    SDL_Rect rect;
    std::array<int, 4> color;
};

class Renderer
{
public:
    Renderer();
    Renderer(SDL_Renderer* renderer);
    
    void RenderTileMap(vector<shared_ptr<MapLocation>>& locations);
    
    void ShowNeighboors(vector<Vertex*>& nodeNeighbors);
    
    void DrawTile(SDL_Rect rect);
    
    void BlinkTile(SDL_Renderer* renderer, SDL_Rect rect, RandomNum* rand);
    
    void addToRenderQueue(SDL_Rect& rect, RGBColor color);

    SDL_Texture* loadTexture(std::string path);
    
    void update();
    
private:
    SDL_Renderer* sdl_renderer;
    std::queue<ColorRect> _render_queue;
};



#endif /* Renderer_hpp */
