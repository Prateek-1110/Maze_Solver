import numpy as np
import imageio.v2 as imageio
import os

CELL_SIZE = 20
BORDER = 10

# Color palette (RGB for imageio)
COLOR_WALL       = (15,  15,  20)    # Near-black walls
COLOR_OPEN       = (240, 238, 230)   # Off-white open cells
COLOR_VISIT      = (80,  160, 220)   # Blue  – exploring
COLOR_BACK       = (220, 100,  80)   # Red   – backtracking
COLOR_PATH       = (80,  200, 120)   # Green – final solution
COLOR_START      = (255, 210,  60)   # Yellow – start
COLOR_END        = (255, 120, 200)   # Pink  – end
COLOR_BORDER_BG  = (30,  30,  40)    # Dark border background


def load_maze(filename: str) -> list[list[int]]:
    with open(filename, "r") as f:
        return [list(map(int, line.split())) for line in f if line.strip()]


def load_steps(filename: str) -> list[tuple[str, int, int]]:
    steps = []
    with open(filename, "r") as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) == 3:
                action, x, y = parts[0], int(parts[1]), int(parts[2])
                steps.append((action, x, y))
    return steps


def make_base_image(maze: list[list[int]]) -> np.ndarray:
    """Draw the static maze walls and open cells."""
    rows, cols = len(maze), len(maze[0])
    w = cols * CELL_SIZE + 2 * BORDER
    h = rows * CELL_SIZE + 2 * BORDER
    img = np.full((h, w, 3), COLOR_BORDER_BG, dtype=np.uint8)

    for i in range(rows):
        for j in range(cols):
            x1 = j * CELL_SIZE + BORDER
            y1 = i * CELL_SIZE + BORDER
            x2 = x1 + CELL_SIZE
            y2 = y1 + CELL_SIZE
            color = COLOR_WALL if maze[i][j] == 1 else COLOR_OPEN
            img[y1:y2, x1:x2] = color

    return img


def paint_cell(img: np.ndarray, row: int, col: int, color: tuple, shrink: int = 1):
    """Paint a single cell, optionally shrinking for a grid-gap look."""
    x1 = col * CELL_SIZE + BORDER + shrink
    y1 = row * CELL_SIZE + BORDER + shrink
    x2 = x1 + CELL_SIZE - 2 * shrink
    y2 = y1 + CELL_SIZE - 2 * shrink
    img[y1:y2, x1:x2] = color


def generate_gif(
    maze_file: str = "maze.txt",
    steps_file: str = "search_steps.txt",
    output_gif: str = "maze_animation.gif",
    frame_skip: int = 3,      # render every Nth step to keep GIF size manageable
    fps: int = 20,
    hold_last: int = 60,      # extra frames to hold the final solved state
):
    maze = load_maze(maze_file)
    steps = load_steps(steps_file)

    rows, cols = len(maze), len(maze[0])
    base = make_base_image(maze)

    # Mark start / end on base
    start_r, start_c = 1, 1
    end_r,   end_c   = rows - 2, cols - 2

    frames: list[np.ndarray] = []

    # --- Phase 1: show the blank maze for a moment ---
    blank = base.copy()
    paint_cell(blank, start_r, start_c, COLOR_START)
    paint_cell(blank, end_r,   end_c,   COLOR_END)
    for _ in range(20):
        frames.append(blank.copy())

    # --- Phase 2: animate search steps ---
    current = blank.copy()

    # Track cell states so we can colour correctly
    cell_state: dict[tuple[int, int], str] = {}

    for idx, (action, x, y) in enumerate(steps):
        cell_state[(x, y)] = action

        if action == "VISIT":
            paint_cell(current, x, y, COLOR_VISIT)
        elif action == "BACK":
            paint_cell(current, x, y, COLOR_BACK)
        elif action == "PATH":
            paint_cell(current, x, y, COLOR_PATH)

        # Always keep start/end visible on top
        paint_cell(current, start_r, start_c, COLOR_START)
        paint_cell(current, end_r,   end_c,   COLOR_END)

        if idx % frame_skip == 0:
            frames.append(current.copy())

    # --- Phase 3: hold final state ---
    final = current.copy()
    for _ in range(hold_last):
        frames.append(final)

    # --- Write GIF ---
    duration = 1.0 / fps  # seconds per frame
    imageio.mimsave(
        output_gif,
        frames,
        duration=duration,
        loop=0,  # loop forever
    )
    print(f"GIF saved → {output_gif}  ({len(frames)} frames, {len(steps)} steps)")
    return output_gif


if __name__ == "__main__":
    generate_gif()