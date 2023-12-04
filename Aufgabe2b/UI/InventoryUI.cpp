#include "InventoryUI.h"

namespace UI
{

    void InventoryUI::Update()
    {
        if (IsKeyPressed(KEY_E))
        {
            if (!showInventory) showInventory = true;
            else
            {
                showInventory = false;
                // Reset the box to first slot
                highlightBox.posX = 0;
                highlightBox.posY = 0;
                selectedInventorySlot = 0;
            }
        }

        if (showInventory)
        {
            if (IsKeyPressed(KEY_D) && selectedInventorySlot < 9)
            {
                highlightBox.posX += (int)highlightBoxOffset.x;

                // If player is at inv slot 4, push the box one below and at the beginning of the inv
                if (selectedInventorySlot == 4)
                {
                    highlightBox.posY += (int)highlightBoxOffset.y;
                    highlightBox.posX = 0;
                }

                selectedInventorySlot++;
            }
            if (IsKeyPressed(KEY_A) && selectedInventorySlot > 0)
            {
                highlightBox.posX -= (int)highlightBoxOffset.x;

                // If player is at inv slot 5, push the box upwards and at the end of the inv
                if (selectedInventorySlot == 5)
                {
                    highlightBox.posY -= (int)highlightBoxOffset.y;
                    highlightBox.posX += (int)highlightBoxOffset.x * 5;
                }

                selectedInventorySlot--;
            }
        }
    }

    void InventoryUI::Draw()
    {
        if (showInventory)
        {
            BeginBlendMode(BLEND_ALPHA);
            DrawRectangle(0, 0, Config::ScreenWidth, Config::ScreenHeight, Fade(BROWN, 0.5f));
            EndBlendMode();
            DrawTexture(invTex.GetTexture(), invTex.posX, invTex.posY, WHITE);
            DrawHighlightBox();
            DrawPlayerStats();
            DrawItems();
            DrawEquipmentItems();
            DrawTexture(equipmentSlotKeys.GetTexture(), equipmentSlotKeys.posX, equipmentSlotKeys.posY, WHITE);
        }
    }

    void InventoryUI::DrawHighlightBox()
    {
        DrawTexture(highlightBox.GetTexture(), highlightBox.posX, highlightBox.posY, WHITE);
    }

    void InventoryUI::DrawPlayerStats()
    {
        DrawText(("Health: " + std::to_string(playerChar->GetHealth())).c_str(), 48, 190, 8, BLACK);
        DrawText(("Strength: " + std::to_string(playerChar->GetStrength())).c_str(), 48, 205, 8, BLACK);
        DrawText(("Weight: " + std::to_string(playerChar->GetCurrentWeight()) + "/" +
                  std::to_string(playerChar->GetPortableWeight())).c_str(), 130, 205, 8, BLACK);
    }

    void InventoryUI::DrawItems()
    {
        try
        {
            if (playerChar->inventory.GetItem(0))
            {
                DrawTextureEx(playerChar->inventory.GetItem(0)->texture.GetTexture(), slot0Pos, 0, 1.9, WHITE);
            }
            if (playerChar->inventory.GetItem(1))
            {
                DrawTextureEx(playerChar->inventory.GetItem(1)->texture.GetTexture(), slot1Pos, 0, 1.9, WHITE);
            }
            if (playerChar->inventory.GetItem(2))
            {
                DrawTextureEx(playerChar->inventory.GetItem(2)->texture.GetTexture(), slot2Pos, 0, 1.9, WHITE);
            }
            if (playerChar->inventory.GetItem(3))
            {
                DrawTextureEx(playerChar->inventory.GetItem(3)->texture.GetTexture(), slot3Pos, 0, 1.9, WHITE);
            }
            if (playerChar->inventory.GetItem(4))
            {
                DrawTextureEx(playerChar->inventory.GetItem(4)->texture.GetTexture(), slot4Pos, 0, 1.9, WHITE);
            }
            if (playerChar->inventory.GetItem(5))
            {
                DrawTextureEx(playerChar->inventory.GetItem(5)->texture.GetTexture(), slot5Pos, 0, 1.9, WHITE);
            }
            if (playerChar->inventory.GetItem(6))
            {
                DrawTextureEx(playerChar->inventory.GetItem(6)->texture.GetTexture(), slot6Pos, 0, 1.9, WHITE);
            }
            if (playerChar->inventory.GetItem(7))
            {
                DrawTextureEx(playerChar->inventory.GetItem(7)->texture.GetTexture(), slot7Pos, 0, 1.9, WHITE);
            }
            if (playerChar->inventory.GetItem(8))
            {
                DrawTextureEx(playerChar->inventory.GetItem(8)->texture.GetTexture(), slot8Pos, 0, 1.9, WHITE);
            }
            if (playerChar->inventory.GetItem(9))
            {
                DrawTextureEx(playerChar->inventory.GetItem(9)->texture.GetTexture(), slot9Pos, 0, 1.9, WHITE);
            }
        }
        catch (Error::InventoryFull& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void InventoryUI::DrawEquipmentItems()
    {
        if (playerChar->inventory.equipmentContainer[0] != nullptr)
        {
            DrawTextureEx(playerChar->inventory.equipmentContainer[0]->texture.GetTexture(), hatPos, 0, 1.9, WHITE);
        }
        if (playerChar->inventory.equipmentContainer[1] != nullptr)
        {
            DrawTextureEx(playerChar->inventory.equipmentContainer[1]->texture.GetTexture(), honeyPos, 0, 1.9, WHITE);
        }
        if (playerChar->inventory.equipmentContainer[2] != nullptr)
        {
            DrawTextureEx(playerChar->inventory.equipmentContainer[2]->texture.GetTexture(), shoesPos, 0, 1.9, WHITE);
        }
    }
}