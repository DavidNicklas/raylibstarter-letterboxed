#pragma once

struct Node
{
    Node(int col, int row, int gCost, int hCost)
    : col(col), row(row), gCost(gCost), hCost(hCost) {}

    int col;
    int row;
    int gCost;
    int hCost;

    int GetFCost() const { return this->gCost + this->hCost; }

    // Overload the comparison operator for the priority queue
    bool operator>(const Node& other) const { return GetFCost() > other.GetFCost(); }
};