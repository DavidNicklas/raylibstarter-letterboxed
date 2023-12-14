#include "PlayerChar.h"
#include "../World/Map.h"
#include "../UI/InventoryUI.h"

namespace Char
{

    PlayerChar::PlayerChar()
    {
        this->playerSprite.ChangeTexture(playerTex);
        this->health = 20;
        inventoryUi = new UI::InventoryUI(this);
    }

    void PlayerChar::Update()
    {
        // Logic when inventory is shown
        if (this->GetInventoryUI()->ShowInventory())
        {
            this->GetInventoryUI()->Update();
            if (IsKeyPressed(KEY_ENTER) && !this->GetInventoryUI()->ShowSortMenu()) EquipItem();
            if (IsKeyPressed(KEY_BACKSPACE)) DropItem();
            if (this->GetInventoryUI()->ShowSortMenu() && IsKeyPressed(KEY_ENTER)) SortItems();
        }
        // Logic when inventory is hidden
        else
        {
            if (totalWeight < portableWeight && !this->reachedGoal) Move();
            if (PlayerOnItemTile()) PickUpItem();
            if (PlayerOnExitTile()) this->reachedGoal = true;
        }

        OpenInventory();
    }

    void PlayerChar::Draw()
    {
        DrawTexture(playerSprite.GetTexture(), playerSprite.posX, playerSprite.posY, WHITE);
        if (totalWeight >= portableWeight) DrawText("You carry to many items.", 50, 0, 30, RED);

        this->GetInventoryUI()->Draw();
    }

    void PlayerChar::ResetPlayerStats()
    {
        SetStartPosition();
        this->totalWeight = 0;
        this->strength = 10;
        this->portableWeight = strength * strengthMultiplier;
        this->reachedGoal = false;
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
                if ((totalWeight - (int)markedForDropItem->GetWeight()) >= 0)
                {
                    totalWeight -= (int)markedForDropItem->GetWeight();
                }
                else totalWeight = 0;
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

    void PlayerChar::SortItems()
    {
        switch (inventoryUi->GetCurrentSortButton())
        {
            case UI::CurrentSortButton::WEIGHT: inventory.SortForWeight(); break;
            case UI::CurrentSortButton::NAME: inventory.SortForName(); break;
            case UI::CurrentSortButton::COST: inventory.SortForCost(); break;
        }
    }

    bool PlayerChar::PlayerOnExitTile()
    {
        return this->arrayPosX == this->map->GetEndCol() && this->arrayPosY == this->map->GetEndRow();
    }

    void PlayerChar::OpenInventory()
    {
        if (IsKeyPressed(KEY_E))
        {
            if (this->GetInventoryUI()->ShowInventory()) this->GetInventoryUI()->SetShowInventory(false);
            else this->GetInventoryUI()->SetShowInventory(true);
        }
    }

}
