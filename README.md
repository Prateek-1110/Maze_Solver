# **Maze Solver**

## ** Project Overview**
The **Maze Solver** is a C++ application that generates a random `n x n` maze and finds the optimal path from the start to the goal. The program utilizes efficient pathfinding algorithms and visually displays the maze using **SFML (Simple and Fast Multimedia Library)**.

## **🛠 Features**
- ✅ **Random Maze Generation** with walls (`1`) and open paths (`0`).
- ✅ **User-Defined Maze Size** (`n x n` matrix based on input).
- ✅ **Pathfinding Algorithm** to find the shortest path.
- ✅ **SFML Visualization** to display the **original** and **solved** maze side by side.
- ✅ **Color-coded Representation** for walls, paths, and solutions.

## **📂 Project Structure**
```
MazeSolver/
│-- src/
│   ├── main.cpp
│   ├── maze_generator.cpp
│   ├── solver.cpp
│-- include/
│   ├── maze_generator.hpp
│   ├── solver.hpp
│-- assets/ (if needed for UI elements)
│-- README.md
│-- CMakeLists.txt (if using CMake)
```

## **📦 Dependencies**
Ensure you have the following installed:
- **C++ Compiler** (GCC, Clang, MSVC, etc.)
- **SFML Library** (for visualization)
- **CMake** (optional, for build automation)

## **🚀 Installation & Usage**
### **1️⃣ Clone the Repository**
```bash
git clone https://github.com/yourusername/MazeSolver.git
cd MazeSolver
```

### **2️⃣ Build the Project**
#### Using g++:
```bash
g++ -o maze_solver src/*.cpp -Iinclude -lsfml-graphics -lsfml-window -lsfml-system
```
#### Using CMake:
```bash
mkdir build && cd build
cmake ..
make
```

### **3️⃣ Run the Maze Solver**
```bash
./maze_solver
```

## **🎨 Visualization (SFML)**
- **Left Panel:** Displays the randomly generated maze.
- **Right Panel:** Displays the solved maze with the path highlighted.
- **Legend:**
  - **Black** → Walls
  - **White** → Open Paths
  - **Green** → Start Point
  - **Red** → Goal
  - **Blue** → Solved Path


## **📜 License**
This project is licensed under the **MIT License**.

## **📬 Contact**
For any issues or improvements, feel free to reach out!
- **GitHub Issues**: [Link to Issues](https://github.com/Prateek-1110/MazeSolver/issues)
- **Email**: b23bb1033@iitj.ac.in

