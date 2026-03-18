#include "maze.hpp"
#include "solver.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int n = 21; // Default maze size (must be odd for proper generation)

    if (argc >= 2) {
        n = atoi(argv[1]);
        // Enforce odd size for recursive backtracking to work correctly
        if (n % 2 == 0) n++;
        // Clamp to a reasonable range
        if (n < 5) n = 5;
        if (n > 101) n = 101;
    }

    std::cout << "Generating " << n << "x" << n << " maze..." << std::endl;

    Maze maze(n);
    maze.generate();
    maze.saveToFile("maze.txt");

    std::cout << "Solving maze..." << std::endl;
    Solver::findPath(maze);

    std::cout << "Done. Output: maze.txt, solved_maze.txt, search_steps.txt" << std::endl;
    return 0;
}