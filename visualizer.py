import cv2
import numpy as np

CELL_SIZE = 20  # Size of each maze cell in pixels
BORDER = 10  # Padding around the maze

def load_maze(filename):
    """Loads the maze from a text file into a 2D list."""
    with open(filename, "r") as f:
        return [list(map(int, line.split())) for line in f.readlines()]

def draw_maze(maze, solution_maze, output_file="maze.png"):
    """Creates an image of the maze with the solution path."""
    rows, cols = len(maze), len(maze[0])
    img_size = (cols * CELL_SIZE + 2 * BORDER, rows * CELL_SIZE + 2 * BORDER, 3)
    img = np.ones(img_size, dtype=np.uint8) * 255  # White background

    for i in range(rows):
        for j in range(cols):
            x1, y1 = j * CELL_SIZE + BORDER, i * CELL_SIZE + BORDER
            x2, y2 = x1 + CELL_SIZE, y1 + CELL_SIZE

            if maze[i][j] == 1:  # Walls
                cv2.rectangle(img, (x1, y1), (x2, y2), (0, 0, 0), -1)
            elif solution_maze[i][j] == 2:  # Solution Path
                cv2.rectangle(img, (x1, y1), (x2, y2), (0, 0, 255), -1)  # Red path

    cv2.imwrite(output_file, img)
    print(f"Maze visualization saved as {output_file}")

# Load and visualize
maze = load_maze("maze.txt")
solved_maze = load_maze("solved_maze.txt")
draw_maze(maze, solved_maze, "maze_solution.png")

# Show the generated image
image = cv2.imread("solved_maze.png")  # Change filename as needed
cv2.imshow("Maze Solution", image)
cv2.waitKey(0)
cv2.destroyAllWindows()
