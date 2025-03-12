#include <iostream>
#include "maze.hpp"
#include "solver.hpp"
// compile using
/*
g++ -std=c++17 -o maze_solver main.cpp maze.cpp solver.cpp visualizer.cpp -lsfml-graphics -lsfml-window -lsfml-system
./maze_solver
*/
int main() {
    int n;
    std::cout << "Enter maze size (odd number >= 5): ";
    std::cin >> n;

    if (n < 5 || n % 2 == 0) {
        std::cout << "Invalid size! Using default size 11.\n";
        n = 11;
    }

    Maze maze(n);
    maze.generate();
    maze.saveToFile("maze.txt");

    Solver::findPath(maze);
    maze.saveToFile("solved_maze.txt");

    std::cout << "Maze saved to maze.txt and solved_maze.txt\n";
    std::cout << "Run 'python3 visualizer.py' to generate the maze image.\n";

    return 0;
}
