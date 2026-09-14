const obstacles = [
    [2, 4],
    [3, 4],
    [4, 4],
    [6, 2],
    [6, 3],
    [6, 4]
];

const drones = [
    { id: 1, start: [0, 0], target: [9, 9] },
    { id: 2, start: [0, 9], target: [9, 0] },
    { id: 3, start: [9, 0], target: [0, 9] }
];

let collisionCount = 0;
let simulationRunning = false;
let totalPathLength = 0;
let coveragePercentage = 0;

const grid = document.getElementById("grid");


// ==========================================
// CHECK OBSTACLE
// ==========================================

function isObstacle(row, col) {
    return obstacles.some(([r, c]) => r === row && c === col);
}


// ==========================================
// BFS PATHFINDING
// ==========================================

function bfs(start, target) {

    const queue = [start];
    const visited = new Set();
    const parent = new Map();

    const startKey = `${start[0]},${start[1]}`;

    visited.add(startKey);

    const directions = [
        [-1, 0],
        [1, 0],
        [0, -1],
        [0, 1]
    ];

    while (queue.length > 0) {

        const current = queue.shift();

        const row = current[0];
        const col = current[1];

        if (row === target[0] && col === target[1]) {
            break;
        }

        for (const [dr, dc] of directions) {

            const newRow = row + dr;
            const newCol = col + dc;

            if (
                newRow < 0 ||
                newRow >= 10 ||
                newCol < 0 ||
                newCol >= 10
            ) {
                continue;
            }

            if (isObstacle(newRow, newCol)) {
                continue;
            }

            const key = `${newRow},${newCol}`;

            if (!visited.has(key)) {

                visited.add(key);

                parent.set(key, current);

                queue.push([newRow, newCol]);
            }
        }
    }


    // ==========================================
    // RECONSTRUCT BFS PATH
    // ==========================================

    const path = [];

    let current = target;

    while (current) {

        path.push(current);

        const key = `${current[0]},${current[1]}`;

        current = parent.get(key);
    }

    path.reverse();

    return path;
}


// ==========================================
// DIJKSTRA PATHFINDING
// ==========================================

function dijkstra(start, target) {

    const distances = new Map();
    const parent = new Map();
    const visited = new Set();

    const priorityQueue = [];

    const startKey = `${start[0]},${start[1]}`;
    const targetKey = `${target[0]},${target[1]}`;


    // Initialize distances
    for (let row = 0; row < 10; row++) {

        for (let col = 0; col < 10; col++) {

            if (!isObstacle(row, col)) {

                const key = `${row},${col}`;

                distances.set(key, Infinity);
            }
        }
    }


    distances.set(startKey, 0);

    priorityQueue.push({
        position: start,
        distance: 0
    });


    const directions = [
        [-1, 0],
        [1, 0],
        [0, -1],
        [0, 1]
    ];


    // ==========================================
    // DIJKSTRA LOOP
    // ==========================================

    while (priorityQueue.length > 0) {

        priorityQueue.sort(
            (a, b) => a.distance - b.distance
        );

        const currentNode =
            priorityQueue.shift();

        const current =
            currentNode.position;

        const currentDistance =
            currentNode.distance;

        const currentKey =
            `${current[0]},${current[1]}`;


        if (visited.has(currentKey)) {
            continue;
        }

        visited.add(currentKey);


        if (currentKey === targetKey) {
            break;
        }


        for (const [dr, dc] of directions) {

            const newRow =
                current[0] + dr;

            const newCol =
                current[1] + dc;


            if (
                newRow < 0 ||
                newRow >= 10 ||
                newCol < 0 ||
                newCol >= 10
            ) {
                continue;
            }


            if (isObstacle(newRow, newCol)) {
                continue;
            }


            const neighborKey =
                `${newRow},${newCol}`;


            const newDistance =
                currentDistance + 1;


            if (
                newDistance <
                distances.get(neighborKey)
            ) {

                distances.set(
                    neighborKey,
                    newDistance
                );


                parent.set(
                    neighborKey,
                    current
                );


                priorityQueue.push({
                    position: [newRow, newCol],
                    distance: newDistance
                });
            }
        }
    }


    // ==========================================
    // RECONSTRUCT DIJKSTRA PATH
    // ==========================================

    const path = [];

    let current = target;

    while (current) {

        path.push(current);

        const key =
            `${current[0]},${current[1]}`;

        current = parent.get(key);
    }

    path.reverse();

    return path;
}


