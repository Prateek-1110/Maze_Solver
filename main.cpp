#include <SFML/Graphics.hpp>
#include <iostream>
#include "maze.hpp"
#include "solver.hpp"

const int CELL_SIZE = 20;
const int PADDING = 40;
const int TEXT_HEIGHT = 30;

// Function to load a font safely
bool loadFont(sf::Font &font) {
    if (font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        return true;
    }
    if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        return true;
    }
    std::cerr << "Error: Could not load font. Text may not be visible.\n";
    return false;
}

// Function to draw a label on the SFML window
void drawLabel(sf::RenderWindow &window, const std::string &text, float x, float y, const sf::Font &font) {
    sf::Text label;
    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(20);
    label.setFillColor(sf::Color::White);
    label.setPosition(x, y);
    window.draw(label);
}

// Function to draw the maze with different colors for walls, paths, and solutions
void drawMaze(sf::RenderWindow &window, const std::vector<std::vector<int>> &grid, int offsetX, bool isSolved) {
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(j * CELL_SIZE + offsetX, i * CELL_SIZE + TEXT_HEIGHT);

            if (grid[i][j] == 1) {
                cell.setFillColor(sf::Color(50, 50, 50)); // Walls (Dark Gray)
            } else if (isSolved && grid[i][j] == 2) {
                cell.setFillColor(sf::Color(255, 0, 0)); // Solution Path (Red)
            } else {
                cell.setFillColor(isSolved ? sf::Color(255, 165, 0) : sf::Color(173, 216, 230)); // Solved (Orange) / Original (Light Blue)
            }
            cell.setOutlineColor(sf::Color::White);
            cell.setOutlineThickness(-1);
            window.draw(cell);
        }
    }
}

// Function to run the console-based solver
void runConsoleMode(int n) {
    Maze maze(n);
    maze.generate();
    
    std::cout << "\nGenerated Maze:\n";
    maze.display();

    std::cout << "\nSolved Maze:\n";
    Solver::findPath(maze);
}

// Function to run the SFML visualization
void runSFMLMode(int n) {
    Maze maze(n);
    maze.generate();
    std::vector<std::vector<int>> originalGrid = maze.getGrid();

    Solver::findPath(maze);
    std::vector<std::vector<int>> solvedGrid = maze.getGrid();

    // SFML Window Dimensions
    int windowWidth = 2 * (n * CELL_SIZE) + PADDING;
    int windowHeight = (n * CELL_SIZE) + TEXT_HEIGHT;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Maze Solver");
    sf::Font font;
    bool fontLoaded = loadFont(font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(30, 30, 30)); // Dark background

        // Calculate label positions dynamically
        float labelOffsetX = (n * CELL_SIZE) / 4;
        drawLabel(window, "Original Maze", labelOffsetX, 5, font);
        drawLabel(window, "Solved Maze", n * CELL_SIZE + PADDING + labelOffsetX, 5, font);

        // Draw the mazes
        drawMaze(window, originalGrid, 0, false); // Left: Original maze
        drawMaze(window, solvedGrid, n * CELL_SIZE + PADDING, true); // Right: Solved maze

        window.display();
    }
}

int main() {
    int n, choice;

    std::cout << "Enter maze size (odd number >= 5): ";
    std::cin >> n;

    if (n < 5 || n % 2 == 0) {
        std::cout << "Invalid size! Using default size 11.\n";
        n = 11;
    }

    std::cout << "\nChoose mode:\n";
    std::cout << "1. Console Mode\n";
    std::cout << "2. SFML Visualization Mode\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    if (choice == 1) {
        runConsoleMode(n);
    } else if (choice == 2) {
        runSFMLMode(n);
    } else {
        std::cout << "Invalid choice! Exiting.\n";
    }

    return 0;
}
