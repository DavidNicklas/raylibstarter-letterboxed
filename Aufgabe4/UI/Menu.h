#pragma once

#include "../Sprite.h"
#include "../Character/PlayerChar.h"
#include "config.h"

namespace UI
{

    class Menu
    {
    public:
        void Update(Char::PlayerChar* player);
        void Draw();

        bool showMenu = false;

    private:
        bool playerInInfoBoxRange = false;

        Rectangle infoBoxHitBox = {26 * Config::TileSize, 15 * Config::TileSize, 4 * Config::TileSize, 2 * Config::TileSize};

        Sprite infoButton = Sprite(417, 255, "../../assets/graphics/backgrounds/infoButton.png");
        Sprite infoMenu = Sprite(60, 20, "../../assets/graphics/backgrounds/infoMenu.png");
    };

}