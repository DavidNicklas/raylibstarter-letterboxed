#include "World.h"

namespace Game
{

    void World::Update()
    {
        map->Update();
        playerChar->Update();
        inventoryUi->Update();
    }

    void World::Draw()
    {
        map->Draw();
        playerChar->Draw();
        inventoryUi->Draw();
    }

    void World::CreateObjects()
    {
        map = new Map();
        playerChar = new Char::PlayerChar();
        inventoryUi = new UI::InventoryUI();

        // map needs the player for resetting the position
        map->playerChar = playerChar;

        // inventory need player for drawing stats
        inventoryUi->playerChar = playerChar;

        // player needs map for moving on it
        playerChar->map = map;
        playerChar->SetStartPosition();
    }

    void World::DeleteObjects()
    {
        delete map;
        delete playerChar;
        delete inventoryUi;
    }

}
