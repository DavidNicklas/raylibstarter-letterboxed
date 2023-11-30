#pragma once

#include "raylib.h"
#include "config.h"
#include "../GameObject.h"

namespace UI
{

    class Menu : public GameObject
    {
    public:
        void Update() override {};
        void Draw() override;

    private:
    };

}
