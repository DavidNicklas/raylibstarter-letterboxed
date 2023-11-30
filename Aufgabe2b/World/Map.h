#pragma once

#include <memory>
#include "raylib.h"
#include "config.h"
#include "../GameObject.h"
#include "../Character/PlayerChar.h"
#include "../Sprite.h"

namespace Game
{

    enum TileState {NONE, BLOCKED, PASSABLE, START, EXIT, ITEM};

    class Map : public GameObject
    {
    public:
        Map();
        ~Map() { ClearMap(); }
        void Update() override;
        void Draw() override;

        void GenerateMap();

        static const int mapWidth = 29;
        static const int mapHeight = 16;
        float centerX; // those are needed for drawing
        float centerY;
        int map[mapWidth][mapHeight];

    private:
        std::shared_ptr<Char::PlayerChar> player;
        Char::Direction playerDirection;

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
        void GenerateValidPath(int endRow, int endCol);
        bool CanMoveChar(int posX, int posY);

    };

}