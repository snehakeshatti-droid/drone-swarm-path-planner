#include <iostream>
#include <vector>

using namespace std;

struct Position
{
    int row;
    int col;
};

struct Drone
{
    int id;
    vector<Position> path;
};

int main()
{
    Drone drone1 =
    {
        1,
        {
            {0, 0},
            {0, 1},
            {0, 2},
            {1, 2},
            {2, 2},
            {3, 2},
            {4, 2}
        }
    };

    cout << "Drone Movement Simulation\n";
    cout << "=========================\n\n";

    for (int step = 0; step < drone1.path.size(); step++)
    {
        cout << "Step " << step + 1
             << ": Drone " << drone1.id
             << " -> ("
             << drone1.path[step].row
             << ", "
             << drone1.path[step].col
             << ")" << endl;
    }

    cout << "\nSimulation completed successfully.\n";

    return 0;
}