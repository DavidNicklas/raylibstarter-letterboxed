#include "PlayerChar.h"
#include "config.h"


namespace Char
{

    PlayerChar::PlayerChar(int posX, int posY)
    {
        this->playerSprite.ChangeTexture("../../assets/graphics/bear.png");
        this->SetPosition(posX, posY);
    }

    void PlayerChar::Update()
    {
        if (IsKeyPressed(KEY_E))
        {
            if (!inInventory) inInventory = true;
            else inInventory = false;
        }
    }

    void PlayerChar::Draw()
    {
        DrawTexture(playerSprite.GetTexture(), playerSprite.posX, playerSprite.posY, WHITE);
    }

    void PlayerChar::Move(Direction dir)
    {
        if (!inInventory)
        {
            switch (dir)
            {
                case Direction::LEFT:
                    playerSprite.posX -= Config::TileSize;
                    arrayPosX--;
                    break;
                case Direction::RIGHT:
                    playerSprite.posX += Config::TileSize;
                    arrayPosX++;
                    break;
                case Direction::UP:
                    playerSprite.posY -= Config::TileSize;
                    arrayPosY--;
                    break;
                case Direction::DOWN:
                    playerSprite.posY += Config::TileSize;
                    arrayPosY++;
                    break;
            }
        }
    }

    int PlayerChar::CalculateTotalWeight()
    {
        // going through normal inventory
        for (int i = 0; i < inventory.GetCapacity(); ++i)
        {
            this->totalWeight += (int)inventory.itemContainer[i]->GetWeight();
        }
        //going through equipment slots
        for (int i = 0; i < inventory.GetEquipmentSlots(); ++i)
        {
            if (inventory.equipmentContainer[i] != nullptr) this->totalWeight += (int)inventory.equipmentContainer[i]->GetWeight();
        }

        return totalWeight;
    }
}
