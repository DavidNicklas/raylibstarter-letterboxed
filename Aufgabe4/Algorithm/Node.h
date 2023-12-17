#pragma once

#include <vector>

struct Node
{
    Node(int col, int row, int gCost, int hCost)
    : col(col), row(row), gCost(gCost), hCost(hCost), parent(nullptr) {}

    int col;
    int row;
    int gCost;
    int hCost;

    int GetFCost() const { return this->gCost + this->hCost; }

    // Overload the comparison operator for the priority queue
    bool operator>(const Node& other) const { return GetFCost() > other.GetFCost(); }

    // TODO For test A* function
    std::vector<Node> neighbours;
    Node* parent;
};