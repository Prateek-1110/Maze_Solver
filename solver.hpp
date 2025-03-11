#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "maze.hpp"

class Solver {
public:
    static void findPath(Maze &maze);
private:
    static bool solveMaze(vector<vector<int>> &maze, int x, int y, vector<vector<bool>> &visited);
};

#endif
