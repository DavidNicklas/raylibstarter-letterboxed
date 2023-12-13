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
        void SetStartPosition() override;

        void SetPath(std::vector<std::pair<int, int>> _path) { this->path = _path; }
        void MoveTo(int col, int row);

    private:
        void UpdateCurrentPosition();

        std::vector<std::pair<int, int>> path;
        int currentProgressOnGraph = 0; // stores at which index of the graph the player currently is

        float speed;
        Vector2 currentPosition;

        bool allowMovement = false;
        bool isMoving = false;
        bool reachedGoal = false;
    };

}