// ==========================================
// CREATE GRID
// ==========================================

for (let row = 0; row < 10; row++) {

    for (let col = 0; col < 10; col++) {

        const cell =
            document.createElement("div");

        cell.classList.add("cell");


        // Add obstacles
        if (isObstacle(row, col)) {

            cell.classList.add("obstacle");
        }


        // Add drone starting positions
        drones.forEach(drone => {

            if (
                drone.start[0] === row &&
                drone.start[1] === col
            ) {

                cell.classList.add(
                    `drone${drone.id}`
                );

                cell.textContent =
                    `D${drone.id}`;
            }
        });


        // Add target positions
        drones.forEach(drone => {

            if (
                drone.target[0] === row &&
                drone.target[1] === col
            ) {

                cell.classList.add("target");

                if (!cell.textContent) {

                    cell.textContent = "T";
                }
            }
        });


        grid.appendChild(cell);
    }
}


// ==========================================
// SELECT ALGORITHM
// ==========================================

const algorithmSelect =
    document.getElementById(
        "algorithmSelect"
    );


// ==========================================
// CALCULATE SELECTED ALGORITHM PATHS
// ==========================================

function calculatePaths() {

    const selectedAlgorithm =
        algorithmSelect.value;


    // Reset total path length
    totalPathLength = 0;


    // Reset coverage
    coveragePercentage = 0;


    // Store all cells covered by drones
    const coveredCells = new Set();


    // ==========================================
    // CALCULATE DRONE PATHS
    // ==========================================

    drones.forEach(drone => {

        // ------------------------------------------
        // DIJKSTRA
        // ------------------------------------------

        if (selectedAlgorithm === "dijkstra") {

            drone.path =
                dijkstra(
                    drone.start,
                    drone.target
                );


            console.log(
                `Drone ${drone.id} Dijkstra Path:`,
                drone.path
            );

        }


        // ------------------------------------------
        // BFS
        // ------------------------------------------

        else {

            drone.path =
                bfs(
                    drone.start,
                    drone.target
                );


            console.log(
                `Drone ${drone.id} BFS Path:`,
                drone.path
            );
        }


        // ------------------------------------------
        // CALCULATE PATH LENGTH
        // ------------------------------------------

        const dronePathLength =
            drone.path.length - 1;


        totalPathLength +=
            dronePathLength;


        // ------------------------------------------
        // CALCULATE COVERED CELLS
        // ------------------------------------------

        drone.path.forEach(position => {

            const row = position[0];
            const col = position[1];

            if (!isObstacle(row, col)) {

                coveredCells.add(
                    `${row},${col}`
                );
            }
        });
    });


    // ==========================================
    // CALCULATE COVERAGE PERCENTAGE
    // ==========================================

    const totalGridCells = 10 * 10;

    const totalFreeCells =
        totalGridCells - obstacles.length;


    coveragePercentage =
        (
            coveredCells.size /
            totalFreeCells
        ) * 100;


    // ==========================================
    // UPDATE ALGORITHM DISPLAY
    // ==========================================

    document.getElementById(
        "algorithm"
    ).textContent =
        selectedAlgorithm === "dijkstra"
            ? "Dijkstra"
            : "BFS";


    // ==========================================
    // UPDATE PATH LENGTH DISPLAY
    // ==========================================

    document.getElementById(
        "pathLength"
    ).textContent =
        totalPathLength;


    // ==========================================
    // UPDATE COVERAGE DISPLAY
    // ==========================================

    document.getElementById(
        "coverage"
    ).textContent =
        coveragePercentage.toFixed(2);
}


// ==========================================
// CALCULATE INITIAL PATHS
// ==========================================

calculatePaths();


// ==========================================
// DISPLAY PATHS
// ==========================================

function displayPaths() {

    // Remove old paths
    document
        .querySelectorAll(".cell")
        .forEach(cell => {

            cell.classList.remove(
                "path1",
                "path2",
                "path3"
            );
        });


    // Draw paths
    drones.forEach(drone => {

        drone.path.forEach(
            ([row, col]) => {

                const cellIndex =
                    row * 10 + col;

                const cell =
                    grid.children[
                        cellIndex
                    ];


                if (
                    !cell.classList.contains(
                        `drone${drone.id}`
                    ) &&
                    !cell.classList.contains(
                        "target"
                    ) &&
                    !cell.classList.contains(
                        "obstacle"
                    )
                ) {

                    cell.classList.add(
                        `path${drone.id}`
                    );
                }
            }
        );
    });
}


