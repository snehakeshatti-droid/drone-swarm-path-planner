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