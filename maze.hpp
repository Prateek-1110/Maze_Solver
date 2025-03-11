#ifndef MAZE_HPP
#define MAZE_HPP

#include <bits/stdc++.h>
using namespace std;

class Maze {
private:
    int size;
    vector<vector<int>> grid;
    void carvePassages(int x, int y);

public:
    Maze(int n);
    void generate();
    void display() const;
    vector<vector<int>> getGrid() const;
};

#endif
