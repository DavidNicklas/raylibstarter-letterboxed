#pragma once

#include <memory>

#include "../Items/BaseItem.h"

namespace Game
{

    struct ItemTile
    {
        std::shared_ptr<Items::BaseItem> item;
        ItemTile() = default;
        ItemTile(int x, int y) : x(x), y(y), item(nullptr) {}
        int x;
        int y;
    };

    enum TileState {NONE, BLOCKED, PASSABLE, START, EXIT, ITEM};

}