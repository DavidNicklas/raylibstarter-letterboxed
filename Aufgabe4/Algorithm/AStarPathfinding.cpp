#include <algorithm>
#include <queue>
#include <cmath>

#include "AStarPathfinding.h"
#include "../Enums.h"


//////////////////////////////////|################################################|////////////////////////////////////
//                                | The base of this code is generated by ChatGPT. |                                  //
//                                | It is modified to fit my own purposes.         |                                  //
//////////////////////////////////|################################################|////////////////////////////////////

using namespace std;

namespace Algorithm
{

    // A* algorithm function
    vector<pair<int, int>> AStar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal)
    {
        // Define possible movement directions (4 directions: up, down, left, right)
        const vector<pair<int, int>> directions =
                {
                        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
                        // These are for diagonal movement
                        //, {-1, 1}, {1, 1}, {1, -1}, {1, 1}
                };

        // Priority queue to store nodes with the minimum total cost (f)
        priority_queue<Node, vector<Node>, greater<Node>> openSet;

        // Closed set to store nodes that have already been visited
        vector<vector<bool>> closedSet(grid.size(), vector<bool>(grid[0].size(), false));

        // Initialize the grid with Node objects
        vector<vector<Node>> nodeGrid(grid.size(), vector<Node>(grid[0].size(), Node(0, 0, 0, 0)));

        // Initialize the start node
        Node startNode(start.first, start.second, 0, CalculateHeuristic(start.first, start.second, goal.first, goal.second));

        // Push the start node into the priority queue
        openSet.push(startNode);

        // Main A* loop
        while (!openSet.empty())
        {
            // Get the node with the minimum total cost (f)
            Node current = openSet.top();
            openSet.pop();

            // Check if the current node is the goal
            if (current.col == goal.first && current.row == goal.second)
            {
                // Reconstruct the path from the goal to the start
                vector<pair<int, int>> path;
                while (!(current.col == start.first && current.row == start.second))
                {
                    path.emplace_back(current.col, current.row);
                    current = nodeGrid[current.col][current.row];
                }
                path.emplace_back(start.first, start.second);

                // Reverse the path to start from the start
                reverse(path.begin(), path.end());

                return path;
            }

            // Mark the current node as visited
            closedSet[current.col][current.row] = true;

            // Explore neighbors
            for (const auto& dir : directions)
            {
                int newX = current.col + dir.first;
                int newY = current.row + dir.second;

                // Check if the new position is within the grid bounds
                if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size())
                {
                    // Check if the neighbor is not an obstacle and has not been visited
                    if (grid[newX][newY] != Game::TileState::BLOCKED && !closedSet[newX][newY])
                    {
                        // Calculate the cost to reach the neighbor from the start
                        int newG = current.gCost + 1;

                        // Check if the neighbor has not been visited or the new path is better
                        if (!closedSet[newX][newY] || newG < nodeGrid[newX][newY].gCost)
                        {
                            // Calculate the Euclidean heuristic (estimated cost to reach the goal from the neighbor)
                            int newH = CalculateHeuristic(newX, newY, goal.first, goal.second);

                            // Create a new node for the neighbor
                            Node neighbor(newX, newY, newG, newH);

                            // Push the neighbor into the priority queue
                            openSet.push(neighbor);

                            // Update the closed set with the current node as the parent of the neighbor
                            nodeGrid[newX][newY] = current;
                        }
                    }
                }
            }
        }

        // If the goal is not reachable, return an empty path
        return {};
    }

/* // TODO Test A* function
    vector<pair<int, int>> AStarTest(int grid[][17], pair<int, int> start, pair<int, int> goal)
    {
        // Define possible movement directions (4 directions: up, down, left, right)
        const vector<pair<int, int>> directions =
                {
                        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
                        // These are for diagonal movement
                        //, {-1, 1}, {1, 1}, {1, -1}, {1, 1}
                };

        // Closed set to store nodes that have already been visited
        std::vector<Node> openNodes;
        std::vector<Node> closedNodes;

        Node startNode = Node(start.first, start.second, 0, CalculateHeuristic(start.first, start.second, goal.first, goal.second));
        openNodes.push_back(startNode);

        // Main A* loop
        while (!openNodes.empty())
        {
            // Get the node with the minimum total cost (f)
            Node current = openNodes[0];
            for (auto node : openNodes)
            {
                if (CompareFCost(node, current, goal))
                    current = node;
            }

            closedNodes.push_back(current);
            openNodes.erase(std::remove_if(openNodes.begin(), openNodes.end(),
                                           [current](const Node& node) { return &node == &current; }), openNodes.end());


            // Check if the current node is the goal
            if (current.col == goal.first && current.row == goal.second)
            {
                // Reconstruct the path from the goal to the start
                vector<pair<int, int>> path;
                while (!(current.col == start.first && current.row == start.second))
                {
                    path.emplace_back(current.col, current.row);
                    //current = nodeGrid[current.col][current.row];
                }
                path.emplace_back(start.first, start.second);

                // Reverse the path to start from the start
                reverse(path.begin(), path.end());

                return path;
            }

            // Mark the current node as visited
            closedNodes.push_back(current);

            CreateNeighbours(current);

            // Explore neighbors
            for (const auto& dir : directions)
            {
                int newX = current.col + dir.first;
                int newY = current.row + dir.second;

                // Check if the new position is within the grid bounds
                if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size())
                {
                    // Check if the neighbor is not an obstacle and has not been visited
                    if (grid[newX][newY] != Game::TileState::BLOCKED && !closedSet[newX][newY])
                    {
                        // Calculate the cost to reach the neighbor from the start
                        int newG = current.gCost + 1;

                        // Check if the neighbor has not been visited or the new path is better
                        if (!closedSet[newX][newY] || newG < nodeGrid[newX][newY].gCost)
                        {
                            // Calculate the Euclidean heuristic (estimated cost to reach the goal from the neighbor)
                            int newH = CalculateHeuristic(newX, newY, goal.first, goal.second);

                            // Create a new node for the neighbor
                            Node neighbor(newX, newY, newG, newH);

                            // Push the neighbor into the priority queue
                            openSet.push(neighbor);

                            // Update the closed set with the current node as the parent of the neighbor
                            nodeGrid[newX][newY] = current;
                        }
                    }
                }
            }
        }

        // If the goal is not reachable, return an empty path
        return {};
    }


    bool CompareFCost(Node node1, Node node2, pair<int, int> goal)
    {
        return
        node1.GetFCost() < node2.GetFCost() ||
        node1.GetFCost() == node2.GetFCost() &&
        CalculateHeuristic(node1.col, node1.row, goal.first, goal.second) < CalculateHeuristic(node2.col, node2.row, goal.first, goal.second);
    }
*/

    int CalculateHeuristic(int col, int row, int endCol, int endRow)
    {
        return static_cast<int>(sqrt(pow(col - endCol, 2) + pow(row - endRow, 2)));
    }

}