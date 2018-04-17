//
//  Renderer.cpp
//  pEngine
//
//  Created by Arthur on 05.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#include "../Inc/Renderer.hpp"

//--------------------------------------------------------------------------------------------------------
// Color Rect implementation
//--------------------------------------------------------------------------------------------------------

ColorRect::ColorRect()
{

}

ColorRect::ColorRect(SDL_Rect rect, int r, int g, int b, int a)
{
    this->rect = rect;
    this->color.at(0) = r;
    this->color.at(1) = g;
    this->color.at(2) = b;
    //printf("Color now is %i %i %i \n ", this->color.at(0), this->color.at(1), this->color.at(2), this->color.at(3));
}



//--------------------------------------------------------------------------------------------------------
// Renderer implementation
//--------------------------------------------------------------------------------------------------------

Renderer::Renderer()
{
    
}

void Renderer::update()
{
    while(!_render_queue.empty())
    {
        SDL_SetRenderDrawColor(sdl_renderer, 30, 30, 30, 0);
        SDL_RenderClear(sdl_renderer);
        
        auto item = _render_queue.front();
        SDL_SetRenderDrawColor( sdl_renderer, item.color.at(0), item.color.at(1), item.color.at(2), item.color.at(3));
        SDL_RenderFillRect( sdl_renderer, &item.rect);
       
        _render_queue.pop();
    }
}

Renderer::Renderer(SDL_Renderer* renderer)
{
    this->sdl_renderer = renderer;
}

void Renderer::RenderTileMap(vector<shared_ptr<MapLocation>>& locations)
{
    for (int i = 0; i < locations.size(); i++)
    {
        if (locations.at(i)->isObstacle)
        {
            addToRenderQueue(locations.at(i)->rect, RGBColor::red);
            continue;
        }
        
        addToRenderQueue(locations.at(i)->rect, RGBColor::lightBlue);
    }
}

void Renderer::ShowNeighboors(vector<Vertex*>& nodeNeighbors)
{
    SDL_SetRenderDrawColor( sdl_renderer, 255, 0, 0, 0 );
    
    for(int i = 0; i < nodeNeighbors.size(); i++)
    {
        SDL_RenderFillRect(sdl_renderer, &nodeNeighbors.at(i)->location.rect);
    }
}

void Renderer::DrawTile(SDL_Rect rect)
{
    SDL_SetRenderDrawColor( sdl_renderer, 100, 205, 40, 0 );
    SDL_RenderFillRect( sdl_renderer, &rect);
}

void Renderer::addToRenderQueue(SDL_Rect& rect, RGBColor color)
{
    std::array<int, 4> color_value;
    switch (color) {
        case RGBColor::red:
            color_value.at(0) = 255;
            color_value.at(1) = 0;
            color_value.at(2) = 0;
            color_value.at(3) = 0;
            break;
        
        case RGBColor::green:
            color_value.at(0) = 0;
            color_value.at(1) = 255;
            color_value.at(2) = 0;
            color_value.at(3) = 0;
            break;
        
        case RGBColor::blue:
            color_value.at(0) = 0;
            color_value.at(1) = 0;
            color_value.at(2) = 255;
            color_value.at(3) = 0;
            break;
            
        case RGBColor::white:
            color_value.at(0) = 255;
            color_value.at(1) = 255;
            color_value.at(2) = 255;
            color_value.at(3) = 0;
            break;
            
        case RGBColor::black:
            color_value.at(0) = 0;
            color_value.at(1) = 0;
            color_value.at(2) = 0;
            color_value.at(3) = 0;
            break;
            
        case RGBColor::swamp:
            color_value.at(0) = 204;
            color_value.at(1) = 204;
            color_value.at(2) = 0;
            color_value.at(3) = 0;
            break;
            
        case RGBColor::lightBlue:
            color_value.at(0) = 153;
            color_value.at(1) = 204;
            color_value.at(2) = 255;
            color_value.at(3) = 0;
            
        default:
            break;
    }
    
    ColorRect color_rect = ColorRect(rect, color_value[0], color_value[1], color_value[2], color_value[3]);
    
    _render_queue.push(color_rect);
}

void Renderer::BlinkTile(SDL_Renderer* renderer, SDL_Rect rect, RandomNum* rand)
{
    LTimer timer = LTimer();
    timer.start();
    
    while(1)
    {
        int randNum = rand->getRange(0, 256);
        if (timer.getTicks() >= 1000)
        {
            SDL_SetRenderDrawColor( renderer, randNum, randNum, randNum, 0xFF );
            SDL_RenderFillRect(renderer, &rect);
            timer.pause();
            BlinkTile(renderer, rect, rand);
            break;
        }
        printf("Ticks: %i \n ", timer.getTicks());
    }
}
