#include "InventoryUI.h"

namespace UI
{

    InventoryUI::InventoryUI(Char::BaseChar* character) : character(character)
    {
        selectedInventorySlot = 0;
        showInventory = false;
        showSortMenu = false;
        currentSortButton = CurrentSortButton::WEIGHT;
    }

    void InventoryUI::Update()
    {
        if (showInventory)
        {
            if (IsKeyPressed(KEY_P))
            {
                if (!showSortMenu) showSortMenu = true;
                else showSortMenu = false;
            }

            if (!showSortMenu) NavigateInventory();
            else NavigateSortMenu();
        }
        else
        {
            ResetUI();
        }
    }

    void InventoryUI::ResetUI()
    {
        showInventory = false;
        showSortMenu = false;
        // Reset the box to first slot
        highlightBox.posX = 0;
        highlightBox.posY = 0;
        selectedInventorySlot = 0;
        selectedItem = nullptr;
    }

    void InventoryUI::Draw()
    {
        if (showInventory)
        {
            // Draw inv background tex
            BeginBlendMode(BLEND_ALPHA);
            DrawRectangle(0, 0, Config::ScreenWidth, Config::ScreenHeight, Fade(BROWN, 0.5f));
            EndBlendMode();

            DrawTexture(invTex.GetTexture(), invTex.posX, invTex.posY, WHITE);
            if (showSortMenu) DrawSortMenu();

            DrawHighlightBox();
            DrawPlayerStats();
            DrawItems();
            DrawItemsInfo();
            DrawEquipmentItems();
            DrawTexture(equipmentSlotKeys.GetTexture(), equipmentSlotKeys.posX, equipmentSlotKeys.posY, WHITE);

        }
    }

    void InventoryUI::NavigateInventory()
    {
        if (IsKeyPressed(KEY_D) && selectedInventorySlot < 9)
        {
            highlightBox.posX += (int) highlightBoxOffset.x;

            // If player is at inv slot 4, push the box one below and at the beginning of the inv
            if (selectedInventorySlot == 4)
            {
                highlightBox.posY += (int) highlightBoxOffset.y;
                highlightBox.posX = 0;
            }

            selectedInventorySlot++;
            // if there is an item on the slot, store it in the selectedItem
            if (character->inventory.itemContainer[selectedInventorySlot] != nullptr) selectedItem = character->inventory.itemContainer[selectedInventorySlot];
            else selectedItem = nullptr;
        }
        if (IsKeyPressed(KEY_A) && selectedInventorySlot > 0)
        {
            highlightBox.posX -= (int) highlightBoxOffset.x;

            // If player is at inv slot 5, push the box upwards and at the end of the inv
            if (selectedInventorySlot == 5)
            {
                highlightBox.posY -= (int) highlightBoxOffset.y;
                highlightBox.posX += (int) highlightBoxOffset.x * 5;
            }

            selectedInventorySlot--;
            // if there is an item on the slot, store it in the selectedItem
            if (character->inventory.itemContainer[selectedInventorySlot] != nullptr) selectedItem = character->inventory.itemContainer[selectedInventorySlot];
            else selectedItem = nullptr;
        }
    }

    void InventoryUI::NavigateSortMenu()
    {
        if (IsKeyPressed(KEY_D))
        {
            if (currentSortButton == CurrentSortButton::NAME) currentSortButton = CurrentSortButton::COST;
            if (currentSortButton == CurrentSortButton::WEIGHT) currentSortButton = CurrentSortButton::NAME;
        }
        if (IsKeyPressed(KEY_A))
        {
            if (currentSortButton == CurrentSortButton::NAME) currentSortButton = CurrentSortButton::WEIGHT;
            if (currentSortButton == CurrentSortButton::COST) currentSortButton = CurrentSortButton::NAME;
        }
    }

    void InventoryUI::DrawHighlightBox()
    {
        DrawTexture(highlightBox.GetTexture(), highlightBox.posX, highlightBox.posY, WHITE);
    }

    void InventoryUI::DrawPlayerStats()
    {
        DrawText(("Health: " + std::to_string(character->GetHealth())).c_str(), 48, 190, 8, BLACK);
        DrawText(("Strength: " + std::to_string(character->GetStrength())).c_str(), 48, 205, 8, BLACK);
        DrawText(("Weight: " + std::to_string(character->GetCurrentWeight()) + "/" +
                  std::to_string(character->GetPortableWeight())).c_str(), 130, 205, 8, BLACK);
    }

