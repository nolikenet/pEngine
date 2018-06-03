//
//  Utility.hpp
//  pEngine
//
//  Created by Arthur on 25.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#ifndef Utility_hpp
#define Utility_hpp

#include <stdio.h>
#include <fstream>
#include <random>
#include <time.h>

typedef std::mt19937 Range;

class RandomNum
{
public:
    RandomNum();
    int getRange(int start, int end);
private:
    Range rng;
    void initialize();
    
};

void initialize();

class Parser
{
public: 
    static std::string ParseFile(char* file_path);
};

#endif /* Utility_hpp */
