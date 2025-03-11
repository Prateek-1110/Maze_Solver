#include "solver.hpp"
bool Solver::solveMaze(vector<vector<int>> &maze, int x, int y, vector<vector<bool>> &visited) {
    if (x == maze.size() - 2 && y == maze[0].size() - 2) {
        maze[x][y] = 2; 
        return true;
    }
    if (x <= 0 || y <= 0 || x >= maze.size() - 1 || y >= maze[0].size() - 1 || maze[x][y] == 1 || visited[x][y])
        return false;

    visited[x][y] = true;
    maze[x][y] = 2;
//Recursively explore in four directions (down, right, up, left)
    if (solveMaze(maze, x + 1, y, visited) || solveMaze(maze, x, y + 1, visited) ||
        solveMaze(maze, x - 1, y, visited) || solveMaze(maze, x, y - 1, visited))
        return true;
    maze[x][y] = 0; 
    return false;
}
//Function to find the path in the maze
void Solver::findPath(Maze &maze) {
    vector<vector<int>> grid = maze.getGrid();
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    solveMaze(grid, 1, 1, visited);
}
