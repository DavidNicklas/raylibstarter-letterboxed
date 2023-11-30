#pragma once

#include "config.h"
#include "../Sprite.h"
#include "../Character/PlayerChar.h"

namespace UI
{

    class InventoryUI
    {
    public:
        void Update();
        void Draw();

        Char::PlayerChar* playerChar = nullptr;

    private:
        bool showInventory = false;

        Sprite invTex = Sprite(0, 0, "../../assets/graphics/inventoryScreen.png");
        Sprite highlightBox = Sprite(0, 0, "../../assets/graphics/invHighlightBox.png");

        void DrawHighlightBox();
        Vector2 highlightBoxOffset = {44, 50};

        void DrawPlayerStats();

    };

}
