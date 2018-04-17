//
//  AstarSearch.hpp
//  pEngine
//
//  Created by Arthur on 15.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#ifndef AStarSearch_hpp
#define AStarSearch_hpp

#include <stdio.h>
#include <tuple>
#include <queue>
#include <algorithm>
#include <unordered_map>

#include "Graph.hpp"
#include "MapLocation.hpp"
#include "Renderer.hpp"

/*class AStarSearch
{
public:
    double update_heuristic(MapLocation a, MapLocation b);
    void build_path(Graph* graph, Vertex* start, Vertex* end);
    
private:
    std::queue<Vertex*> open_set;
};*/

double update_heuristic(MapLocation a, MapLocation b);
void build_path(Renderer* renderer, std::unique_ptr<Graph>& graph, std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end);

#endif /* AStarSearch_hpp */
