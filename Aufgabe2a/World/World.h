#pragma once

#include <vector>
#include <memory>
#include "Map.h"
#include "../UI/Menu.h"
#include "../UI/InventoryUI.h"

namespace Game
{

    typedef std::shared_ptr<GameObject> ObjectType;

    class World
    {
    public:
        World() { CreateObjects(); }

        void Update();
        void Draw();

    private:
        std::vector<ObjectType> objects;

        void CreateObjects();
    };

}