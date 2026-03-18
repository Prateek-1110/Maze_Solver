#include "solver.hpp"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

// Global file stream for logging search steps
static ofstream stepsFile;

bool Solver::solveMaze(vector<vector<int>> &maze, int x, int y, vector<vector<bool>> &visited) {
    int rows = maze.size();
    int cols = maze[0].size();

    if (x == rows - 2 && y == cols - 2) {
        maze[x][y] = 2;
        // Log final cell as part of solution path
        if (stepsFile.is_open())
            stepsFile << "PATH " << x << " " << y << "\n";
        return true;
    }

    if (x <= 0 || y <= 0 || x >= rows - 1 || y >= cols - 1 || maze[x][y] == 1 || visited[x][y])
        return false;

    visited[x][y] = true;
    maze[x][y] = 2;

    // Log this cell as visited (exploring)
    if (stepsFile.is_open())
        stepsFile << "VISIT " << x << " " << y << "\n";

    if (solveMaze(maze, x + 1, y, visited) ||
        solveMaze(maze, x, y + 1, visited) ||
        solveMaze(maze, x - 1, y, visited) ||
        solveMaze(maze, x, y - 1, visited)) {
        // Mark as confirmed solution path on the way back up
        if (stepsFile.is_open())
            stepsFile << "PATH " << x << " " << y << "\n";
        return true;
    }

    maze[x][y] = 0;
    // Log backtrack
    if (stepsFile.is_open())
        stepsFile << "BACK " << x << " " << y << "\n";
    return false;
}

void Solver::findPath(Maze &maze) {
    // Open the steps log file
    stepsFile.open("search_steps.txt");
    if (!stepsFile.is_open()) {
        cerr << "Error: Could not open search_steps.txt for writing." << endl;
    }

    vector<vector<int>> &grid = maze.getGridRef();
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    solveMaze(grid, 1, 1, visited);

    stepsFile.close();
    maze.saveToFile("solved_maze.txt");
}