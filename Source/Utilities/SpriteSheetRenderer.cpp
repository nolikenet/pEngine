#include "../../Inc/SpriteSheetRenderer.hpp"

SpriteSheet::SpriteSheet(SDL_Renderer* renderer, SDL_Texture* texture, std::string data, std::vector<int> seq, float time)
{
    this->_renderer = renderer;
    this->_texture = texture;
    this->_data = data;
    this->_seq = seq;
    this->_time = time;
}

void SpriteSheet::RenderFrame(SDL_Texture* texture, const SDL_Rect* src_rect, const SDL_Rect* dest_rect)
{
    SDL_RenderCopy(this->_renderer, texture, src_rect, dest_rect);
    std::cout << "Frame Rendered " << std::endl;
}

bool SpriteSheet::Render()
{
    Document doc;
    doc.Parse(_data.c_str());
    doc["frames"].IsArray();
    const Value& arr = doc["frames"];
    int initialX = 100;

    for (Value::ConstValueIterator itr = arr.Begin(); itr != arr.End(); ++itr) {
        printf("iterate over arr %s \n ", itr->GetObject()["filename"].GetString());

    int iter_index = std::distance(arr.Begin(), itr);

    auto seq_iter = std::find(_seq.begin(), _seq.end(), iter_index);
    if (seq_iter == _seq.end()) continue;

    SDL_Rect src_rect;
    src_rect.x = itr->GetObject()["frame"].GetObject()["x"].GetInt();
    src_rect.y = itr->GetObject()["frame"].GetObject()["y"].GetInt();
    src_rect.h = itr->GetObject()["frame"].GetObject()["h"].GetInt();
    src_rect.w = itr->GetObject()["frame"].GetObject()["w"].GetInt();

    SDL_Rect dest_rect = { 100, 100, src_rect.w, src_rect.h };
    SDL_RenderCopy(_renderer, _texture, &src_rect, &dest_rect);

    SDL_Delay(_time * 500);
    SDL_RenderPresent(_renderer);
    SDL_RenderClear(_renderer);

    //initialX += src_rect.w;

    }

    std::cout << "Rednering Done " << std::endl;
    return true;
}




