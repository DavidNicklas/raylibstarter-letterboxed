#pragma once

#include <vector>

#include "BaseChar.h"

namespace Char
{

    class NonPlayerChar : public BaseChar
    {
    public:
        NonPlayerChar();

        void Update();
        void Draw();

        void Move() override;
        void ResetPlayerStats() override;
        void SetStartPosition() override;

        void SetPath(std::vector<std::pair<int, int>> _path) { this->path = _path; }
        void MoveTo(int col, int row);

    private:
        void UpdateCurrentPosition();
        void CheckGoalReached();

        void PickUpItem() override;
        bool PlayerOnExitTile() override;

        std::vector<std::pair<int, int>> path;
        int currentProgressOnGraph = 0; // stores at which index of the graph the player currently is

        Vector2 currentPosition = {0, 0};
        bool allowMovement = false;
        bool isMoving = false;

        Texture2D nonPlayerTex = LoadTexture("../../assets/graphics/robotBear.png");
    };

}
