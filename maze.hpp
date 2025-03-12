#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <string>
#include <iostream>

class Maze {
private:
    int size;
    std::vector<std::vector<int>> grid;
    void carvePassages(int x, int y);

public:
    Maze(int n);
    void generate();
    void display() const;
    std::vector<std::vector<int>> getGrid() const;
    std::vector<std::vector<int>>& getGridRef(); // 🔹 Added this function
    void saveToFile(const std::string &filename) const;
};

#endif // MAZE_HPP
