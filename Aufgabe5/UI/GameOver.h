#pragma once

#include "../Character/PlayerChar.h"
#include "../Character/NonPlayerChar.h"

namespace UI
{

    class GameOver
    {
    public:
        void Update();
        void Draw();

        Char::PlayerChar* playerChar = nullptr;
        Char::NonPlayerChar* nonPlayerChar = nullptr;
        Game::Map* map = nullptr;

    private:
        CurrentGameOverOption currentGameOverOption = CurrentGameOverOption::PLAY_AGAIN;

        void NavigateGameOverMenu();
        void DrawGameOverMenu();

        Sprite gameOverScreen = Sprite(0, 0, "../../assets/graphics/backgrounds/goalMessage.png");
        Sprite playAgainHighlight = Sprite(0, 0, "../../assets/graphics/backgrounds/playAgainHighlight.png");
        Sprite showInventoryHighlight = Sprite(0, 0, "../../assets/graphics/backgrounds/showInvHighlight.png");
    };

}