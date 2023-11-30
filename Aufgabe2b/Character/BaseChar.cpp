#include "BaseChar.h"


namespace Char
{

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

    bool BaseChar::CanMove(Direction direction)
    {
        switch (direction)
        {
            case Direction::LEFT:
                if (map->map[arrayPosX - 1][arrayPosY] != Game::TileState::BLOCKED && arrayPosX - 1 >= 0) return true;
                break;
            case Direction::RIGHT:
                if (map->map[arrayPosX + 1][arrayPosY] != Game::TileState::BLOCKED && arrayPosX + 1 < map->mapWidth) return true;
                break;
            case Direction::UP:
                if (map->map[arrayPosX][arrayPosY - 1] != Game::TileState::BLOCKED && arrayPosY - 1 >= 0) return true;
                break;
            case Direction::DOWN:
                if (map->map[arrayPosX][arrayPosY + 1] != Game::TileState::BLOCKED && arrayPosY + 1 < map->mapHeight) return true;
                break;
        }
        return false;
    }

}
