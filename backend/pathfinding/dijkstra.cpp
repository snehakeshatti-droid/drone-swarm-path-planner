#include <iostream>
#include <vector>
#include <queue>
#include <limits>

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

    int totalNodes = ROWS * COLS;

    int start = getNodeId(0, 0);
    int destination = getNodeId(9, 9);

    const int INF = numeric_limits<int>::max();

    vector<int> distance(totalNodes, INF);
    vector<int> parent(totalNodes, -1);

    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    distance[start] = 0;
    pq.push({0, start});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!pq.empty())
    {
        int currentDistance = pq.top().first;
        int current = pq.top().second;

        pq.pop();

        if (currentDistance != distance[current])
            continue;

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

                int newDistance = currentDistance + 1;

                if (newDistance < distance[neighbour])
                {
                    distance[neighbour] = newDistance;
                    parent[neighbour] = current;

                    pq.push({newDistance, neighbour});
                }
            }
        }
    }

    // Reconstruct shortest path
    vector<int> path;

    int current = destination;

    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    cout << "Dijkstra Shortest Path:\n";

    for (int i = path.size() - 1; i >= 0; i--)
    {
        int row = path[i] / COLS;
        int col = path[i] % COLS;

        cout << "(" << row << "," << col << ")";

        if (i != 0)
            cout << " -> ";
    }

    cout << "\n";
    cout << "Shortest Distance = "
         << distance[destination]
         << " steps\n";

    return 0;
}