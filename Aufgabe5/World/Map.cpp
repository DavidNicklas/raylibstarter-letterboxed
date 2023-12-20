#include <algorithm>
#include "Map.h"
#include "../Helper.h"

namespace Game
{

    Map::Map()
    {
        startRow = 0;
        startCol = 0;
        endCol = 0;
        endRow = 0;
        itemsOnMap = 0;
        maxItemsOnMap = 15;
        GenerateMap();
    }

    /**** CORE-FUNCTIONS ****/
    //================================================================================================================//
    void Map::Update()
    {
        if (IsKeyPressed(KEY_G) && !playerChar->GetInventoryUI()->ShowInventory())
        {
            ResetMap();
        }

        if (IsKeyPressed(KEY_L)) FillInventoryForDemonstrationPurpose();

        if (IsKeyPressed(KEY_H)) path.showPath = !path.showPath;
    }

    void Map::Draw()
    {
        for (int i = 0; i < mapWidth; ++i)
        {
            for (int j = 0; j < mapHeight; ++j)
            {
                Rectangle tileRec = {static_cast<float>(i * Config::TileSize),
                                     static_cast<float>(j * Config::TileSize),
                                     Config::TileSize,
                                     Config::TileSize};

                switch (map[i][j])
                {
                    case TileState::BLOCKED:
                        DrawTexture(sprite_treeTile.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        break;
                    case TileState::PASSABLE:
                        DrawTexture(sprite_grassTile.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        break;
                    case TileState::START:
                        DrawTexture(sprite_startTile.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        break;
                    case TileState::EXIT:
                        DrawTexture(sprite_exitTile.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        break;
                    case TileState::ITEM:
                        DrawTexture(sprite_grassTile.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        if (itemTiles[i][j].item != nullptr) DrawTexture(itemTiles[i][j].item->texture.GetTexture(), (int)tileRec.x, (int)tileRec.y, WHITE);
                        break;
                }
            }
        }

        if (path.showPath) path.DrawPathLines();
    }
    //================================================================================================================//


    /**** MAP-GENERATION-FUNCTIONS ****/
    //================================================================================================================//
    void Map::ResetMap()
    {
        GenerateMap();
        // Resets player stats
        playerChar->ResetPlayerStats();
        playerChar->inventory.ResetInventory();
        // Reset NPC
        nonPlayerChar->ResetPlayerStats();
        nonPlayerChar->inventory.ResetInventory();
        // Reset path
        path.showPath = false;
    }

    /* Resets the map and initializes it with 0 */
    void Map::ClearMap()
    {
        itemsOnMap = 0;

        for (int i = 0; i < mapWidth; ++i)
        {
            for (int j = 0; j < mapHeight; ++j)
            {
                map[i][j] = TileState::NONE;
                itemTiles[i][j].item = nullptr;
            }
        }
    }

    /* Generate a random map */
    void Map::GenerateMap()
    {
        ClearMap();

        GenerateStartAndEnd();

        GenerateValidPath(endRow, endCol);

        GenerateItems();

        // Fill the rest of the map with random tiles
        for (int i = 0; i < mapWidth; ++i)
        {
            for (int j = 0; j < mapHeight; ++j)
            {
                if (map[i][j] == TileState::NONE)
                {
                    map[i][j] = GetRandomValue(TileState::PASSABLE, TileState::BLOCKED);
                }
            }
        }

        GenerateShortestPath();
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
        // The following block spawns every item one single time
        std::vector<int> itemIndex = {0, 1, 2, 3, 4, 5, 6, 7};
        for (int i = 0; i < itemIndex.size(); ++i)
        {
            std::pair<int, int> spawnPoint = GetRandomItemSpawn();

            map[spawnPoint.first][spawnPoint.second] = TileState::ITEM;
            RandomizeItem(spawnPoint.first, spawnPoint.second, itemIndex[i]);
            itemsOnMap++;
        }

        // The following block spawns random non equippable items till maxItemsOnMap is reached
        while (itemsOnMap < maxItemsOnMap)
        {
            std::pair<int, int> spawnPoint = GetRandomItemSpawn();

            map[spawnPoint.first][spawnPoint.second] = TileState::ITEM;
            RandomizeItem(spawnPoint.first, spawnPoint.second, GetRandomValue(0, 3));
            itemsOnMap++;
        }
    }

    std::pair<int, int> Map::GetRandomItemSpawn()
    {
        std::pair<int, int> spawnPoint;
        do
        {
            spawnPoint.first = GetRandomValue(0, mapWidth);
            spawnPoint.second = GetRandomValue(0, mapHeight);
        } while (map[spawnPoint.first][spawnPoint.second] != TileState::PASSABLE || itemTiles[spawnPoint.first][spawnPoint.second].item != nullptr);

        return spawnPoint;
    }

    /* Creates a random item on the current ITEM tile and puts it in the container for all item tiles */
    void Map::RandomizeItem(int col, int row, int randomItemValue)
    {
        itemTiles[col][row].x = col;
        itemTiles[col][row].y = row;
        switch (randomItemValue)
        {
            case 0: itemTiles[col][row].item = std::make_shared<Items::Coffee>(sprite_coffee.GetTexture()); break;
            case 1: itemTiles[col][row].item = std::make_shared<Items::Steak>(sprite_steak.GetTexture()); break;
            case 2: itemTiles[col][row].item = std::make_shared<Items::Fish>(sprite_fish.GetTexture()); break;
            case 3: itemTiles[col][row].item = std::make_shared<Items::Stick>(sprite_stick.GetTexture()); break;
            case 4: itemTiles[col][row].item = std::make_shared<Items::Hat>(sprite_hat.GetTexture()); break;
            case 5: itemTiles[col][row].item = std::make_shared<Items::Honey>(sprite_honey.GetTexture()); break;
            case 6: itemTiles[col][row].item = std::make_shared<Items::Shoes>(sprite_shoes.GetTexture()); break;
            case 7: itemTiles[col][row].item = std::make_shared<Items::MysticalHoney>(sprite_mysticalHoney.GetTexture()); break;
        }
    }

    /* Generate a valid path from start to end */
    void Map::GenerateValidPath(int _endRow, int _endCol)
    {
        int currentCol = _endCol;
        int currentRow = _endRow;

        while (currentRow != startRow || currentCol != startCol)
        {
            if (GetRandomValue(0, 1) == 0)
            {
                // Move vertically
                if (currentRow < startRow)
                {
                    if (IsTileInBounds(currentRow + 1, currentCol)) currentRow++;
                }
                else
                {
                    if (IsTileInBounds(currentRow - 1, currentCol)) currentRow--;
                }
            }
            else
            {
                // Move horizontally
                if (currentCol < startCol)
                {
                    if (IsTileInBounds(currentRow, currentCol + 1)) currentCol++;
                }
                else
                {
                    if (IsTileInBounds(currentRow, currentCol - 1)) currentCol--;
                }
            }

            if (IsTileInBounds(currentRow, currentCol)) map[currentCol][currentRow] = TileState::PASSABLE;
        }

        // Reset start and exit so it doesn't get overwritten
        map[_endCol][_endRow] = TileState::EXIT;
        map[startCol][startRow] = TileState::START;
    }

        void Map::GenerateShortestPath()
    {
        std::vector<std::vector<int>> mapVector = ConvertToVector(this->map);
        path.CreateShortestPath(mapVector, {startCol, startRow}, {endCol, endRow});
    }

    bool Map::IsTileInBounds(int row, int col)
    {
        return row >= 0 && row < mapHeight && col >= 0 && col < mapWidth;
    }
    //================================================================================================================//

    void Map::FillInventoryForDemonstrationPurpose()
    {
        std::vector<int> itemIndex = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int i = 0; i < playerChar->inventory.GetCapacity(); ++i)
        {
            std::shared_ptr<Items::BaseItem> testItem = nullptr;
            switch (itemIndex[i])
            {
                case 0: testItem = std::make_shared<Items::Coffee>(sprite_coffee.GetTexture()); break;
                case 1: testItem = std::make_shared<Items::Hat>(sprite_hat.GetTexture()); break;
                case 2: testItem = std::make_shared<Items::Shoes>(sprite_shoes.GetTexture()); break;
                case 3: testItem = std::make_shared<Items::Honey>(sprite_honey.GetTexture()); break;
                case 4: testItem = std::make_shared<Items::Steak>(sprite_steak.GetTexture()); break;
                case 5: testItem = std::make_shared<Items::Fish>(sprite_fish.GetTexture()); break;
                case 6: testItem = std::make_shared<Items::Stick>(sprite_stick.GetTexture()); break;
                case 7: testItem = std::make_shared<Items::MysticalHoney>(sprite_mysticalHoney.GetTexture()); break;
                case 8: testItem = std::make_shared<Items::MysticalHoney>(sprite_mysticalHoney.GetTexture()); break;
                case 9: testItem = std::make_shared<Items::Steak>(sprite_steak.GetTexture()); break;
            }

            try
            {
                playerChar->inventory.AddItem(testItem);
            }
            catch (Error::InventoryFull& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

}