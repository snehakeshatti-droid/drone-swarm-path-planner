#include <iostream>
#include <vector>

using namespace std;

const int ROWS = 10;
const int COLS = 10;

void displayGrid(const vector<vector<int>>& grid)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << grid[i][j] << " ";
        }

        cout << endl;
    }
}

int main()
{
    vector<vector<int>> grid(ROWS, vector<int>(COLS, 0));

    // Add some obstacles
    grid[2][4] = 1;
    grid[3][4] = 1;
    grid[4][4] = 1;

    grid[6][2] = 1;
    grid[6][3] = 1;
    grid[6][4] = 1;

    cout << "Drone Swarm Grid" << endl;
    cout << "0 = Free Cell" << endl;
    cout << "1 = Obstacle" << endl;
    cout << endl;

    displayGrid(grid);

    return 0;
}