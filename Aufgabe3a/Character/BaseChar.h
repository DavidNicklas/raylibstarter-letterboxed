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
        virtual void SetStartPosition() = 0;
        bool CanMove(Direction direction);

        // Position of Player is implemented by Sprite
        Sprite playerSprite = Sprite();

        void SetPosition(int x, int y);
        void SetArrayPosition(int x, int y);

        Game::Map* map = nullptr;

    protected:
        // Is needed to move player correctly
        int arrayPosX;
        int arrayPosY;
        Direction direction;
    };

}
