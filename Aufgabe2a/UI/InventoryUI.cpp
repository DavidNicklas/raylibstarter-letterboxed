#include "InventoryUI.h"

namespace UI
{

    void InventoryUI::Update()
    {
        if (IsKeyPressed(KEY_E))
        {
            if (!showInventory) showInventory = true;
            else showInventory = false;
        }

        if (showInventory)
        {
            if (IsKeyPressed(KEY_D) && highlightBox.posX < (int)highlightBoxOffset.x * 4){
                highlightBox.posX += (int)highlightBoxOffset.x;
            }
            if (IsKeyPressed(KEY_A) && highlightBox.posX > 0){
                highlightBox.posX -= (int)highlightBoxOffset.x;
            }
            if (IsKeyPressed(KEY_W) && highlightBox.posY > 0){
                highlightBox.posY -= (int)highlightBoxOffset.y;
            }
            if (IsKeyPressed(KEY_S) && highlightBox.posY < (int)highlightBoxOffset.y){
                highlightBox.posY += (int)highlightBoxOffset.y;
            }
        }
    }

    void InventoryUI::Draw()
    {
        BeginBlendMode(BLEND_ALPHA);
        if (showInventory)
        {
            DrawRectangle(0, 0, Config::ScreenWidth, Config::ScreenHeight, Fade(BROWN, 0.5f));
            DrawTexture(invTex.GetTexture(), invTex.posX, invTex.posY, WHITE);
            DrawHighlightBox();
        }
        EndBlendMode();
    }

    void InventoryUI::DrawHighlightBox()
    {
        DrawTexture(highlightBox.GetTexture(), highlightBox.posX, highlightBox.posY, WHITE);
    }
}