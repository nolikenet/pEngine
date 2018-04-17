#include "../../Inc/Config.hpp"

Config::Config()
{

}

void Config::read(const char* configFilePath)
{
    Document doc;
    doc.Parse(configFilePath);
    std::cout << doc["name"].GetString() << std::endl;
}


