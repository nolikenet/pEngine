#include <string>

#include "rapidjson/document.h"

using namespace rapidjson;


class TextureUnpacker
{
public:
    TextureUnpacker();
    void Unpack(const char* dataFilePath);
};
