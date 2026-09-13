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
    Position start;
    Position target;
    vector<Position> path;
};


// =====================================================
// HELPER FUNCTIONS
// =====================================================

int getNodeId(int row, int col)
{
    return row * COLS + col;
}

string getKey(int row, int col)
{
    return to_string(row) + "," + to_string(col);
}

bool samePosition(Position a, Position b)
{
    return a.row == b.row && a.col == b.col;
}


// =====================================================
// BFS
// =====================================================

vector<Position> bfs(
    vector<vector<int>>& grid,
    Position start,
    Position target)
{
    int totalNodes = ROWS * COLS;

    vector<bool> visited(totalNodes, false);
    vector<int> parent(totalNodes, -1);

    queue<int> q;

    int startNode = getNodeId(start.row, start.col);
    int targetNode = getNodeId(target.row, target.col);

    q.push(startNode);
    visited[startNode] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (current == targetNode)
            break;

        int row = current / COLS;
        int col = current % COLS;

        for (int k = 0; k < 4; k++)
        {
            int newRow = row + dr[k];
            int newCol = col + dc[k];

            if (newRow >= 0 &&
                newRow < ROWS &&
                newCol >= 0 &&
                newCol < COLS &&
                grid[newRow][newCol] == 0)
            {
                int neighbour =
                    getNodeId(newRow, newCol);

                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    parent[neighbour] = current;
                    q.push(neighbour);
                }
            }
        }
    }

    // No path found
    if (!visited[targetNode])
    {
        return vector<Position>();
    }

    vector<int> nodePath;

    int current = targetNode;

    while (current != -1)
    {
        nodePath.push_back(current);
        current = parent[current];
    }

    reverse(
        nodePath.begin(),
        nodePath.end()
    );

    vector<Position> path;

    for (int node : nodePath)
    {
        Position p;

        p.row = node / COLS;
        p.col = node % COLS;

        path.push_back(p);
    }

    return path;
}


// =====================================================
// BFS WITH TEMPORARY DRONE OBSTACLES
// =====================================================

vector<Position> rerouteBFS(
    vector<vector<int>>& grid,
    Position start,
    Position target,
    vector<Position>& blocked)
{
    vector<vector<int>> tempGrid = grid;

    // Temporarily block other drones
    for (const Position& p : blocked)
    {
        if (!samePosition(p, start) &&
            !samePosition(p, target))
        {
            tempGrid[p.row][p.col] = 1;
        }
    }

    return bfs(
        tempGrid,
        start,
        target
    );
}


// =====================================================
// CHECK IF POSITION IS VALID
// =====================================================

bool validPosition(Position p)
{
    return (
        p.row >= 0 &&
        p.row < ROWS &&
        p.col >= 0 &&
        p.col < COLS
    );
}


// =====================================================
// MAIN
// =====================================================

