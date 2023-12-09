//
// Created by David on 29/11/2023.
//

#include "Sprite.h"

Sprite::Sprite(int posX, int posY, const char* filePath)
{
    this->posX = posX;
    this->posY = posY;
    this->texture = LoadTexture(filePath);
}
