// visualizer.cpp
#include <SFML/Graphics.hpp>
#include "maze.hpp"
#include "solver.hpp"

const int CELL_SIZE = 20;
const int PADDING = 40;
const int TEXT_HEIGHT = 30;

// Function to load font
bool loadFont(sf::Font &font) {
    if (font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") ||
        font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        return true;
    }
    return false;
}

// Function to draw labels
void drawLabel(sf::RenderWindow &window, const std::string &text, float x, float y, const sf::Font &font) {
    sf::Text label;
    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(20);
    label.setFillColor(sf::Color::White);
    label.setPosition(x, y);
    window.draw(label);
}

// Function to draw the maze
void drawMaze(sf::RenderWindow &window, const std::vector<std::vector<int>> &grid, int offsetX, bool isSolved) {
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(j * CELL_SIZE + offsetX, i * CELL_SIZE + TEXT_HEIGHT);

            if (grid[i][j] == 1) {
                cell.setFillColor(sf::Color(50, 50, 50)); // Walls
            } else if (isSolved && grid[i][j] == 2) {
                cell.setFillColor(sf::Color(255, 0, 0)); // Solution Path
            } else {
                cell.setFillColor(isSolved ? sf::Color(255, 165, 0) : sf::Color(173, 216, 230)); // Paths
            }
            cell.setOutlineColor(sf::Color::White);
            cell.setOutlineThickness(-1);
            window.draw(cell);
        }
    }
}

// Function to run SFML visualization
void runSFMLMode(int n) {
    Maze maze(n);
    maze.generate();
    std::vector<std::vector<int>> originalGrid = maze.getGrid();

    Solver::findPath(maze);
    std::vector<std::vector<int>> solvedGrid = maze.getGrid();

    int windowWidth = 2 * (n * CELL_SIZE) + PADDING;
    int windowHeight = (n * CELL_SIZE) + TEXT_HEIGHT;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Maze Solver");
    
    sf::Font font;
    if (!loadFont(font)) {
        std::cerr << "Error: Could not load font. Labels may not be visible.\n";
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(30, 30, 30));
        drawLabel(window, "Original Maze", (n * CELL_SIZE) / 4, 5, font);
        drawLabel(window, "Solved Maze", n * CELL_SIZE + PADDING + (n * CELL_SIZE) / 4, 5, font);
        drawMaze(window, originalGrid, 0, false);
        drawMaze(window, solvedGrid, n * CELL_SIZE + PADDING, true);
        window.display();
    }
}