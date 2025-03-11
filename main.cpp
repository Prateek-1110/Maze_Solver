#include "maze.hpp"
#include "solver.hpp"
int main() {
    int n;
    cout << "Enter the size of the maze (odd number >= 5): ";
    cin >> n;
// if n is not valid , code takes n as 11 for running
    if (n < 5 || n % 2 == 0) {
        cout << "Invalid size! Using default size 11.\n";
        n = 11;
    }
// this create maze of size n * n 
    Maze maze(n);
    maze.generate();
// printing maze before solving 
    cout << "\nGenerated Maze:\n";
    maze.display();
// printing maze after solving 
    cout << "\nSolved Maze:\n";
    Solver::findPath(maze);
    return 0;
}
