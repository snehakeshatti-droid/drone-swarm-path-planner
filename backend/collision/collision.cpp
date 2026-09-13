#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

string getPositionKey(int row, int col)
{
    return to_string(row) + "," + to_string(col);
}

int main()
{
    unordered_map<string, int> occupiedCells;

    // Drone 1 moves to (2,3)
    int drone1Row = 2;
    int drone1Col = 3;

    string position1 = getPositionKey(drone1Row, drone1Col);

    occupiedCells[position1] = 1;

    cout << "Drone 1 moved to (2,3)\n";

    // Drone 2 tries to move to (2,3)
    int drone2Row = 2;
    int drone2Col = 3;

    string position2 = getPositionKey(drone2Row, drone2Col);

    if (occupiedCells.find(position2) != occupiedCells.end())
    {
        cout << "Collision detected!\n";
        cout << "Drone 2 cannot move to (2,3)\n";
    }
    else
    {
        occupiedCells[position2] = 2;
        cout << "Drone 2 moved to (2,3)\n";
    }

    // Drone 2 tries another cell
    drone2Row = 2;
    drone2Col = 4;

    position2 = getPositionKey(drone2Row, drone2Col);

    if (occupiedCells.find(position2) != occupiedCells.end())
    {
        cout << "Collision detected!\n";
    }
    else
    {
        occupiedCells[position2] = 2;
        cout << "Drone 2 moved to (2,4)\n";
    }

    return 0;
}