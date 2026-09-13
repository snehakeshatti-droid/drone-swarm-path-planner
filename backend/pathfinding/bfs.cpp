#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int ROWS = 10;
const int COLS = 10;

int getNodeId(int row, int col)
{
    return row * COLS + col;
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
    vector<int> parent(ROWS * COLS, -1);

    queue<int> q;

    q.push(start);
    visited[start] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (current == destination)
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

    // Reconstruct path
    vector<int> path;

    int current = destination;

    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    cout << "BFS Shortest Path:\n";

    for (int i = path.size() - 1; i >= 0; i--)
    {
        int row = path[i] / COLS;
        int col = path[i] % COLS;

        cout << "(" << row << "," << col << ")";

        if (i != 0)
            cout << " -> ";
    }

    cout << "\n";
    cout << "Distance = " << path.size() - 1 << " steps\n";

    return 0;
}