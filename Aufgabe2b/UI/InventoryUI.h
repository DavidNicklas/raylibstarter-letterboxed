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
        int selectedInventorySlot = 0;

        Sprite invTex = Sprite(0, 0, "../../assets/graphics/inventoryScreen.png");

        void DrawPlayerStats();
        void DrawItems();

        // The box that shows which slot is currently highlighted
        Sprite highlightBox = Sprite(0, 0, "../../assets/graphics/invHighlightBox.png");
        void DrawHighlightBox();
        Vector2 highlightBoxOffset = {44, 50};

        // Those vectors are needed to draw the items at the right position in the inventory
        Vector2 slot0Pos = {227, 61};
        Vector2 slot1Pos = {slot0Pos.x + (1 * highlightBoxOffset.x), slot0Pos.y};
        Vector2 slot2Pos = {slot0Pos.x + (2 * highlightBoxOffset.x), slot0Pos.y};
        Vector2 slot3Pos = {slot0Pos.x + (3 * highlightBoxOffset.x), slot0Pos.y};
        Vector2 slot4Pos = {slot0Pos.x + (4 * highlightBoxOffset.x), slot0Pos.y};
        Vector2 slot5Pos = {slot0Pos.x, slot0Pos.y + highlightBoxOffset.y};
        Vector2 slot6Pos = {slot0Pos.x + (1 * highlightBoxOffset.x), slot0Pos.y + highlightBoxOffset.y};
        Vector2 slot7Pos = {slot0Pos.x + (2 * highlightBoxOffset.x), slot0Pos.y + highlightBoxOffset.y};
        Vector2 slot8Pos = {slot0Pos.x + (3 * highlightBoxOffset.x), slot0Pos.y + highlightBoxOffset.y};
        Vector2 slot9Pos = {slot0Pos.x + (4 * highlightBoxOffset.x), slot0Pos.y + highlightBoxOffset.y};


    };

}
