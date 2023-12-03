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
        maxItemsOnMap = 8;
        centerX = Config::ScreenWidth / 2 - ((Config::TileSize * mapWidth) / 2);
        centerY = Config::ScreenHeight / 2 - ((Config::TileSize * mapHeight) / 2);
        GenerateMap();
    }

    /**** CORE-FUNCTIONS ****/
    //================================================================================================================//
    void Map::Update()
    {
        if (IsKeyPressed(KEY_G))
        {
            GenerateMap();
            // Resets player position
            playerChar->SetStartPosition();
        }
    }

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
                        DrawTexture(treeTile.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        break;
                    case TileState::PASSABLE:
                        DrawTexture(grassTile.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        break;
                    case TileState::START:
                        DrawTexture(startTile.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        break;
                    case TileState::EXIT:
                        DrawTexture(exitTile.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        break;
                    case TileState::ITEM:
                        DrawTexture(grassTile.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        if (itemTiles[i][j].item != nullptr) DrawTexture(itemTiles[i][j].item->texture.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        break;
                }
            }
        }

        DrawRectangleLinesEx({centerX, centerY, Config::TileSize * mapWidth, Config::TileSize * mapHeight}, 2, DARKBROWN);
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
                int randomItem = GetRandomValue(0, 4);
                RandomizeItem(col, row, randomItem);
                itemsOnMap++;
            }
        }
    }

    /* Creates a random item on the current ITEM tile and puts it in the container for all item tiles */
    void Map::RandomizeItem(int col, int row, int randomValue)
    {
        itemTiles[col][row].x = col;
        itemTiles[col][row].y = row;
        switch (randomValue)
        {
            case 0: itemTiles[col][row].item = std::make_shared<Items::Coffee>(); break;
            case 1: itemTiles[col][row].item = std::make_shared<Items::Hat>(); break;
            case 2: itemTiles[col][row].item = std::make_shared<Items::Shoes>(); break;
            case 3: itemTiles[col][row].item = std::make_shared<Items::Honey>(); break;
            case 4: itemTiles[col][row].item = std::make_shared<Items::Steak>(); break;
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