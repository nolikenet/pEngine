//
//  AstarSearch.cpp
//  pEngine
//
//  Created by Arthur on 15.11.17.
//  Copyright © 2017 plaiko. All rights reserved.
//

#include "../Inc/AStarSearch.hpp"


double update_heuristic(MapLocation a, MapLocation b)
{
    int x1, y1, x2, y2;
    x1 = a.position.x;
    y1 = a.position.y;
    x2 = b.position.x;
    y2 = b.position.y;
    return abs(x1 - x2) + abs(y1 - y2);
}

void build_path(Renderer* renderer, std::unique_ptr<Graph>& graph, std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end)
{
    std::queue<std::shared_ptr<Vertex>> open_set;
    open_set.push(start);
    
    std::unordered_map<std::shared_ptr<Vertex>, std::shared_ptr<Vertex>> came_from;
    
    
    while (!open_set.empty())
    {
        auto& current = open_set.front();
        open_set.pop();
        
        if (current == end) break;
        
        for (const auto& next : current->neighboors)
        {
            if (came_from.find(next) == came_from.end())
            {
                open_set.push(next);
                came_from.insert(std::make_pair(next, current));
        
                printf("Came from size %lu \n ", came_from.size());
            }
        }
    }
    
    std::shared_ptr<Vertex> p = end;
    while(p != start)
    {
        std::array<int, 4> color = {0, 0, 0, 0};
     
        renderer->addToRenderQueue(p->location.rect, RGBColor::blue);
        p = came_from.at(came_from.find(p)->first);
        printf("Looking for p %p \n ", p.get());
    }
}

