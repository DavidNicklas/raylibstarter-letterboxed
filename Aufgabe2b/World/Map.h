#pragma once

#include <memory>
#include <vector>
#include "raylib.h"
#include "config.h"
#include "../Sprite.h"
#include "../Character/PlayerChar.h"
#include "../Items/Coffee.h"
#include "../Items/Equipment/Hat.h"
#include "../Items/Equipment/Shoes.h"
#include "../Items/Equipment/Honey.h"
#include "../Items/Steak.h"

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

    class Map
    {
    public:
        Map();
        ~Map() { ClearMap(); }
        void Update();
        void Draw();

        void GenerateMap();

        int GetStartRow() const { return startRow; }
        int GetStartCol() const { return startCol; }

        static const int mapWidth = 29;
        static const int mapHeight = 16;
        float centerX; // those are needed for drawing
        float centerY;
        int map[mapWidth][mapHeight];

        Char::PlayerChar* playerChar = nullptr;
        ItemTile itemTiles[mapWidth][mapHeight]; // stores all item tiles on the map

    private:
        int startRow, startCol;
        int endRow, endCol;

        int itemsOnMap, maxItemsOnMap;

        Sprite grassTile = Sprite(0, 0, "../../assets/graphics/grassTile.png");
        Sprite treeTile = Sprite(0, 0, "../../assets/graphics/treeTile.png");
        Sprite startTile = Sprite(0, 0, "../../assets/graphics/startTile.png");
        Sprite exitTile = Sprite(0, 0, "../../assets/graphics/exitTile.png");

        void ClearMap();
        void GenerateStartAndEnd();
        void GenerateItems();
        void RandomizeItem(int col, int row, int randomValue);
        void GenerateValidPath(int endRow, int endCol);

    };

}
