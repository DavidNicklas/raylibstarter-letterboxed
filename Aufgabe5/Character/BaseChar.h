#pragma once

#include "raylib.h"
#include "../Sprite.h"

namespace Game
{
    class Map;
}

namespace Char
{

    enum Direction {LEFT, RIGHT, UP, DOWN};

    class BaseChar
    {
    public:
        virtual void Move() = 0;
        virtual void ResetPlayerStats() = 0;
        void SetStartPosition();
        bool CanMove(Direction direction);

        // Position of Player is implemented by Sprite
        Sprite playerSprite = Sprite();

        Game::Map* map = nullptr;

    protected:
        // Is needed to move player correctly
        int arrayPosX;
        int arrayPosY;
        Direction direction;
    };

}
