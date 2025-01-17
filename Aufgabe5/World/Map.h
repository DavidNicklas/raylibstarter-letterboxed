#pragma once

#include <memory>
#include <vector>

#include "raylib.h"
#include "config.h"
#include "../Sprite.h"
#include "../Character/PlayerChar.h"
#include "../Character/NonPlayerChar.h"
#include "../Items/Coffee.h"
#include "../Items/Equipment/Hat.h"
#include "../Items/Equipment/Shoes.h"
#include "../Items/Equipment/Honey.h"
#include "../Items/Equipment/MysticalHoney.h"
#include "../Items/Steak.h"
#include "../Items/Fish.h"
#include "../Items/Stick.h"
#include "Tiles.h"
#include "Path.h"

namespace UI
{
    class InventoryUI;
}

namespace Game
{

    class Map
    {
    public:
        Map();
        ~Map() { ClearMap(); }
        void Update();
        void Draw();

        void GenerateMap();
        void ResetMap();

        int GetStartRow() const { return startRow; }
        int GetStartCol() const { return startCol; }
        int GetEndRow() const { return endRow; }
        int GetEndCol() const { return endCol; }

        static const int mapWidth = 30;
        static const int mapHeight = 17;
        int map[mapWidth][mapHeight];
        Path path;

        Char::PlayerChar* playerChar = nullptr;
        Char::NonPlayerChar* nonPlayerChar = nullptr;
        ItemTile itemTiles[mapWidth][mapHeight]; // stores all item tiles on the map

    private:
        int startRow, startCol;
        int endRow, endCol;

        int itemsOnMap, maxItemsOnMap;

        void ClearMap();
        void GenerateStartAndEnd();
        void GenerateItems();
        void RandomizeItem(int col, int row, int randomItemValue);
        std::pair<int, int> GetRandomItemSpawn();
        void GenerateValidPath(int endRow, int endCol);
        void GenerateShortestPath();
        void GenerateValidItemPath(int startRow, int startCol, int goalRow, int goalCol);
        bool IsTileInBounds(int row, int col);

        void FillInventoryForDemonstrationPurpose();

        Sprite sprite_grassTile = Sprite(0, 0, "../../assets/graphics/grassTile.png");
        Sprite sprite_treeTile = Sprite(0, 0, "../../assets/graphics/treeTile.png");
        Sprite sprite_startTile = Sprite(0, 0, "../../assets/graphics/startTile.png");
        Sprite sprite_exitTile = Sprite(0, 0, "../../assets/graphics/exitTile.png");

        Sprite sprite_coffee = Sprite(0, 0, "../../assets/graphics/coffee.png");
        Sprite sprite_steak = Sprite(0, 0, "../../assets/graphics/steak.png");
        Sprite sprite_hat = Sprite(0, 0, "../../assets/graphics/sleepingHat.png");
        Sprite sprite_honey = Sprite(0, 0, "../../assets/graphics/honey.png");
        Sprite sprite_shoes = Sprite(0, 0, "../../assets/graphics/boots.png");
        Sprite sprite_fish = Sprite(0, 0, "../../assets/graphics/fish.png");
        Sprite sprite_stick = Sprite(0, 0, "../../assets/graphics/stick.png");
        Sprite sprite_mysticalHoney = Sprite(0, 0, "../../assets/graphics/mysticalHoney.png");
    };

}
