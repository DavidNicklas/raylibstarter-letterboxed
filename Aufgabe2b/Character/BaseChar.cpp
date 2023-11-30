#include "BaseChar.h"


namespace Char
{

    Vector2 BaseChar::GetPos()
    {
        Vector2 posVector;
        posVector.x = (float)playerSprite.posX;
        posVector.y = (float)playerSprite.posY;
        return posVector;
    }

    Vector2 BaseChar::GetArrayPos()
    {
        Vector2 posVector;
        posVector.x = (float)arrayPosX;
        posVector.y = (float)arrayPosY;
        return posVector;
    }


    void BaseChar::SetPosition(int x, int y)
    {
        this->playerSprite.posX = x;
        this->playerSprite.posY = y;
    }

    void BaseChar::SetArrayPosition(int x, int y)
    {
        this->arrayPosX = x;
        this->arrayPosY = y;
    }

}
