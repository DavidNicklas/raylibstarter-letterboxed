#include "GameOver.h"
#include "config.h"
#include "../World/Map.h"

namespace UI
{
    void GameOver::Update()
    {
        if (playerChar->ReachedGoal() || nonPlayerChar->ReachedGoal())
        {
            NavigateGameOverMenu();
        }
    }

    void GameOver::Draw()
    {
        if (playerChar->ReachedGoal() || nonPlayerChar->ReachedGoal())
        {
            // Draw background texture
            BeginBlendMode(BLEND_ALPHA);
            DrawRectangle(0, 0, Config::ScreenWidth, Config::ScreenHeight, Fade(BROWN, 0.5f));
            EndBlendMode();

            DrawGameOverMenu();
        }
    }

    void GameOver::NavigateGameOverMenu()
    {
        if (IsKeyPressed(KEY_S))
        {
            if (currentGameOverOption == CurrentGameOverOption::PLAY_AGAIN) currentGameOverOption = CurrentGameOverOption::SHOW_INVENTORY;
        }
        if (IsKeyPressed(KEY_W))
        {
            if (currentGameOverOption == CurrentGameOverOption::SHOW_INVENTORY) currentGameOverOption = CurrentGameOverOption::PLAY_AGAIN;
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            switch (currentGameOverOption)
            {
                case CurrentGameOverOption::PLAY_AGAIN:
                    map->ResetMap();
                    break;
                case CurrentGameOverOption::SHOW_INVENTORY:
                    
                    break;
            }
        }
    }

    void GameOver::DrawGameOverMenu()
    {
        DrawTexture(gameOverScreen.GetTexture(), gameOverScreen.posX, gameOverScreen.posY, WHITE);

        switch (currentGameOverOption)
        {
            case CurrentGameOverOption::PLAY_AGAIN: DrawTexture(playAgainHighlight.GetTexture(), playAgainHighlight.posX, playAgainHighlight.posY, WHITE); break;
            case CurrentGameOverOption::SHOW_INVENTORY: DrawTexture(showInventoryHighlight.GetTexture(), showInventoryHighlight.posX, showInventoryHighlight.posY, WHITE); break;
        }
    }
}