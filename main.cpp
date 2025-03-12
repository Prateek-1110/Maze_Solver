#include<bits/stdc++.h>
#include"visualizer.hpp"./
using namespace std;
int main() {
    int n;
    cout << "Enter maze size (odd number >= 5): ";
    cin >> n;
    if (n < 5 || n % 2 == 0) {
        std::cout << "Invalid size! Using default size 11.\n";
        n = 11;
    }
    runSFMLMode(n);
    return 0;
}
