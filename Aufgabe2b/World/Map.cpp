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
        // set player positions for drawing and movement
        player = std::make_shared<Char::PlayerChar>(centerX + static_cast<float>(startCol * Config::TileSize),
                                                    centerY + static_cast<float>(startRow * Config::TileSize));
        player->SetArrayPosition(startCol, startRow);
    }

    /**** CORE-FUNCTIONS ****/
    //================================================================================================================//
    void Map::Update()
    {
        if (IsKeyPressed(KEY_G))
        {
            GenerateMap();
            // Resets player position
            player = std::make_shared<Char::PlayerChar>(centerX + static_cast<float>(startCol * Config::TileSize),
                                                        centerY + static_cast<float>(startRow * Config::TileSize));
            player->SetArrayPosition(startCol, startRow);
        }

        player->Update();

        if (CanMoveChar((int)player->GetArrayPos().x, (int)player->GetArrayPos().y))
        {
            player->Move(playerDirection);
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
                        DrawRectangleRec(tileRec, PURPLE);
                        break;
                }
            }
        }

        player->Draw();
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

    /* Returns true if player can move in desired direction, player->Move functions needs this information */
    bool Map::CanMoveChar(int posX, int posY)
    {
        if (IsKeyPressed(KEY_A))
        {
            if (map[posX - 1][posY] != TileState::BLOCKED && posX - 1 >= 0)
            {
                playerDirection = Char::Direction::LEFT;
                return true;
            }
        }
        else if (IsKeyPressed(KEY_D))
        {
            if (map[posX + 1][posY] != TileState::BLOCKED && posX + 1 < mapWidth)
            {
                playerDirection = Char::Direction::RIGHT;
                return true;
            }
        }
        else if (IsKeyPressed(KEY_W))
        {
            if (map[posX][posY - 1] != TileState::BLOCKED && posY - 1 >= 0)
            {
                playerDirection = Char::Direction::UP;
                return true;
            }
        }
        else if (IsKeyPressed(KEY_S))
        {
            if (map[posX][posY + 1] != TileState::BLOCKED && posY + 1 < mapHeight)
            {
                playerDirection = Char::Direction::DOWN;
                return true;
            }
        }
        return false;
    }

}