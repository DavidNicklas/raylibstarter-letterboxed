#pragma once

struct Node
{
    Node(int col, int row, int gCost, int hCost, Node* parent)
    : col(col), row(row), gCost(gCost), hCost(hCost), parent(parent) {}

    int col;
    int row;
    int gCost;
    int hCost;
    int GetFCost() const { return this->gCost + this->hCost; }

    Node* parent; // stores the node the path came from
};