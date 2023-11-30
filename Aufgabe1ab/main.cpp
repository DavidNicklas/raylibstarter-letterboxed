#include <cstdlib>

#include "RaylibHelp.h"
#include "World/World.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Config::ScreenWidth, Config::ScreenHeight, Config::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    RenderTexture2D canvas = LoadRenderTexture(Config::ScreenWidth, Config::ScreenHeight);
    float renderScale{}; //those two are relevant to drawing and code-cleanliness
    Rectangle renderRec{};

    Game::World game = Game::World();

    while (!WindowShouldClose())
    {
        /*** Logic ***/
        CheckFullscreen();

        game.Update();

        /*** Drawing ***/
        BeginDrawing();
        BeginTextureMode(canvas);
        {
            ClearBackground(BEIGE);
            game.Draw();
        }
        EndTextureMode();
        Letterbox(renderScale, canvas, renderRec);
        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}