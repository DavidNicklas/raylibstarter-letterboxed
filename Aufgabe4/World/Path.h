#pragma once

#include <vector>

#include "../Algorithm/AStarPathfinding.h"

namespace Game
{

    class Path
    {
    public:
        Path() { showPath = false; }
        ~Path() { showPath = false; }

        std::vector<std::pair<int, int>> path;

        void DrawPath();
        void DrawPathLines();
        void CreateShortestPath(std::vector<std::vector<int>>& map, std::pair<int, int> start, std::pair<int, int> goal);

        bool showPath;
    };

}
