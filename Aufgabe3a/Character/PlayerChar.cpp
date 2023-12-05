#include "PlayerChar.h"
#include "../World/Map.h"
#include "../UI/InventoryUI.h"

namespace Char
{

    PlayerChar::PlayerChar(Texture2D newTexture)
    {
        this->playerSprite.ChangeTexture(newTexture);
    }

    void PlayerChar::Update()
    {
        if (inventoryUi->ShowInventory())
        {
            if (IsKeyPressed(KEY_ENTER) && !inventoryUi->ShowSortMenu()) EquipItem();
            if (IsKeyPressed(KEY_BACKSPACE)) DropItem();
            if (inventoryUi->ShowSortMenu() && IsKeyPressed(KEY_ENTER)) SortItems();
        }
        else
        {
            if (totalWeight < portableWeight) Move();
            if (PlayerOnItemTile()) PickUpItem();
        }
    }

    void PlayerChar::Draw()
    {
        DrawTexture(playerSprite.GetTexture(), playerSprite.posX, playerSprite.posY, WHITE);
        if (totalWeight >= portableWeight) DrawText("You carry to many items.", 50, 0, 30, RED);
    }

    void PlayerChar::ResetPlayerStats()
    {
        SetStartPosition();
        this->totalWeight = 0;
        this->strength = 10;
        this->portableWeight = strength * strengthMultiplier;
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
                DropItemOnGround();
                arrayPosX--;
            }
        }

        else if (IsKeyPressed(KEY_D))
        {
            direction = Direction::RIGHT;
            if (CanMove(direction))
            {
                playerSprite.posX += Config::TileSize;
                DropItemOnGround();
                arrayPosX++;
            }
        }

        else if (IsKeyPressed(KEY_W))
        {
            direction = Direction::UP;
            if (CanMove(direction))
            {
                playerSprite.posY -= Config::TileSize;
                DropItemOnGround();
                arrayPosY--;
            }
        }

        else if (IsKeyPressed(KEY_S))
        {
            direction = Direction::DOWN;
            if (CanMove(direction))
            {
                playerSprite.posY += Config::TileSize;
                DropItemOnGround();
                arrayPosY++;
            }
        }
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
            totalWeight += (int)map->itemTiles[arrayPosX][arrayPosY].item->GetWeight();
            map->itemTiles[arrayPosX][arrayPosY].item = nullptr;
            std::cout << "Picked up Item" << std::endl; //TODO Debug
            std::cout << inventory.GetCurrentNumberOfItems() << std::endl; // TODO Debug
            map->map[arrayPosX][arrayPosY] = Game::TileState::PASSABLE; // only resets tile to passable if item was added (because of exception it jumps directly into catch block)
        }
        catch (Error::InventoryFull &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    //TODO still a bug if you drop two items on the same tile
    void PlayerChar::DropItem()
    {
        if (map->map[arrayPosX][arrayPosY] == Game::TileState::PASSABLE)
        {
            try
            {
                // safe the item temporarily and then drop it on the ground when the player moves
                // otherwise, the player instantly picks the item back up
                markedForDropItem = inventory.RemoveItem(inventoryUi->GetSelectedInventorySlot());
                totalWeight -= (int)markedForDropItem->GetWeight();
            }
            catch (Error::OutOfRange &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        else std::cout << "Can not drop item. Tile already has an item on it." << std::endl;
    }

    void PlayerChar::DropItemOnGround()
    {
        if (markedForDropItem != nullptr)
        {
            // if there is still an item marked, place it on the map after player has moved
            map->map[arrayPosX][arrayPosY] = Game::TileState::ITEM;
            map->itemTiles[arrayPosX][arrayPosY].item = markedForDropItem;
            // clear the marked item and free it for the next
            markedForDropItem = nullptr;
        }
    }

    void PlayerChar::EquipItem()
    {
        if (inventory.GetItem(inventoryUi->GetSelectedInventorySlot()) != nullptr)
        {
            try
            {
                std::shared_ptr<Items::BaseItem> temporaryItem = inventory.GetItem(inventoryUi->GetSelectedInventorySlot());
                inventory.EquipItem(temporaryItem);
                // make a dynamic cast to get the strength attribute
                std::shared_ptr<Items::EquippableItem> equippableItem = std::dynamic_pointer_cast<Items::EquippableItem>(temporaryItem);
                if (equippableItem != nullptr)
                {
                    this->strength += equippableItem->GetAdditionalStrength();
                    this->portableWeight = strength * strengthMultiplier;
                }
            }
            catch (Error::InventoryFull& e)
            {
                std::cout << e.what() << std::endl;
            }
            catch (Error::EquipmentError& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    void PlayerChar::SortItems()
    {
        switch (inventoryUi->GetCurrentSortButton())
        {
            case UI::CurrentSortButton::WEIGHT: inventory.SortForWeight(); break;
            case UI::CurrentSortButton::NAME: inventory.SortForName(); break;
            case UI::CurrentSortButton::COST: inventory.SortForCost(); break;
        }
    }

}
