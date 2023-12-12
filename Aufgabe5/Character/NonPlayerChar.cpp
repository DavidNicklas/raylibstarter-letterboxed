#include <iostream>

#include "NonPlayerChar.h"
#include "../World/Map.h"

namespace Char
{

    NonPlayerChar::NonPlayerChar(Texture2D newTexture)
    {
        this->playerSprite.ChangeTexture(newTexture);
        currentProgressOnGraph = 0;
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
            if (currentProgressOnGraph < path.size() || !reachedGoal)
            {
                int newCol = path[currentProgressOnGraph].first;
                int newRow = path[currentProgressOnGraph].second;

                MoveTo(newCol, newRow);

                if (this->arrayPosX == this->map->GetEndCol() && this->arrayPosY == this->map->GetEndRow())
                    reachedGoal = true;

                currentProgressOnGraph++;
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
        path = this->map->path.path;
        allowMovement = false;
        reachedGoal = false;
        currentProgressOnGraph = 0;
    }

    void NonPlayerChar::MoveTo(int col, int row)
    {
        if (col < arrayPosX && row == arrayPosY) this->playerSprite.posX -= Config::TileSize;
        else if (col > arrayPosX && row == arrayPosY) this->playerSprite.posX += Config::TileSize;
        else if (col == arrayPosX && row < arrayPosY) this->playerSprite.posY -= Config::TileSize;
        else if (col == arrayPosX && row > arrayPosY) this->playerSprite.posY += Config::TileSize;

        this->arrayPosX = col;
        this->arrayPosY = row;
    }

}
