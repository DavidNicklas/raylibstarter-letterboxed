#pragma once

#include <vector>
#include <memory>
#include "Map.h"
#include "../UI/Menu.h"
#include "../UI/InventoryUI.h"
#include "../Character/PlayerChar.h"

namespace Game
{

    class World
    {
    public:
        World() { CreateObjects(); }

        void Update();
        void Draw();

    private:
        Game::Map* map;
        Char::PlayerChar* playerChar;
        UI::InventoryUI* inventoryUi;

        void CreateObjects();
        void DeleteObjects();
    };

}