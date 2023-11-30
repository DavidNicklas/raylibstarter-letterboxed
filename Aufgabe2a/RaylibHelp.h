#pragma once

#include <algorithm>
#include "raylib.h"
#include "config.h"

void CheckFullscreen()
{
    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
    {
        if (IsWindowFullscreen())
        {
            ToggleFullscreen();
            SetWindowSize(Config::ScreenWidth,Config::ScreenHeight);
        } else
        {
            SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
            ToggleFullscreen();
        }
    }
}

/* The following lines put the canvas in the middle of the window and have the negative as black */
void Letterbox(float renderScale, RenderTexture2D& canvas, Rectangle& renderRec)
{
    ClearBackground(BLACK);
    renderScale = std::min(GetScreenHeight() / (float) canvas.texture.height, GetScreenWidth() / (float) canvas.texture.width);
    renderRec.width = canvas.texture.width * renderScale;
    renderRec.height = canvas.texture.height * renderScale;
    renderRec.x = (GetScreenWidth() - renderRec.width) / 2.0f;
    renderRec.y = (GetScreenHeight() - renderRec.height) / 2.0f;
    DrawTexturePro(canvas.texture, Rectangle{0, 0, (float) canvas.texture.width, (float) -canvas.texture.height}, renderRec, {}, 0, WHITE);
}