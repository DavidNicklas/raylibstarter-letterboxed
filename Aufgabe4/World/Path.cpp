#include <iostream>
#include "config.h"
#include "Path.h"
#include "raylib.h"

namespace Game
{

    void Path::DrawPath()
    {
        if (!path.empty())
        {
            for (auto node : path)
            {
                Rectangle destRec = { static_cast<float>(node.first * Config::TileSize),
                                      static_cast<float>(node.second * Config::TileSize),
                                      Config::TileSize,
                                      Config::TileSize };
                BeginBlendMode(BLEND_ALPHA);
                DrawRectangleRec(destRec, Fade(RED, 0.5f));
                EndBlendMode();
            }
        }
        else std::cout << "No path found" << std::endl;
    }

    void Path::CreateShortestPath(std::vector<std::vector<int>>& map, std::pair<int, int> start, std::pair<int, int> goal)
    {
        path = Algorithm::AStar(map, start, goal);
    }

}