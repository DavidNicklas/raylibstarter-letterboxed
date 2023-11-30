#include "Map.h"


namespace Game
{

    Map::Map()
    {
        startRow = 0;
        startCol = 0;
        endCol = 0;
        endRow = 0;
        itemsOnMap = 0;
        maxItemsOnMap = 6;
        centerX = Config::ScreenWidth / 2 - ((Config::TileSize * mapWidth) / 2);
        centerY = Config::ScreenHeight / 2 - ((Config::TileSize * mapHeight) / 2);
        GenerateMap();
    }

    /**** CORE-FUNCTIONS ****/
    //================================================================================================================//
    void Map::Draw()
    {
        for (int i = 0; i < mapWidth; ++i)
        {
            for (int j = 0; j < mapHeight; ++j)
            {
                Rectangle tileRec = {centerX + static_cast<float>(i * Config::TileSize),
                                     centerY + static_cast<float>(j * Config::TileSize),
                                     Config::TileSize,
                                     Config::TileSize};

                switch (map[i][j])
                {
                    case TileState::BLOCKED:
                        DrawRectangleRec(tileRec, DARKGRAY);
                        break;
                    case TileState::PASSABLE:
                        DrawRectangleRec(tileRec, LIGHTGRAY);
                        break;
                    case TileState::START:
                        DrawRectangleRec(tileRec, RED);
                        break;
                    case TileState::EXIT:
                        DrawRectangleRec(tileRec, GREEN);
                        break;
                    case TileState::ITEM:
                        DrawRectangleRec(tileRec, PURPLE);
                        break;
                }
            }
        }

        DrawRectangleLinesEx({centerX, centerY, Config::TileSize * mapWidth, Config::TileSize * mapHeight}, 2, DARKBROWN);
    }

    void Map::Update()
    {
        if (IsKeyPressed(KEY_G))
        {
            GenerateMap();
        }
    }
    //================================================================================================================//


    /**** MAP-GENERATION-FUNCTIONS ****/
    //================================================================================================================//
    /* Resets the map and initializes it with 0 */
    void Map::ClearMap()
    {
        itemsOnMap = 0;

        for (int i = 0; i < mapWidth; ++i)
        {
            for (int j = 0; j < mapHeight; ++j)
            {
                map[i][j] = TileState::NONE;
            }
        }
    }

    /* Generate a random map */
    void Map::GenerateMap()
    {
        ClearMap();

        GenerateStartAndEnd();

        // Fill map with random tiles
        for (int i = 0; i < mapWidth; ++i)
        {
            for (int j = 0; j < mapHeight; ++j)
            {
                if (map[i][j] != TileState::START && map[i][j] != TileState::EXIT)
                {
                    map[i][j] = GetRandomValue(TileState::PASSABLE, TileState::BLOCKED);
                }
            }
        }

        GenerateValidPath(endRow, endCol);

        GenerateItems();
    }

    void Map::GenerateStartAndEnd()
    {
        // Define start (only in last row)
        startRow = mapHeight - 1;
        startCol = GetRandomValue(0, mapWidth - 1);
        map[startCol][startRow] = TileState::START;

        // Define exit (only in first row)
        endRow = 0;
        endCol = GetRandomValue(0, mapWidth - 1);
        map[endCol][endRow] = TileState::EXIT;
    }

    void Map::GenerateItems()
    {
        while (itemsOnMap < maxItemsOnMap)
        {
            int col = GetRandomValue(0, mapWidth);
            int row = GetRandomValue(0, mapHeight);

            if (map[col][row] == TileState::PASSABLE)
            {
                map[col][row] = TileState::ITEM;
                itemsOnMap++;
            }
        }
    }

    /* Generate a valid path from start to end */
    void Map::GenerateValidPath(int endRow, int endCol)
    {
        // Looking for the right col
        int currentCol = endCol;
        while (currentCol != startCol)
        {
            if (currentCol < startCol)
            {
                currentCol++;
            }
            else
            {
                currentCol--;
            }
            map[currentCol][endRow] = TileState::PASSABLE;
        }

        // Looking for the right row
        int currentRow = endRow;
        while (currentRow != startRow)
        {
            if (currentRow < startRow)
            {
                currentRow++;
            }
            else
            {
                currentRow--;
            }
            map[startCol][currentRow] = TileState::PASSABLE;
        }

        // Reset start and exit value
        map[startCol][startRow] = TileState::START;
        map[endCol][endRow] = TileState::EXIT;
    }
    //================================================================================================================//

}