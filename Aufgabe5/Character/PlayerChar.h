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

    private:
        void DropItem();

        std::shared_ptr<Items::BaseItem> markedForDropItem = nullptr;
        void DropItemOnGround();
        void SortItems();

        bool PlayerOnExitTile() override;

        Texture2D playerTex = LoadTexture("../../assets/graphics/bear.png");
    };

}

