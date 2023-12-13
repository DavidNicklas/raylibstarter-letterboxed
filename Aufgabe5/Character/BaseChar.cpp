#include "BaseChar.h"
#include "../World/Map.h"

namespace Char
{

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

    void BaseChar::SetStartPosition()
    {
        this->playerSprite.posX = this->map->GetStartCol() * Config::TileSize;
        this->playerSprite.posY = this->map->GetStartRow() * Config::TileSize;

        this->arrayPosX = this->map->GetStartCol();
        this->arrayPosY = this->map->GetStartRow();
    }

    /* Checks if the player is standing on a tile which carries an item */
    bool BaseChar::PlayerOnItemTile()
    {
        if (this->map->map[this->arrayPosX][this->arrayPosY] == Game::TileState::ITEM) return true;
        else return false;
    }

    void BaseChar::PickUpItem()
    {
        try
        {
            inventory.AddItem(map->itemTiles[arrayPosX][arrayPosY].item);
            totalWeight += (int)map->itemTiles[arrayPosX][arrayPosY].item->GetWeight();
            map->itemTiles[arrayPosX][arrayPosY].item = nullptr;
            map->map[arrayPosX][arrayPosY] = Game::TileState::PASSABLE; // only resets tile to passable if item was added (because of exception it jumps directly into catch block)
        }
        catch (Error::InventoryFull &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

}
