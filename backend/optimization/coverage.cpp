#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int ROWS = 10;
const int COLS = 10;

struct Position
{
    int row;
    int col;
};

int main()
{
    vector<Position> dronePath =
    {
        {0, 0},
        {0, 1},
        {0, 2},
        {1, 2},
        {2, 2},
        {3, 2},
        {4, 2},
        {5, 2},
        {5, 3},
        {5, 4}
    };

    set<pair<int, int>> coveredCells;

    for (const Position& position : dronePath)
    {
        coveredCells.insert(
            {position.row, position.col}
        );
    }

    int totalCells = ROWS * COLS;
    int covered = coveredCells.size();

    double coveragePercentage =
        (covered * 100.0) / totalCells;

    cout << "Drone Coverage Analysis\n";
    cout << "========================\n\n";

    cout << "Total Grid Cells: "
         << totalCells << endl;

    cout << "Covered Cells: "
         << covered << endl;

    cout << "Coverage Percentage: "
         << coveragePercentage
         << "%\n";

    return 0;
}