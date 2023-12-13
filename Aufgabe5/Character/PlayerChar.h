#pragma once

#include <memory>
#include "BaseChar.h"
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

        void Move() override;
        void ResetPlayerStats() override;

        // Gets for stats
        int GetStrength() const { return this->strength; }
        int GetHealth() const { return this->health; }
        int GetPortableWeight() const { return this->portableWeight; }
        int GetCurrentWeight() const { return this->totalWeight; }

        UI::InventoryUI* inventoryUi = nullptr;

    private:
        int health = 20;

        void DropItem();
        void EquipItem();

        std::shared_ptr<Items::BaseItem> markedForDropItem = nullptr;
        void DropItemOnGround();
        void SortItems();

    };

}

