#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>

#include "rapidjson/document.h"

using namespace rapidjson;


class SpriteSheet
{
public:
    SpriteSheet(SDL_Renderer* renderer, SDL_Texture* texture, std::string data, std::vector<int> seq, float time);
    void RenderFrame(SDL_Texture* texture, const SDL_Rect* src_rect, const SDL_Rect* dest_rect); 
    bool Render();
    std::string parseFile(char* file_path);
private:
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;
    std::string _data;
    std::vector<int> _seq;
    float _time;
};
