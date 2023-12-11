#pragma once

#include <string>
#include "raylib.h"

class Sprite
{
public:
    Sprite() = default;
    Sprite(int posX, int posY, const char* filePath);

    int posX;
    int posY;

    Texture2D GetTexture() { return this->texture; }
    void ChangeTexture(Texture2D newTexture) { this->texture = newTexture; }

private:
    Texture2D texture;

};