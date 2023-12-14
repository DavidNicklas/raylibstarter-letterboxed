#pragma once

#include <memory>
#include "BaseChar.h"
#include "../Items/BaseItem.h"

namespace Char
{

    class PlayerChar : public BaseChar
    {
    public:
        PlayerChar();

        void Update();
        void Draw();

        void Move() override;
        void ResetPlayerStats() override;

        // Gets for stats
        int GetStrength() const { return this->strength; }
        int GetHealth() const { return this->health; }
        int GetPortableWeight() const { return this->portableWeight; }
        int GetCurrentWeight() const { return this->totalWeight; }

    private:
        int health = 20;

        void DropItem();

        std::shared_ptr<Items::BaseItem> markedForDropItem = nullptr;
        void DropItemOnGround();
        void SortItems();

        bool PlayerOnExitTile() override;

        Texture2D playerTex = LoadTexture("../../assets/graphics/bear.png");
    };

}

