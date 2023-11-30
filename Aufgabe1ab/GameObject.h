#pragma once

class GameObject
{
public:
    GameObject() = default;
    ~GameObject() = default;

    virtual void Update() = 0;
    virtual void Draw() = 0;
};