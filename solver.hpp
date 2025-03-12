#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>  // 🔹 Required for std::vector
#include "maze.hpp"

class Solver {
public:
    static void findPath(Maze &maze);

private:
    static bool solveMaze(std::vector<std::vector<int>> &maze, int x, int y, std::vector<std::vector<bool>> &visited); // 🔹 Add std::
};

#endif // SOLVER_HPP
