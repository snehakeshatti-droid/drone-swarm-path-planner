#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int ROWS = 10;
const int COLS = 10;

struct Position
{
    int row;
    int col;
};

struct Drone
{
    int id;
    Position start;
    Position target;
    vector<Position> path;
};

int getNodeId(int row, int col)
{
    return row * COLS + col;
}

vector<Position> bfs(vector<vector<int>>& grid,
                     Position start,
                     Position target)
{
    int totalNodes = ROWS * COLS;

    vector<bool> visited(totalNodes, false);
    vector<int> parent(totalNodes, -1);

    queue<int> q;

    int startNode = getNodeId(start.row, start.col);
    int targetNode = getNodeId(target.row, target.col);

    q.push(startNode);
    visited[startNode] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (current == targetNode)
            break;

        int row = current / COLS;
        int col = current % COLS;

        for (int k = 0; k < 4; k++)
        {
            int newRow = row + dr[k];
            int newCol = col + dc[k];

            if (newRow >= 0 && newRow < ROWS &&
                newCol >= 0 && newCol < COLS &&
                grid[newRow][newCol] == 0)
            {
                int neighbour = getNodeId(newRow, newCol);

                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    parent[neighbour] = current;
                    q.push(neighbour);
                }
            }
        }
    }

    vector<int> nodePath;

    int current = targetNode;

    while (current != -1)
    {
        nodePath.push_back(current);
        current = parent[current];
    }

    reverse(nodePath.begin(), nodePath.end());

    vector<Position> path;

    for (int node : nodePath)
    {
        Position p;

        p.row = node / COLS;
        p.col = node % COLS;

        path.push_back(p);
    }

    return path;
}

int main()
{
    vector<vector<int>> grid(
        ROWS, vector<int>(COLS, 0)
    );

    // Obstacles
    grid[2][4] = 1;
    grid[3][4] = 1;
    grid[4][4] = 1;

    grid[6][2] = 1;
    grid[6][3] = 1;
    grid[6][4] = 1;

    vector<Drone> drones =
    {
        {1, {0, 0}, {9, 9}, {}},
        {2, {0, 9}, {9, 0}, {}},
        {3, {9, 0}, {0, 9}, {}}
    };

    cout << "===== DRONE SWARM PATH PLANNER =====\n\n";

    for (Drone& drone : drones)
    {
        drone.path = bfs(
            grid,
            drone.start,
            drone.target
        );

        cout << "Drone " << drone.id << endl;

        cout << "Start: ("
             << drone.start.row << ","
             << drone.start.col << ")" << endl;

        cout << "Target: ("
             << drone.target.row << ","
             << drone.target.col << ")" << endl;

        cout << "Path: ";

        for (int i = 0; i < drone.path.size(); i++)
        {
            cout << "("
                 << drone.path[i].row
                 << ","
                 << drone.path[i].col
                 << ")";

            if (i != drone.path.size() - 1)
                cout << " -> ";
        }

        cout << endl;

        cout << "Distance: "
             << drone.path.size() - 1
             << " steps\n";

        cout << "-----------------------------\n";
    }

    return 0;
}