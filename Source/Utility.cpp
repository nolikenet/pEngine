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
