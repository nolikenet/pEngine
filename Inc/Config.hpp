#include <iostream>
#include "rapidjson/document.h"

using namespace rapidjson;

class Config
{
public: 
    Config();
    void read(const char* configFilePath);

};
