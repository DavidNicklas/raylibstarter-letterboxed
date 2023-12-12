#include <iostream>

#include "NonPlayerChar.h"
#include "../World/Map.h"

namespace Char
{

    NonPlayerChar::NonPlayerChar(Texture2D newTexture)
    {
        this->playerSprite.ChangeTexture(newTexture);
    }

    void NonPlayerChar::Update()
    {
        if (IsKeyPressed(KEY_L)) allowMovement = !allowMovement;

        if (allowMovement) this->Move();
    }

    void NonPlayerChar::Draw()
    {
        DrawTexture(playerSprite.GetTexture(), playerSprite.posX, playerSprite.posY, WHITE);
    }

    void NonPlayerChar::Move()
    {
        if (!path.empty())
        {
            if (currentProgressOnGraph < path.size() || reachedGoal)
            {
                int newCol = path[currentProgressOnGraph].first;
                int newRow = path[currentProgressOnGraph].second;

                this->arrayPosX = newCol;
                this->arrayPosY = newRow;

                if (this->arrayPosX == this->map->GetEndCol() && this->arrayPosY == this->map->GetEndRow())
                    reachedGoal = true;

            }
        }
        else
        {
            std::cout << "No path found" << std::endl;
        }
    }

    void NonPlayerChar::ResetPlayerStats()
    {
        SetStartPosition();
    }

}
