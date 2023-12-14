#pragma once

#include <vector>
#include <memory>
#include "Map.h"
#include "../Character/PlayerChar.h"
#include "../UI/Menu.h"
#include "../Character/NonPlayerChar.h"
#include "../UI/GameOver.h"

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
        Char::NonPlayerChar* robot;
        UI::Menu* menu;
        UI::GameOver* gameOver;

        void CreateObjects();
    };

}