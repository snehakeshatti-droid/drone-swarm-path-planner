#include <iostream>
#include <vector>

using namespace std;

const int ROWS = 10;
const int COLS = 10;

int getNodeId(int row, int col)
{
    return row * COLS + col;
}

bool dfs(int current, int destination,
         vector<vector<int>>& grid,
         vector<bool>& visited,
         vector<int>& path)
{
    int row = current / COLS;
    int col = current % COLS;

    visited[current] = true;
    path.push_back(current);

    if (current == destination)
        return true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

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
                if (dfs(neighbour, destination,
                        grid, visited, path))
                {
                    return true;
                }
            }
        }
    }

    path.pop_back();
    return false;
}

int main()
{
    vector<vector<int>> grid(ROWS, vector<int>(COLS, 0));

    // Obstacles
    grid[2][4] = 1;
    grid[3][4] = 1;
    grid[4][4] = 1;

    grid[6][2] = 1;
    grid[6][3] = 1;
    grid[6][4] = 1;

    int start = getNodeId(0, 0);
    int destination = getNodeId(9, 9);

    vector<bool> visited(ROWS * COLS, false);
    vector<int> path;

    dfs(start, destination, grid, visited, path);

    cout << "DFS Path:\n";

    for (int i = 0; i < path.size(); i++)
    {
        int row = path[i] / COLS;
        int col = path[i] % COLS;

        cout << "(" << row << "," << col << ")";

        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\n";
    cout << "Path Length = " << path.size() - 1 << " steps\n";

    return 0;
}