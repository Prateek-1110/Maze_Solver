#include "maze.hpp"
// creating n * n with walls( denoted as 1s)
Maze::Maze(int n) : size(n) {
    grid.resize(size, vector<int>(size, 1)); 
}
// function to make passage using backtracking 
void Maze::carvePassages(int x, int y) {
    vector<pair<int, int>> directions = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
// random changes to make maze unique 
    shuffle(directions.begin(), directions.end(), mt19937(random_device()()));
//loop for each direction to carve path
    for (auto [dx, dy] : directions) {
        int nx = x + dx, ny = y + dy;
        if (nx > 0 && ny > 0 && nx < size - 1 && ny < size - 1 && grid[nx][ny] == 1) {
            grid[x + dx / 2][y + dy / 2] = 0;
            grid[nx][ny] = 0;
            carvePassages(nx, ny);
        }
    }
}

void Maze::generate() {
    srand(time(0));
    grid[1][1] = 0; 
    carvePassages(1, 1);
    grid[size - 2][size - 2] = 0; 
}
void Maze::display() const {
    for (const auto &row : grid) {
        for (int cell : row)
            cout << cell << " ";
        cout << endl;
    }
}
vector<vector<int>> Maze::getGrid() const {
    return grid;
}
