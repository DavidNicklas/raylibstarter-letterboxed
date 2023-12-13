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

        Char::PlayerChar* playerChar;
        Char::NonPlayerChar* nonPlayerChar;

    private:
        Sprite gameOverScreen = Sprite(0, 0, "../../assets/graphics/backgrounds/goalMessage.png");
    };

}