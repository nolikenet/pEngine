#include "../../Inc/TextureUnpacker.hpp"

TextureUnpacker::TextureUnpacker()
{

}

void TextureUnpacker::Unpack(const char* dataFilePath)
{
  Document data;
  data.Parse(dataFilePath);
}
