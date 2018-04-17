//
//  Graph.cpp
//  pEngine
//
//  Created by Arthur on 10.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#include "../Inc/Graph.hpp"

//--------------------------------------------------------------------------------------------------------
// Vertex definitions
//--------------------------------------------------------------------------------------------------------
Vertex::Vertex(MapLocation location)
{
    this->location = location;
}


//--------------------------------------------------------------------------------------------------------
// Graph Definitions
//--------------------------------------------------------------------------------------------------------

Graph::Graph(std::vector<std::shared_ptr<MapLocation>>& locations)
{
    for (int i = 0; i < locations.size(); i++)
    {
        //create graph vertices
        std::shared_ptr<Vertex> vert (new Vertex(*locations.at(i)));
        this->vertices.push_back(vert);

        //printf("locations stuff %i \n ", i);
        printf("locations coordinates num: %i coords: %i %i \n ", i, vert->location.position.x, vert->location.position.y);
    }
    
    index_grid();
  
}

void Graph::index_grid()
{
    int dirs[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    
    //check for neighboors, create links

    for (auto &current : this->vertices)
    {
        for (auto &dir : dirs)
        {
            NodePosition neighbour;
            neighbour.x = current->location.position.x + dir[0];
            neighbour.y = current->location.position.y + dir[1];
            
            for (auto &vert : this->vertices)
            {
                if (neighbour.x == vert->location.position.x
                    && neighbour.y == vert->location.position.y)
                {
                    if (!vert->location.isObstacle)
                        current->neighboors.push_back(vert);
                }
            }
        }
        
    }

    
}

