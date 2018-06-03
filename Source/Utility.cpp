//
//  Utility.cpp
//  pEngine
//
//  Created by Arthur on 25.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#include "../Inc/Utility.hpp"

RandomNum::RandomNum()
{
    this->initialize();
}

void RandomNum::initialize()
{
    rng.seed((unsigned int)time(NULL));
}

int RandomNum::getRange(int start, int end)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(start,end);
    return dist(rng);
}

std::string Parser::ParseFile(char* file_path)
{
    std::ifstream file;
    file.open(file_path);
    std::string temp;
    std::string contents;
    while(std::getline(file, temp))
    {
        contents += temp;
    }
    file.close();

    return contents;
}
