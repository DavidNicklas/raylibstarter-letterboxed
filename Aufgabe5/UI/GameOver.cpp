#include "GameOver.h"
#include "config.h"

namespace UI
{
    void GameOver::Update()
    {
        if (playerChar->ReachedGoal() || nonPlayerChar->ReachedGoal())
        {

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

            DrawTexture(gameOverScreen.GetTexture(), gameOverScreen.posX, gameOverScreen.posY, WHITE);
        }
    }
}