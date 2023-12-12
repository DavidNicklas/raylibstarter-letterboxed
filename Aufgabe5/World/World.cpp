#include "World.h"

namespace Game
{

    void World::Update()
    {
        map->Update();
        playerChar->Update();
        inventoryUi->Update();
        menu->Update(playerChar);
        robot->Update();
    }

    void World::Draw()
    {
        map->Draw();
        playerChar->Draw();
        robot->Draw();
        menu->Draw();
        inventoryUi->Draw();
    }

    void World::CreateObjects()
    {
        map = new Map();
        playerChar = new Char::PlayerChar(playerTex);
        robot = new Char::NonPlayerChar(playerTex);
        inventoryUi = new UI::InventoryUI();
        menu = new UI::Menu();

        // map needs the player for resetting the position
        map->playerChar = playerChar;
        map->nonPlayerChar = robot;

        // inventory need player for drawing stats
        inventoryUi->playerChar = playerChar;

        // player needs map for moving on it and inventoryUI for dropping items
        playerChar->map = map;
        playerChar->inventoryUi = inventoryUi;
        playerChar->SetStartPosition();

        robot->map = map;
        robot->SetPath(map->path.path);
        robot->SetStartPosition();
    }

    void World::DeleteObjects()
    {
        delete map;
        delete playerChar;
        delete inventoryUi;
        delete menu;
    }

}
