#pragma once

#include <memory>
#include "BaseChar.h"
#include "../Inventory/Inventory.hpp"
#include "../Items/BaseItem.h"
#include "../UI/InventoryUI.h"

namespace Char
{

    class PlayerChar : public BaseChar
    {
    public:
        PlayerChar(int posX, int posY);

        void Update();
        void Draw();

        void PickUpItem();
        void DropItem();
        void EquipItem();

        void Move(Direction dir) override;

        Inventory::Inventory<std::shared_ptr<Items::BaseItem>, 10> inventory;

    private:
        int strength = 10; // Defines the weight, the player can carry in his inventory
        int totalWeight = 0;
        int portableWeight = strength * 2;
        int health = 20;

        int CalculateTotalWeight();

        bool inInventory = false;
    };

}

