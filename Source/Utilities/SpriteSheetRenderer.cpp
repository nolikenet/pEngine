#include "../../Inc/SpriteSheetRenderer.hpp"

SpriteSheet::SpriteSheet(SDL_Renderer* renderer)
{
    this->_renderer = renderer;
}

void SpriteSheet::RenderFrame(SDL_Texture* texture, const SDL_Rect* src_rect, const SDL_Rect* dest_rect)
{
    SDL_RenderCopy(this->_renderer, texture, src_rect, dest_rect);
    std::cout << "Frame Rendered " << std::endl;
}

bool SpriteSheet::Render(SDL_Texture* texture, std::string data)
{
    Document doc;
    doc.Parse(data.c_str());
    doc["frames"].IsArray();
    const Value& arr = doc["frames"];
    for (Value::ConstValueIterator itr = arr.Begin(); itr != arr.End(); ++itr) // Uses SizeType instead of size_t
        printf("iterate over arr %s \n ", itr->GetObject()["filename"].GetString());
    std::cout << "Rednering Done " << std::endl;
    return true;
}


