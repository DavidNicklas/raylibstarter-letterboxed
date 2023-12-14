#include "World.h"

namespace Game
{

    void World::Update()
    {
        map->Update();
        // Only update the player if robot is not in inventory & if the robot has not reached the goal
        if (!robot->GetInventoryUI()->ShowInventory() && !robot->ReachedGoal())
            playerChar->Update();
        // Only update the robot if player is not in inventory & if the player has not reached the goal
        if (!playerChar->GetInventoryUI()->ShowInventory() && !playerChar->ReachedGoal())
            robot->Update();
        menu->Update(playerChar);
        gameOver->Update();
    }

    void World::Draw()
    {
        map->Draw();
        gameOver->Draw();
        robot->Draw();
        playerChar->Draw();
        menu->Draw();
    }

    void World::CreateObjects()
    {
        map = new Map();
        playerChar = new Char::PlayerChar();
        robot = new Char::NonPlayerChar();
        menu = new UI::Menu();
        gameOver = new UI::GameOver();

        // map needs the player for resetting the position
        map->playerChar = playerChar;
        map->nonPlayerChar = robot;

        // player needs map for moving on it and inventoryUI for dropping items
        playerChar->map = map;
        playerChar->SetStartPosition();

        // robot needs map and path for moving
        robot->map = map;
        robot->SetPath(map->path.path);
        robot->SetStartPosition();

        // gameOver need characters to check if its active, needs the map to reset it if player presses play again
        gameOver->playerChar = playerChar;
        gameOver->nonPlayerChar = robot;
        gameOver->map = map;
    }

    void World::DeleteObjects()
    {
        delete map;
        delete playerChar;
        delete robot;
        delete menu;
        delete gameOver;
    }

}
