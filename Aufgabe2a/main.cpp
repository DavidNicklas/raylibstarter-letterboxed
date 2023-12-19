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

    while (!WindowShouldClose())
    {
        /*** Logic ***/
        CheckFullscreen();

        game.Update();

        try
        {
            if (IsKeyPressed(KEY_U)) inventory.AddItem(coffee);
            if (IsKeyPressed(KEY_O)) inventory.AddItem(hat);
            if (IsKeyPressed(KEY_L)) inventory.EquipItem(hat);
            if (IsKeyPressed(KEY_J)) inventory.EquipItem(coffee);
            if (IsKeyPressed(KEY_K)) std::cout << inventory.GetItem(2)->GetName() << std::endl;
            if (IsKeyPressed(KEY_I)) inventory.UnequipItem(Items::DesiredEquipmentSlot::HAT);
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
        catch (Error::UnequipError &e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (Error::SlotIsEmpty &e)
        {
            std::cout << e.what() << std::endl;
        }

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