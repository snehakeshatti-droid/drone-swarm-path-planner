#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

struct Position
{
    int row;
    int col;
};

string getKey(Position p)
{
    return to_string(p.row) + "," + to_string(p.col);
}

bool isOccupied(const unordered_map<string, int>& occupied,
                Position position)
{
    return occupied.find(getKey(position)) != occupied.end();
}

int main()
{
    Position drone1 = {2, 2};
    Position drone2 = {2, 3};

    unordered_map<string, int> occupied;

    occupied[getKey(drone1)] = 1;

    cout << "Drone 1 moved to (2,3)" << endl;

    Position drone1Next = {2, 3};

    if (isOccupied(occupied, drone1Next))
    {
        cout << "Collision detected!" << endl;
    }

    occupied[getKey(drone1Next)] = 1;

    Position drone2Next = {2, 3};

    if (isOccupied(occupied, drone2Next))
    {
        cout << "Drone 2 cannot move to (2,3)" << endl;

        drone2Next = {2, 4};
    }

    occupied[getKey(drone2Next)] = 2;

    cout << "Drone 2 moved to ("
         << drone2Next.row << ","
         << drone2Next.col << ")" << endl;

    return 0;
}