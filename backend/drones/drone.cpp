#include <iostream>
#include <vector>

using namespace std;

struct Drone
{
    int id;
    int startRow;
    int startCol;
    int targetRow;
    int targetCol;
};

int main()
{
    vector<Drone> drones =
    {
        {1, 0, 0, 9, 9},
        {2, 0, 9, 9, 0},
        {3, 9, 0, 0, 9}
    };

    cout << "Drone Swarm\n";
    cout << "============\n\n";

    for (const Drone& drone : drones)
    {
        cout << "Drone " << drone.id << endl;

        cout << "Start: ("
             << drone.startRow << ","
             << drone.startCol << ")" << endl;

        cout << "Target: ("
             << drone.targetRow << ","
             << drone.targetCol << ")" << endl;

        cout << "Status: Ready" << endl;

        cout << "------------------\n";
    }

    return 0;
}