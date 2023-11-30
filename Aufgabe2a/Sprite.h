#pragma once

#include <string>
#include "raylib.h"

class Sprite
{
public:
    Sprite(int posX, int posY, const char* filePath);
    ~Sprite() { UnloadTexture(this->texture); }

    int posX;
    int posY;

    Texture2D GetTexture() { return this->texture; }

private:
    Texture2D texture;

};