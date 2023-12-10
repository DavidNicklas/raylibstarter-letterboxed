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

    void Path::DrawPathLines()
    {
        if (!path.empty())
        {
            for (size_t i = 0; i < path.size() - 1; ++i)
            {
                Vector2 startPos = { static_cast<float>(path[i].first * Config::TileSize + Config::TileSize / 2),
                                     static_cast<float>(path[i].second * Config::TileSize + Config::TileSize / 2) };

                Vector2 endPos = { static_cast<float>(path[i + 1].first * Config::TileSize + Config::TileSize / 2),
                                   static_cast<float>(path[i + 1].second * Config::TileSize + Config::TileSize / 2) };

                DrawLineV(startPos, endPos, RED);
            }
        }
        else
        {
            std::cout << "No path found" << std::endl;
        }
    }

    void Path::CreateShortestPath(std::vector<std::vector<int>>& map, std::pair<int, int> start, std::pair<int, int> goal)
    {
        path = Algorithm::AStar(map, start, goal);
    }

}