int main()
{
    // =================================================
    // CREATE GRID
    // =================================================

    vector<vector<int>> grid(
        ROWS,
        vector<int>(COLS, 0)
    );


    // =================================================
    // OBSTACLES
    // =================================================

    grid[2][4] = 1;
    grid[3][4] = 1;
    grid[4][4] = 1;

    grid[6][2] = 1;
    grid[6][3] = 1;
    grid[6][4] = 1;


    // =================================================
    // CREATE DRONES
    // =================================================

    vector<Drone> drones =
    {
        {1, {0, 0}, {9, 9}, {}},
        {2, {0, 9}, {9, 0}, {}},
        {3, {9, 0}, {0, 9}, {}}
    };


    // =================================================
    // GENERATE INITIAL BFS PATH
    // =================================================

    for (Drone& drone : drones)
    {
        drone.path =
            bfs(
                grid,
                drone.start,
                drone.target
            );

        if (drone.path.empty())
        {
            cout
                << "No path found for Drone "
                << drone.id
                << endl;

            return 0;
        }
    }


    cout
        << "===== INTEGRATED DRONE SWARM =====\n\n";


    // =================================================
    // CURRENT POSITIONS
    // =================================================

    vector<Position> currentPositions;

    for (const Drone& drone : drones)
    {
        currentPositions.push_back(
            drone.start
        );
    }


    // Position inside each drone's path
    vector<int> pathIndex(
        drones.size(),
        0
    );


    int collisionCount = 0;

    int step = 0;

    const int MAX_STEPS = 100;


    // =================================================
    // SIMULATION
    // =================================================

    while (step < MAX_STEPS)
    {
        step++;

        cout
            << "Step "
            << step
            << ":\n";


        // -------------------------------------------------
        // CHECK IF ALL DRONES HAVE REACHED THEIR TARGET
        // -------------------------------------------------

        bool allReached = true;

        for (int i = 0;
             i < drones.size();
             i++)
        {
            if (!samePosition(
                    currentPositions[i],
                    drones[i].target))
            {
                allReached = false;
                break;
            }
        }

        if (allReached)
        {
            break;
        }


        // =================================================
        // FIRST CREATE DESIRED NEXT POSITIONS
        // =================================================

        vector<Position> nextPositions =
            currentPositions;


        for (int i = 0;
             i < drones.size();
             i++)
        {
            if (pathIndex[i] + 1 <
                drones[i].path.size())
            {
                nextPositions[i] =
                    drones[i].path[
                        pathIndex[i] + 1
                    ];
            }
        }


        // =================================================
        // CHECK SWAP COLLISIONS
        // =================================================

        for (int i = 0;
             i < drones.size();
             i++)
        {
            for (int j = i + 1;
                 j < drones.size();
                 j++)
            {

                bool swapCollision =
                    samePosition(
                        nextPositions[i],
                        currentPositions[j]
                    )
                    &&
                    samePosition(
                        nextPositions[j],
                        currentPositions[i]
                    );


                if (swapCollision)
                {
                    cout
                        << "  SWAP COLLISION: Drone "
                        << drones[i].id
                        << " and Drone "
                        << drones[j].id
                        << "\n";


                    collisionCount++;


                    // =====================================
                    // TRY TO REROUTE DRONE WITH LOWER ID
                    // =====================================

                    vector<Position> blocked;

                    for (int k = 0;
                         k < drones.size();
                         k++)
                    {
                        if (k != i)
                        {
                            blocked.push_back(
                                currentPositions[k]
                            );

                            blocked.push_back(
                                nextPositions[k]
                            );
                        }
                    }


                    vector<Position> newPath =
                        rerouteBFS(
                            grid,
                            currentPositions[i],
                            drones[i].target,
                            blocked
                        );


                    bool rerouteSuccessful =
                        newPath.size() > 1;


                    if (rerouteSuccessful)
                    {
                        drones[i].path =
                            newPath;

                        pathIndex[i] = 0;

                        nextPositions[i] =
                            newPath[1];


                        cout
                            << "  Drone "
                            << drones[i].id
                            << " reroutes using BFS.\n";
                    }
                    else
                    {
                        // =================================
                        // IF REROUTE FAILS, DRONE WAITS
                        // =================================

                        nextPositions[i] =
                            currentPositions[i];

                        cout
                            << "  Drone "
                            << drones[i].id
                            << " waits.\n";
                    }
                }
            }
        }


        // =================================================
        // CHECK SAME-CELL COLLISIONS
        // =================================================

        for (int i = 0;
             i < drones.size();
             i++)
        {
            for (int j = i + 1;
                 j < drones.size();
                 j++)
            {
                if (samePosition(
                        nextPositions[i],
                        nextPositions[j]))
                {
                    cout
                        << "  SAME-CELL COLLISION: Drone "
                        << drones[j].id
                        << " waits.\n";


                    nextPositions[j] =
                        currentPositions[j];

                    collisionCount++;
                }
            }
        }


        // =================================================
        // HASH TABLE OCCUPANCY CHECK
        // =================================================

        unordered_map<string, int> occupiedCells;

        for (int i = 0;
             i < drones.size();
             i++)
        {
            string key =
                getKey(
                    nextPositions[i].row,
                    nextPositions[i].col
                );


            if (occupiedCells.find(key)
                != occupiedCells.end())
            {
                cout
                    << "  OCCUPANCY CONFLICT: Drone "
                    << drones[i].id
                    << " waits.\n";


                nextPositions[i] =
                    currentPositions[i];

                collisionCount++;
            }
            else
            {
                occupiedCells[key] =
                    drones[i].id;
            }
        }


        // =================================================
        // UPDATE POSITIONS
        // =================================================

        for (int i = 0;
             i < drones.size();
             i++)
        {
            if (!samePosition(
                    nextPositions[i],
                    currentPositions[i]))
            {
                pathIndex[i]++;
            }


            currentPositions[i] =
                nextPositions[i];


            cout
                << "  Drone "
                << drones[i].id
                << " -> ("
                << currentPositions[i].row
                << ","
                << currentPositions[i].col
                << ")\n";
        }


        cout << endl;
    }


    // =================================================
    // FINAL RESULT
    // =================================================

    cout
        << "===============================\n";


    cout
        << "Simulation completed in "
        << step
        << " steps.\n";


    cout
        << "Total collision events: "
        << collisionCount
        << endl;


    cout
        << "\nFinal Positions:\n";


    for (int i = 0;
         i < drones.size();
         i++)
    {
        cout
            << "Drone "
            << drones[i].id
            << ": ("
            << currentPositions[i].row
            << ","
            << currentPositions[i].col
            << ")";


        if (samePosition(
                currentPositions[i],
                drones[i].target))
        {
            cout
                << " - TARGET REACHED";
        }
        else
        {
            cout
                << " - TARGET NOT REACHED";
        }

        cout << endl;
    }


    return 0;
}