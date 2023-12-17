#include <cstdlib>

#include "RaylibHelp.h"
#include "World/World.h"
#include "Items/Coffee.h"
#include "Inventory/Inventory.hpp"
#include "Items/Equipment/Hat.h"

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

    Inventory::Inventory<std::shared_ptr<Items::BaseItem>, 3> inventory;
    std::shared_ptr<Items::BaseItem> coffee = std::make_shared<Items::Coffee>();
    std::shared_ptr<Items::BaseItem> hat = std::make_shared<Items::Hat>();

    try
    {
        inventory.AddItem(coffee);
        inventory.AddItem(coffee);
        inventory.AddItem(hat);
        inventory.EquipItem(coffee);
        inventory.EquipItem(hat);
        inventory.AddItem(coffee);
        inventory.UnequipItem(0);

        std::cout << inventory.GetItem(2)->GetName();
    }
    catch (Error::OutOfRange &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (Error::InventoryFull &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (Error::EquipmentError &e)
    {
        std::cout << e.what() << std::endl;
    }

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