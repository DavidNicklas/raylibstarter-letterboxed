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

        Sprite sprite_grassTile = Sprite(0, 0, "../../assets/graphics/grassTile.png");
        Sprite sprite_treeTile = Sprite(0, 0, "../../assets/graphics/treeTile.png");
        Sprite sprite_startTile = Sprite(0, 0, "../../assets/graphics/startTile.png");
        Sprite sprite_exitTile = Sprite(0, 0, "../../assets/graphics/exitTile.png");

        Sprite sprite_coffee = Sprite(0, 0, "../../assets/graphics/coffee.png");
        Sprite sprite_steak = Sprite(0, 0, "../../assets/graphics/steak.png");
        Sprite sprite_hat = Sprite(0, 0, "../../assets/graphics/sleepingHat.png");
        Sprite sprite_honey = Sprite(0, 0, "../../assets/graphics/honey.png");
        Sprite sprite_shoes = Sprite(0, 0, "../../assets/graphics/boots.png");

        void ClearMap();
        void GenerateStartAndEnd();
        void GenerateItems();
        void RandomizeItem(int col, int row, int randomValue);
        void GenerateValidPath(int endRow, int endCol);

    };

}
