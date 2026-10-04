CREATE TABLE Drones (
    drone_id INT PRIMARY KEY,
    drone_name VARCHAR(50) NOT NULL,
    start_row INT NOT NULL,
    start_col INT NOT NULL,
    target_row INT NOT NULL,
    target_col INT NOT NULL
);

INSERT INTO Drones
(drone_id, drone_name, start_row, start_col, target_row, target_col)
VALUES
(1, 'Drone 1', 0, 0, 9, 9),
(2, 'Drone 2', 0, 9, 9, 0),
(3, 'Drone 3', 9, 0, 0, 9);

CREATE TABLE Obstacles (
    obstacle_id INT PRIMARY KEY,
    row_position INT NOT NULL,
    col_position INT NOT NULL
);

INSERT INTO Obstacles
(obstacle_id, row_position, col_position)
VALUES
(1, 2, 4),
(2, 3, 4),
(3, 4, 4),
(4, 6, 2),
(5, 6, 3),
(6, 6, 4);

CREATE TABLE Simulations (
    simulation_id INT PRIMARY KEY,
    algorithm VARCHAR(20) NOT NULL,
    total_path_length INT NOT NULL,
    collision_count INT NOT NULL,
    coverage_percentage DECIMAL(5,2) NOT NULL,
    simulation_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Collision_Events (
    collision_id INT PRIMARY KEY,
    simulation_id INT NOT NULL,
    drone1_id INT NOT NULL,
    drone2_id INT NOT NULL,
    collision_step INT NOT NULL,
    collision_type VARCHAR(30) NOT NULL,
    
    FOREIGN KEY (simulation_id)
        REFERENCES Simulations(simulation_id),

    FOREIGN KEY (drone1_id)
        REFERENCES Drones(drone_id),

    FOREIGN KEY (drone2_id)
        REFERENCES Drones(drone_id)
);

INSERT INTO Simulations
(simulation_id, algorithm, total_path_length, collision_count, coverage_percentage)
VALUES
(1, 'BFS', 54, 2, 38.30);

INSERT INTO Collision_Events
(collision_id, simulation_id, drone1_id, drone2_id, collision_step, collision_type)
VALUES
(1, 1, 1, 3, 5, 'Swap Collision'),
(2, 1, 1, 2, 14, 'Swap Collision');