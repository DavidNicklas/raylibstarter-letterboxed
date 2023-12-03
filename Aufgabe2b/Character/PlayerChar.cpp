#include "PlayerChar.h"
#include "../World/Map.h"

namespace Char
{

    PlayerChar::PlayerChar()
    {
        this->playerSprite.ChangeTexture("../../assets/graphics/bear.png");
    }

    void PlayerChar::Update()
    {
        // Inventory Input
        if (IsKeyPressed(KEY_E))
        {
            if (!inInventory) inInventory = true;
            else inInventory = false;
        }

        if (!inInventory) Move();

        if (PlayerOnItemTile()) PickUpItem();
    }

    void PlayerChar::Draw()
    {
        DrawTexture(playerSprite.GetTexture(), playerSprite.posX, playerSprite.posY, WHITE);
    }

    void PlayerChar::SetStartPosition()
    {
        this->playerSprite.posX = this->map->centerX + static_cast<float>(this->map->GetStartCol() * Config::TileSize);
        this->playerSprite.posY = this->map->centerY + static_cast<float>(this->map->GetStartRow() * Config::TileSize);

        this->arrayPosX = this->map->GetStartCol();
        this->arrayPosY = this->map->GetStartRow();
    }

    void PlayerChar::Move()
    {
        if (IsKeyPressed(KEY_A))
        {
            direction = Direction::LEFT;
            if (CanMove(direction))
            {
                playerSprite.posX -= Config::TileSize;
                arrayPosX--;
            }
        }

        else if (IsKeyPressed(KEY_D))
        {
            direction = Direction::RIGHT;
            if (CanMove(direction))
            {
                playerSprite.posX += Config::TileSize;
                arrayPosX++;
            }
        }

        else if (IsKeyPressed(KEY_W))
        {
            direction = Direction::UP;
            if (CanMove(direction))
            {
                playerSprite.posY -= Config::TileSize;
                arrayPosY--;
            }
        }

        else if (IsKeyPressed(KEY_S))
        {
            direction = Direction::DOWN;
            if (CanMove(direction))
            {
                playerSprite.posY += Config::TileSize;
                arrayPosY++;
            }
        }
    }

    int PlayerChar::CalculateTotalWeight()
    {
        // going through normal inventory
        for (int i = 0; i < inventory.GetCapacity(); ++i)
        {
            this->totalWeight += (int) inventory.itemContainer[i]->GetWeight();
        }
        //going through equipment slots
        for (int i = 0; i < inventory.GetEquipmentSlots(); ++i)
        {
            if (inventory.equipmentContainer[i] != nullptr)
                this->totalWeight += (int) inventory.equipmentContainer[i]->GetWeight();
        }

        return totalWeight;
    }

    /* Checks if the player is standing on a tile which carries an item */
    bool PlayerChar::PlayerOnItemTile()
    {
        if (this->map->map[this->arrayPosX][this->arrayPosY] == Game::TileState::ITEM) return true;
        else return false;
    }

    void PlayerChar::PickUpItem()
    {
        try
        {
            inventory.AddItem(map->itemTiles[arrayPosX][arrayPosY].item);
            std::cout << "Picked up Item" << std::endl; //TODO Debug
            std::cout << inventory.GetCurrentNumberOfItems() << std::endl; // TODO Debug
            map->map[arrayPosX][arrayPosY] = Game::TileState::PASSABLE; // only resets tile to passable if item was added (because of exception it jumps directly into catch block)
        }
        catch (Error::InventoryFull &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

}
