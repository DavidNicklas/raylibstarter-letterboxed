#pragma once

#include <memory>
#include "raylib.h"
#include "../Sprite.h"
#include "../Inventory/Inventory.hpp"

namespace Game
{
    class Map;
}

namespace Char
{

    enum Direction {LEFT, RIGHT, UP, DOWN};

    class BaseChar
    {
    public:
        virtual void Move() = 0;
        virtual void ResetPlayerStats() = 0;
        virtual void SetStartPosition();
        bool CanMove(Direction direction);

        // Position of Player is implemented by Sprite
        Sprite playerSprite = Sprite();

        Game::Map* map = nullptr;

        Inventory::Inventory<std::shared_ptr<Items::BaseItem>, 10> inventory;

    protected:
        bool PlayerOnItemTile();
        void PickUpItem();

        // Is needed to move player correctly
        int arrayPosX;
        int arrayPosY;
        Direction direction;

        int strength = 10; // Defines the weight, the player can carry in his inventory
        int totalWeight = 0; // Defines the current weight of all his items in his inventory
        int strengthMultiplier = 2;
        int portableWeight = strength * strengthMultiplier; // Defines the weight he can max carry
    };

}
