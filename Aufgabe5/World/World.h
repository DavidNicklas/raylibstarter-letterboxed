#pragma once

#include <vector>
#include <memory>
#include "Map.h"
#include "../UI/InventoryUI.h"
#include "../Character/PlayerChar.h"
#include "../UI/Menu.h"

namespace Game
{

    class World
    {
    public:
        World() { CreateObjects(); }

        void Update();
        void Draw();

        void DeleteObjects();
    private:
        Game::Map* map;
        Char::PlayerChar* playerChar;
        UI::InventoryUI* inventoryUi;
        UI::Menu* menu;

        Texture2D playerTex = LoadTexture("../../assets/graphics/bear.png");

        void CreateObjects();
    };

}