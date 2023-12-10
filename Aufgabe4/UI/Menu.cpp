#include "Menu.h"

namespace UI
{

    void Menu::Update(Char::PlayerChar* player)
    {
        if (IsKeyPressed(KEY_I)) showMenu = !showMenu;

        Rectangle playerRec = {static_cast<float>(player->playerSprite.posX),
                                static_cast<float>(player->playerSprite.posY),
                                Config::TileSize,
                                Config::TileSize};

        if (CheckCollisionRecs(playerRec,infoBoxHitBox))
            playerInInfoBoxRange = true;
        else
            playerInInfoBoxRange = false;
    }

    void Menu::Draw()
    {
        if (playerInInfoBoxRange)
        {
            BeginBlendMode(BLEND_ALPHA);
            DrawTexture(infoButton.GetTexture(), infoButton.posX, infoButton.posY, Fade(WHITE, 0.3));
            EndBlendMode();
        }
        else DrawTexture(infoButton.GetTexture(), infoButton.posX, infoButton.posY, WHITE);

        if (showMenu) DrawTextureEx(infoMenu.GetTexture(), {static_cast<float>(infoMenu.posX), static_cast<float>(infoMenu.posY)}, 0.0f, 0.75f, WHITE);
    }

}