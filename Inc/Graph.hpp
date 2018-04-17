//
//  Graph.hpp
//  pEngine
//
//  Created by Arthur on 10.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include <array>

#include "MapLocation.hpp"


struct Edge;
struct MapLocation;

struct Vertex
{
    Vertex();
    Vertex(MapLocation location);
    //Vertex(MapLocation location, std::array<Edge, 4>* edges);
    MapLocation location;
    std::vector<std::shared_ptr<Vertex>> neighboors;
    
};

/*struct Edge
{
    int weight;
    Vertex vert;
};*/

class Graph
{
public:
    Graph();
    Graph(std::vector<std::shared_ptr<MapLocation>>& locations);
    void add_vertex(Vertex vert, Edge edges[4]);
    void add_edge(Edge edge);
    std::vector<std::shared_ptr<Vertex>> vertices;
    void index_grid();
};


#endif /* Graph_hpp */
