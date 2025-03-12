#include "maze.hpp"
#include <fstream>
#include <random>
#include <iostream>
#include <algorithm> // Required for std::shuffle

using namespace std;

// Constructor: Initializes an `n x n` maze filled with walls (1s)
Maze::Maze(int n) : size(n) {
    grid.resize(size, vector<int>(size, 1)); 
}

// Function to create passages using recursive backtracking
void Maze::carvePassages(int x, int y) {
    vector<pair<int, int>> directions = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};

    // Shuffle directions for randomness
    random_device rd;
    mt19937 g(rd());
    shuffle(directions.begin(), directions.end(), g);

    // Loop for each direction to carve a path
    for (size_t i = 0; i < directions.size(); i++) {
        int dx = directions[i].first;
        int dy = directions[i].second;
        
        int nx = x + dx, ny = y + dy;

        if (nx > 0 && ny > 0 && nx < size - 1 && ny < size - 1 && grid[nx][ny] == 1) {
            grid[x + dx / 2][y + dy / 2] = 0; // Remove wall
            grid[nx][ny] = 0; // Make new path
            carvePassages(nx, ny); // Recur for next cell
        }
    }
}

// Function to generate the maze
void Maze::generate() {
    srand(time(0));
    grid[1][1] = 0; // Start point
    carvePassages(1, 1);
    grid[size - 2][size - 2] = 0; // End point
}

// Function to save the maze to a file
void Maze::saveToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            file << grid[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

// Function to display the maze in the console (for debugging)
void Maze::display() const {
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Getter function to return the maze grid
std::vector<std::vector<int>>& Maze::getGridRef() {
    return grid;
}
