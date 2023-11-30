#include "World.h"

namespace Game
{

    void World::Update()
    {
        for (const auto& object : objects)
        {
            object->Update();
        }
    }

    void World::Draw()
    {
        for (const auto& object : objects)
        {
            object->Draw();
        }
    }

    void World::CreateObjects()
    {
        ObjectType map = std::make_shared<Map>();
        ObjectType menu = std::make_shared<UI::Menu>();
        ObjectType inventoryUI = std::make_shared<UI::InventoryUI>();

        objects.push_back(map);
        objects.push_back(menu);
        objects.push_back(inventoryUI);
    }

}