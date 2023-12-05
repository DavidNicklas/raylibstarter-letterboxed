#pragma once

#include <memory>
#include "BaseChar.h"
#include "../Inventory/Inventory.hpp"
#include "../Items/BaseItem.h"

namespace UI
{
    class InventoryUI;
}

namespace Char
{

    class PlayerChar : public BaseChar
    {
    public:
        PlayerChar(Texture2D newTexture);

        void Update();
        void Draw();

        void ResetPlayerStats() override;
        void SetStartPosition() override;
        void Move() override;

        bool PlayerOnItemTile();
        void PickUpItem();
        void DropItem();
        void EquipItem();

        // Gets for stats
        int GetStrength() const { return this->strength; }
        int GetHealth() const { return this->health; }
        int GetPortableWeight() const { return this->portableWeight; }
        int GetCurrentWeight() const { return this->totalWeight; }

        Inventory::Inventory<std::shared_ptr<Items::BaseItem>, 10> inventory;

        UI::InventoryUI* inventoryUi = nullptr;

    private:
        int strength = 10; // Defines the weight, the player can carry in his inventory
        int totalWeight = 0; // Defines the current weight of all his items in his inventory
        int strengthMultiplier = 2;
        int portableWeight = strength * strengthMultiplier; // Defines the weight he can max carry
        int health = 20;

        std::shared_ptr<Items::BaseItem> markedForDropItem = nullptr;
        void DropItemOnGround();
        void SortItems();

    };

}

