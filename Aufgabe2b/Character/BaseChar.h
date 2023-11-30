#pragma once

#include "raylib.h"
#include "../Sprite.h"


namespace Char
{

    enum Direction {LEFT, RIGHT, UP, DOWN};

    class BaseChar
    {
    public:
        virtual void Move(Direction dir) = 0;

        // Position of Player is implemented by Sprite
        Sprite playerSprite = Sprite();

        Vector2 GetPos();
        Vector2 GetArrayPos();
        void SetPosition(int x, int y);
        void SetArrayPosition(int x, int y);

    protected:
        // Is needed to move player correctly
        int arrayPosX;
        int arrayPosY;
        Direction direction;
    };

}
