#pragma once

#include <vector>

#include "BaseChar.h"

namespace Char
{

    class NonPlayerChar : public BaseChar
    {
    public:
        NonPlayerChar(Texture2D newTexture);

        void Update();
        void Draw();

        void Move() override;
        void ResetPlayerStats() override;

        void SetPath(std::vector<std::pair<int, int>> _path) { this->path = _path; }
        void MoveTo(int col, int row);

    private:

        std::vector<std::pair<int, int>> path;
        int currentProgressOnGraph = 0;

        float speed;
        bool allowMovement = false;
        bool reachedGoal = false;
    };

}
