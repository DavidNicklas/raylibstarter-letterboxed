#pragma once

#include <memory>
#include "raylib.h"
#include "../Sprite.h"
#include "../Inventory/Inventory.hpp"

namespace Game
{
    class Map;
}
namespace UI
{
    class InventoryUI;
}

namespace Char
{

    class BaseChar
    {
    public:
        virtual void Move() = 0;
        virtual void ResetPlayerStats() = 0;
        virtual void SetStartPosition();
        bool CanMove(Direction direction);
        bool ReachedGoal() const { return this->reachedGoal; }

        // Gets for stats
        int GetStrength() const { return this->strength; }
        int GetHealth() const { return this->health; }
        int GetPortableWeight() const { return this->portableWeight; }
        int GetCurrentWeight() const { return this->totalWeight; }

        // Position of Player is implemented by Sprite
        Sprite playerSprite = Sprite();

        Game::Map* map = nullptr;

        Inventory::Inventory<std::shared_ptr<Items::BaseItem>, 10> inventory;
        UI::InventoryUI* GetInventoryUI() { return this->inventoryUi; }

    protected:
        bool PlayerOnItemTile();
        virtual bool PlayerOnExitTile() = 0;
        virtual void PickUpItem();
        virtual void EquipItem();

        // Is needed to move player correctly
        int arrayPosX = 0;
        int arrayPosY = 0;
        Direction direction;

        UI::InventoryUI* inventoryUi = nullptr;

        bool reachedGoal = false; // Stores if the player has reached the exit tile
        int health = 0;
        int strength = 10; // Defines the weight, the player can carry in his inventory
        int totalWeight = 0; // Defines the current weight of all his items in his inventory
        int strengthMultiplier = 2;
        int portableWeight = strength * strengthMultiplier; // Defines the weight he can max carry
    };

}
