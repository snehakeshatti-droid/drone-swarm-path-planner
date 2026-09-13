#include <iostream>
#include <vector>

using namespace std;

const int ROWS = 10;
const int COLS = 10;

int getNodeId(int row, int col)
{
    return row * COLS + col;
}

bool isValid(int row, int col)
{
    return row >= 0 && row < ROWS &&
           col >= 0 && col < COLS;
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

    // Directions: Up, Down, Left, Right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    cout << "Graph Nodes and Their Neighbours\n\n";

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (grid[row][col] == 0)
            {
                int node = getNodeId(row, col);

                cout << "Node " << node << " -> ";

                for (int k = 0; k < 4; k++)
                {
                    int newRow = row + dr[k];
                    int newCol = col + dc[k];

                    if (isValid(newRow, newCol) &&
                        grid[newRow][newCol] == 0)
                    {
                        cout << getNodeId(newRow, newCol) << " ";
                    }
                }

                cout << endl;
            }
        }
    }

    return 0;
}