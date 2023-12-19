#pragma once

#include <vector>

#include "World/Map.h"

std::vector<std::vector<int>> ConvertToVector(int map[][Game::Map::mapHeight])
{
    std::vector<std::vector<int>> grid;

    for (int i = 0; i < Game::Map::mapWidth; ++i)
    {
        std::vector<int> row;
        for (int j = 0; j < Game::Map::mapHeight; ++j)
        {
            row.push_back(map[i][j]);
        }
        grid.push_back(row);
    }

    return grid;
}