    void InventoryUI::DrawItemsInfo()
    {
        if (selectedItem != nullptr)
        {
            DrawText(("Info: " + selectedItem->GetDesc()).c_str(), 230, 175, 8, BLACK);
            DrawText(("Name: " + selectedItem->GetName()).c_str(), 230, 188, 8, BLACK);
            DrawText(("Weight: " + std::to_string((int)selectedItem->GetWeight())).c_str(), 230, 201, 8, BLACK);
            if (selectedItem->GetItemType() == Items::ItemType::EQUIPPABLE) DrawText("Can equip: Yes", 350, 188, 8, BLACK);
            else DrawText("Can equip: No", 350, 188, 8, BLACK);
            DrawText(("Cost: " + std::to_string((int)selectedItem->GetCost())).c_str(), 350, 201, 8, BLACK);
        }
    }

    // If there is an item in a slot, it takes its texture and draws it in the inventory
    void InventoryUI::DrawItems()
    {
        try
        {
            if (character->inventory.GetItem(0))
            {
                DrawTextureEx(character->inventory.GetItem(0)->texture.GetTexture(), slot0Pos, 0, 1.9, WHITE);
            }
            if (character->inventory.GetItem(1))
            {
                DrawTextureEx(character->inventory.GetItem(1)->texture.GetTexture(), slot1Pos, 0, 1.9, WHITE);
            }
            if (character->inventory.GetItem(2))
            {
                DrawTextureEx(character->inventory.GetItem(2)->texture.GetTexture(), slot2Pos, 0, 1.9, WHITE);
            }
            if (character->inventory.GetItem(3))
            {
                DrawTextureEx(character->inventory.GetItem(3)->texture.GetTexture(), slot3Pos, 0, 1.9, WHITE);
            }
            if (character->inventory.GetItem(4))
            {
                DrawTextureEx(character->inventory.GetItem(4)->texture.GetTexture(), slot4Pos, 0, 1.9, WHITE);
            }
            if (character->inventory.GetItem(5))
            {
                DrawTextureEx(character->inventory.GetItem(5)->texture.GetTexture(), slot5Pos, 0, 1.9, WHITE);
            }
            if (character->inventory.GetItem(6))
            {
                DrawTextureEx(character->inventory.GetItem(6)->texture.GetTexture(), slot6Pos, 0, 1.9, WHITE);
            }
            if (character->inventory.GetItem(7))
            {
                DrawTextureEx(character->inventory.GetItem(7)->texture.GetTexture(), slot7Pos, 0, 1.9, WHITE);
            }
            if (character->inventory.GetItem(8))
            {
                DrawTextureEx(character->inventory.GetItem(8)->texture.GetTexture(), slot8Pos, 0, 1.9, WHITE);
            }
            if (character->inventory.GetItem(9))
            {
                DrawTextureEx(character->inventory.GetItem(9)->texture.GetTexture(), slot9Pos, 0, 1.9, WHITE);
            }
        }
        catch (Error::InventoryFull& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void InventoryUI::DrawEquipmentItems()
    {
        if (character->inventory.equipmentContainer[0] != nullptr)
        {
            DrawTextureEx(character->inventory.equipmentContainer[0]->texture.GetTexture(), hatPos, 0, 1.9, WHITE);
        }
        if (character->inventory.equipmentContainer[1] != nullptr)
        {
            DrawTextureEx(character->inventory.equipmentContainer[1]->texture.GetTexture(), honeyPos, 0, 1.9, WHITE);
        }
        if (character->inventory.equipmentContainer[2] != nullptr)
        {
            DrawTextureEx(character->inventory.equipmentContainer[2]->texture.GetTexture(), shoesPos, 0, 1.9, WHITE);
        }
    }

    void InventoryUI::DrawSortMenu()
    {
        DrawTexture(invSortMenu.GetTexture(), 0, 0, WHITE);

        switch (currentSortButton)
        {
            case CurrentSortButton::WEIGHT: DrawTexture(weightHighlight.GetTexture(), 0, 0, WHITE); break;
            case CurrentSortButton::NAME: DrawTexture(nameHighlight.GetTexture(), 0, 0, WHITE); break;
            case CurrentSortButton::COST: DrawTexture(costHighlight.GetTexture(), 0, 0, WHITE); break;
        }
    }

}