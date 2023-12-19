#include <iostream>

#include "NonPlayerChar.h"
#include "../World/Map.h"

namespace Char
{

    NonPlayerChar::NonPlayerChar()
    {
        this->playerSprite.ChangeTexture(nonPlayerTex);
        this->health = 10;
        currentProgressOnGraph = 0;
        inventoryUi = new UI::InventoryUI(this, false);
    }

    void NonPlayerChar::Update()
    {
        // Logic when inventory is shown
        if (this->GetInventoryUI()->ShowInventory())
        {
            this->GetInventoryUI()->Update();
            if (this->GetInventoryUI()->ShowSortMenu() && IsKeyPressed(KEY_ENTER)) SortItems();
        }
        // Logic when inventory is hidden
        else
        {
            if (IsKeyPressed(KEY_M)) allowMovement = !allowMovement;
            if (allowMovement) this->Move();
            if (PlayerOnExitTile()) this->reachedGoal = true;
        }

        OpenInventory();
    }

    void NonPlayerChar::Draw()
    {
        DrawTexture(playerSprite.GetTexture(), (int)currentPosition.x, (int)currentPosition.y, WHITE);

        this->GetInventoryUI()->Draw();
    }

    void NonPlayerChar::Move()
    {
        if (!path.empty())
        {
            // Checks if there are still tiles open in the path
            if (currentProgressOnGraph < path.size() || !reachedGoal)
            {
                if (!isMoving)
                {
                    // Takes the cords of the current path tile and stores is in two integer variables
                    int newCol = path[currentProgressOnGraph].first;
                    int newRow = path[currentProgressOnGraph].second;

                    // Moves the NPC to the new position
                    MoveTo(newCol, newRow);

                    if (PlayerOnItemTile()) PickUpItem();

                    currentProgressOnGraph++;
                }
                else if (totalWeight <= portableWeight) UpdateCurrentPosition();

                CheckGoalReached();
            }
        }
        else
        {
            std::cout << "No path found" << std::endl;
        }
    }

    // Check if the NPC has reached the goal
    void NonPlayerChar::CheckGoalReached()
    {
        if (currentPosition.x == (float)this->map->GetEndCol() * Config::TileSize && currentPosition.y == (float)this->map->GetEndRow() * Config::TileSize)
            reachedGoal = true;
    }

    void NonPlayerChar::MoveTo(int col, int row)
    {
        // Move the target position (sprite position)
        // Only set the target position if the character is not moving towards it
        if (col < arrayPosX && row == arrayPosY && !isMoving)
        {
            this->playerSprite.posX -= Config::TileSize;
            isMoving = true;
        }
        else if (col > arrayPosX && row == arrayPosY && !isMoving)
        {
            this->playerSprite.posX += Config::TileSize;
            isMoving = true;
        }
        else if (col == arrayPosX && row < arrayPosY && !isMoving)
        {
            this->playerSprite.posY -= Config::TileSize;
            isMoving = true;
        }
        else if (col == arrayPosX && row > arrayPosY && !isMoving)
        {
            this->playerSprite.posY += Config::TileSize;
            isMoving = true;
        }

        this->arrayPosX = col;
        this->arrayPosY = row;
    }

    // Move the character step by step
    void NonPlayerChar::UpdateCurrentPosition()
    {
        if (this->playerSprite.posX < currentPosition.x) currentPosition.x -= 1;
        else if (this->playerSprite.posX > currentPosition.x) currentPosition.x += 1;
        else if (this->playerSprite.posY < currentPosition.y) currentPosition.y -= 1;
        else if (this->playerSprite.posY > currentPosition.y) currentPosition.y += 1;

        if (this->playerSprite.posX == currentPosition.x && this->playerSprite.posY == currentPosition.y)
            isMoving = false;
    }

    void NonPlayerChar::ResetPlayerStats()
    {
        this->SetStartPosition();
        path = this->map->path.path;
        allowMovement = false;
        reachedGoal = false;
        currentProgressOnGraph = 0;
        isMoving = false;
        this->totalWeight = 0;
        this->strength = 10;
        this->portableWeight = strength * strengthMultiplier;
    }

    void NonPlayerChar::SetStartPosition()
    {
        BaseChar::SetStartPosition();
        this->currentPosition.x = (float) this->map->GetStartCol() * Config::TileSize;
        this->currentPosition.y = (float) this->map->GetStartRow() * Config::TileSize;
    }

    void NonPlayerChar::PickUpItem()
    {
        try
        {
            // Only pick up the item if he can carry it, otherwise he keeps walking
            if ((GetCurrentWeight() + (int)map->itemTiles[arrayPosX][arrayPosY].item->GetWeight()) <= GetPortableWeight())
            {
                inventory.AddItem(map->itemTiles[arrayPosX][arrayPosY].item);
                totalWeight += (int)map->itemTiles[arrayPosX][arrayPosY].item->GetWeight();
                // if the item is an equippable item, it automatically equips
                EquipItem();

                map->itemTiles[arrayPosX][arrayPosY].item = nullptr;
                map->map[arrayPosX][arrayPosY] = Game::TileState::PASSABLE; // only resets tile to passable if item was added (because of exception it jumps directly into catch block)
            }
            else std::cout << "Robot can't carry this item." << std::endl;
        }
        catch (Error::InventoryFull &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void NonPlayerChar::EquipItem()
    {
        try
        {
            std::shared_ptr<Items::BaseItem> temporaryItem = map->itemTiles[arrayPosX][arrayPosY].item;
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

    bool NonPlayerChar::PlayerOnExitTile()
    {
        return (int)currentPosition.x == this->map->GetEndCol() && (int)currentPosition.y == this->map->GetEndRow();
    }

    void NonPlayerChar::OpenInventory()
    {
        if (IsKeyPressed(KEY_T))
        {
            if (this->GetInventoryUI()->ShowInventory()) this->GetInventoryUI()->SetShowInventory(false);
            else this->GetInventoryUI()->SetShowInventory(true);
        }
    }

    void NonPlayerChar::SortItems()
    {
        switch (this->GetInventoryUI()->GetCurrentSortButton())
        {
            case UI::CurrentSortButton::WEIGHT: inventory.SortForWeight(); break;
            case UI::CurrentSortButton::NAME: inventory.SortForName(); break;
            case UI::CurrentSortButton::COST: inventory.SortForCost(); break;
        }
    }

}
