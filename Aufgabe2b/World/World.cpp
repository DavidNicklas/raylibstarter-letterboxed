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

        //map->playerChar = playerChar;

        playerChar->map = map;
        playerChar->SetStartPosition();
    }

    void World::DeleteObjects()
    {
        delete map;
        delete playerChar;
    }

}
