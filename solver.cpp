#include "solver.hpp"
#include <fstream>
#include <vector>  // 🔹 Include vector header
#include <iostream> // 🔹 Optional: For debugging output

using namespace std; // 🔹 Required for vector, cout, etc.

bool Solver::solveMaze(vector<vector<int>> &maze, int x, int y, vector<vector<bool>> &visited) {
    int rows = maze.size();
    int cols = maze[0].size();

    if (x == rows - 2 && y == cols - 2) {  // 🔹 Check if we've reached the end
        maze[x][y] = 2; 
        return true;
    }

    if (x <= 0 || y <= 0 || x >= rows - 1 || y >= cols - 1 || maze[x][y] == 1 || visited[x][y])
        return false;

    visited[x][y] = true;
    maze[x][y] = 2; // Mark path

    // 🔹 Recursively explore in four directions (down, right, up, left)
    if (solveMaze(maze, x + 1, y, visited) || 
        solveMaze(maze, x, y + 1, visited) || 
        solveMaze(maze, x - 1, y, visited) || 
        solveMaze(maze, x, y - 1, visited)) {
        return true;
    }

    maze[x][y] = 0; // Backtrack
    return false;
}

// 🔹 Function to find and solve the maze path
void Solver::findPath(Maze &maze) {
    vector<vector<int>> &grid = maze.getGridRef();  // Get a reference to the actual maze grid
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    solveMaze(grid, 1, 1, visited);
    maze.saveToFile("solved_maze.txt");
}
