#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
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
    vector<Position> path;
};

string getKey(int row, int col)
{
    return to_string(row) + "," + to_string(col);
}

int main()
{
    // Sample paths from our swarm
    vector<Drone> drones =
    {
        {
            1,
            {
                {0,0}, {0,1}, {0,2},
                {1,2}, {1,3}, {1,4}
            }
        },
        {2,
    {
        {0,9}, {0,8}, {0,7},
        {1,7}, {1,6}, {1,4}
    }
},
        {
            3,
            {
                {9,0}, {8,0}, {7,0},
                {7,1}, {6,1}, {5,1}
            }
        }
    };

    // Stores which drone occupies each cell
    unordered_map<string, int> occupiedCells;

    cout << "===== DRONE SWARM COLLISION CHECK =====\n\n";

    int collisionCount = 0;

    // Simulate movement step by step
    int maxSteps = 0;

    for (const Drone& drone : drones)
    {
        if (drone.path.size() > maxSteps)
            maxSteps = drone.path.size();
    }

    for (int step = 0; step < maxSteps; step++)
    {
        cout << "Step " << step + 1 << ":\n";

        occupiedCells.clear();

        for (const Drone& drone : drones)
        {
            if (step >= drone.path.size())
                continue;

            int row = drone.path[step].row;
            int col = drone.path[step].col;

            string key = getKey(row, col);

           if (occupiedCells.find(key) != occupiedCells.end())
                {
                    cout << "  COLLISION! Drone "
                        << drone.id
                        << " tried to enter ("
                        << row << "," << col
                        << ")\n";

                    cout << "  Drone "
                        << drone.id
                        << " waits at previous position.\n";

                    collisionCount++;
                }
            else
            {
                occupiedCells[key] = drone.id;

                cout << "  Drone "
                     << drone.id
                     << " -> ("
                     << row << ","
                     << col << ")\n";
            }
        }

        cout << endl;
    }

    cout << "Total collisions detected: "
         << collisionCount << endl;

    return 0;
}