// ==========================================
// DISPLAY INITIAL PATHS
// ==========================================

displayPaths();


// ==========================================
// CHANGE ALGORITHM
// ==========================================

algorithmSelect.addEventListener(
    "change",
    () => {

        // Don't change during simulation
        if (simulationRunning) {
            return;
        }


        calculatePaths();

        displayPaths();


        // Reset status
        document.getElementById(
            "status"
        ).textContent =
            "Ready";
    }
);


// ==========================================
// START SIMULATION BUTTON
// ==========================================

const startButton =
    document.getElementById(
        "startSimulation"
    );


startButton.addEventListener(
    "click",
    () => {


        // Prevent multiple simulations
        if (simulationRunning) {
            return;
        }


        simulationRunning = true;


        // Reset collision count
        collisionCount = 0;


        document.getElementById(
            "collisionCount"
        ).textContent =
            collisionCount;


        // Update status
        document.getElementById(
            "status"
        ).textContent =
            "Running";


        // ==========================================
        // INITIALIZE DRONE POSITIONS
        // ==========================================

        drones.forEach(drone => {

            drone.current =
                [...drone.start];


            drone.pathIndex = 1;
        });


        // ==========================================
        // SIMULATION LOOP
        // ==========================================

        const simulation =
            setInterval(
                () => {

                    let allFinished = true;


                    // Store proposed movements
                    const proposedMoves =
                        new Map();


                    // ==========================================
                    // FIND NEXT POSITION
                    // ==========================================

                    drones.forEach(drone => {

                        if (
                            drone.pathIndex <
                            drone.path.length
                        ) {

                            allFinished = false;


                            const nextPosition =
                                drone.path[
                                    drone.pathIndex
                                ];


                            proposedMoves.set(
                                drone.id,
                                nextPosition
                            );
                        }
                    });


                    // ==========================================
                    // COLLISION DETECTION
                    // ==========================================

                    const blockedDrones =
                        new Set();


                    const collisionPairs =
                        new Set();


                    // ------------------------------------------
                    // SAME CELL COLLISION
                    // ------------------------------------------

                    const destinationMap =
                        new Map();


                    proposedMoves.forEach(
                        (position, droneId) => {

                            const key =
                                `${position[0]},${position[1]}`;


                            if (
                                destinationMap.has(
                                    key
                                )
                            ) {

                                const otherDrone =
                                    destinationMap.get(
                                        key
                                    );


                                const pairKey =
                                    [
                                        otherDrone,
                                        droneId
                                    ]
                                        .sort(
                                            (a, b) =>
                                                a - b
                                        )
                                        .join("-");


                                if (
                                    !collisionPairs.has(
                                        pairKey
                                    )
                                ) {

                                    collisionPairs.add(
                                        pairKey
                                    );


                                    collisionCount++;


                                    console.log(
                                        `SAME CELL COLLISION: Drone ${otherDrone} and Drone ${droneId}`
                                    );
                                }


                                // Lower ID gets priority
                                if (
                                    droneId >
                                    otherDrone
                                ) {

                                    blockedDrones.add(
                                        droneId
                                    );

                                } else {

                                    blockedDrones.add(
                                        otherDrone
                                    );
                                }

                            } else {

                                destinationMap.set(
                                    key,
                                    droneId
                                );
                            }
                        }
                    );


                    // ------------------------------------------
                    // SWAP COLLISION
                    // ------------------------------------------

                    for (
                        let i = 0;
                        i < drones.length;
                        i++
                    ) {

                        for (
                            let j = i + 1;
                            j < drones.length;
                            j++
                        ) {

                            const droneA =
                                drones[i];

                            const droneB =
                                drones[j];


                            const nextA =
                                proposedMoves.get(
                                    droneA.id
                                );

                            const nextB =
                                proposedMoves.get(
                                    droneB.id
                                );


                            if (
                                !nextA ||
                                !nextB
                            ) {

                                continue;
                            }


                            // Check position swap
                            const isSwap =
                                nextA[0] ===
                                    droneB.current[0] &&
                                nextA[1] ===
                                    droneB.current[1] &&
                                nextB[0] ===
                                    droneA.current[0] &&
                                nextB[1] ===
                                    droneA.current[1];


                            if (isSwap) {

                                const pairKey =
                                    [
                                        droneA.id,
                                        droneB.id
                                    ]
                                        .sort(
                                            (a, b) =>
                                                a - b
                                        )
                                        .join("-");


                                if (
                                    !collisionPairs.has(
                                        pairKey
                                    )
                                ) {

                                    collisionPairs.add(
                                        pairKey
                                    );


                                    collisionCount++;


                                    console.log(
                                        `SWAP COLLISION: Drone ${droneA.id} and Drone ${droneB.id}`
                                    );
                                }


                                // Higher-numbered drone waits
                                const waitingDrone =
                                    droneA.id >
                                    droneB.id
                                        ? droneA.id
                                        : droneB.id;


                                blockedDrones.add(
                                    waitingDrone
                                );
                            }
                        }
                    }


                    // ==========================================
                    // UPDATE COLLISION COUNT
                    // ==========================================

                    document.getElementById(
                        "collisionCount"
                    ).textContent =
                        collisionCount;


                    // ==========================================
                    // UPDATE STATUS
                    // ==========================================

                    if (
                        collisionPairs.size > 0
                    ) {

                        document.getElementById(
                            "status"
                        ).textContent =
                            "⚠️ Collision Avoided";

                    } else {

                        document.getElementById(
                            "status"
                        ).textContent =
                            "Running";
                    }


                    // ==========================================
                    // MOVE DRONES
                    // ==========================================

                    drones.forEach(drone => {

                        const nextPosition =
                            proposedMoves.get(
                                drone.id
                            );


                        // No remaining path
                        if (!nextPosition) {
                            return;
                        }


                        // Drone waits
                        // because of collision
                        if (
                            blockedDrones.has(
                                drone.id
                            )
                        ) {

                            console.log(
                                `Drone ${drone.id} waits to avoid collision.`
                            );

                            return;
                        }


                        // Move drone
                        drone.current = [
                            nextPosition[0],
                            nextPosition[1]
                        ];


                        // Move to next path position
                        drone.pathIndex++;
                    });


                    // ==========================================
                    // REDRAW DRONES
                    // ==========================================

                    document
                        .querySelectorAll(".cell")
                        .forEach(cell => {

                            cell.classList.remove(
                                "drone1",
                                "drone2",
                                "drone3"
                            );


                            // Restore target text
                            if (
                                cell.classList.contains(
                                    "target"
                                )
                            ) {

                                cell.textContent =
                                    "T";

                            } else {

                                cell.textContent =
                                    "";
                            }
                        });


                    // Draw drones
                    drones.forEach(drone => {

                        const row =
                            drone.current[0];

                        const col =
                            drone.current[1];


                        const cellIndex =
                            row * 10 + col;


                        const cell =
                            grid.children[
                                cellIndex
                            ];


                        cell.classList.add(
                            `drone${drone.id}`
                        );


                        cell.textContent =
                            `D${drone.id}`;
                    });


                    // ==========================================
                    // CHECK COMPLETION
                    // ==========================================

                    if (allFinished) {

                        clearInterval(
                            simulation
                        );


                        simulationRunning =
                            false;


                        document.getElementById(
                            "status"
                        ).textContent =
                            "Completed";


                        console.log(
                            "Simulation completed!"
                        );


                        alert(
                            "Simulation completed!"
                        );
                    }


                },
                500
            );
    }
);

// ==========================================
// RESET SIMULATION
// ==========================================

const resetButton =
    document.getElementById("resetSimulation");

resetButton.addEventListener("click", () => {

    // Stop any running simulation
    simulationRunning = false;

    // Reset collision count
    collisionCount = 0;

    document.getElementById("collisionCount").textContent =
        collisionCount;

    // Reset drone positions
    drones.forEach(drone => {
        drone.current = [...drone.start];
        drone.pathIndex = 1;
    });

    // Recalculate paths
    calculatePaths();

    // Display paths again
    displayPaths();

    // Restore drone positions
    drones.forEach(drone => {

        const row = drone.start[0];
        const col = drone.start[1];

        const cellIndex = row * 10 + col;
        const cell = grid.children[cellIndex];

        cell.classList.add(`drone${drone.id}`);
        cell.textContent = `D${drone.id}`;
    });

    // Reset status
    document.getElementById("status").textContent =
        "Ready";
});