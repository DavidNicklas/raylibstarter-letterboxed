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
        void DropItemOnGround();
        void SortItems();
        bool PlayerOnExitTile() override;
        void OpenInventory();

        std::shared_ptr<Items::BaseItem> markedForDropItem = nullptr;

        Texture2D playerTex = LoadTexture("../../assets/graphics/bear.png");
        Sound invOpen = LoadSound("../../assets/audio/sfx/buttonClick.mp3");
    };

}

