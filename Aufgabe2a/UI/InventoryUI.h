#pragma once

#include "config.h"
#include "../Sprite.h"
#include "../GameObject.h"

namespace UI
{

    class InventoryUI : public GameObject
    {
    public:
        void Update() override;
        void Draw() override;

        bool showInventory = false;

    private:
        Sprite invTex = Sprite(0, 0, "../../assets/graphics/inventoryScreen.png");
        Sprite highlightBox = Sprite(0, 0, "../../assets/graphics/invHighlightBox.png");

        void DrawHighlightBox();
        Vector2 highlightBoxOffset = {44, 50};

    };

}
