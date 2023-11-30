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

        bool ShowInventory() const { return this->showInventory; }

    private:
        bool showInventory = false;

        Sprite invTex = Sprite(0, 0, "../../assets/graphics/inventoryScreen.png");
        Sprite highlightBox = Sprite(0, 0, "../../assets/graphics/invHighlightBox.png");

        void DrawHighlightBox();
        Vector2 highlightBoxOffset = {44, 50};

        void DrawPlayerStats();

    };

}
