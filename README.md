# 🌀 Maze Solver

A maze generator and solver built in **C++**, visualized as an **animated GIF**, and served through a **Streamlit web app** — no frontend framework needed.

This project started as a way to learn Python beyond the basics: exploring libraries like `imageio` and `numpy`, understanding how to bridge compiled C++ with a Python web interface, and figuring out how to ship something that actually runs in a browser.

---

## 🎯 Why This Project?

Most "learn Python" projects stop at scripts. This one goes further:

- **C++ does the hard work** — maze generation (recursive backtracking) and pathfinding (DFS) are performance-sensitive, so they live in compiled C++
- **Python handles the visual layer** — `numpy` for pixel manipulation, `imageio` for GIF encoding, `streamlit` for the web UI
- **The bridge between them** — Python's `subprocess` module calls the C++ binary and reads its output files, which is a pattern used in real production pipelines
- **Deployment without a server** — Streamlit Community Cloud gives a public URL for free, which meant figuring out how to compile C++ at runtime on someone else's Linux machine

The goal was never just "make a maze" — it was to understand how different layers of a stack talk to each other.

---

## ✨ Features

- 🏗️ **Random maze generation** using recursive backtracking (guaranteed solvable)
- 🔍 **DFS pathfinding** with full step-by-step logging
- 🎨 **Animated GIF output** showing the solver exploring, backtracking, and finding the path
- 📊 **Live stats** — steps explored, backtracks, path length, solve time
- 🎛️ **Adjustable maze size** (5×5 to 51×51) and animation speed
- ⬇️ **Download button** for the generated GIF
- 🌐 **Deployed as a public web app** on Streamlit Community Cloud

---

## 🎨 Colour Key

| Colour | Meaning |
|--------|---------|
| 🟦 Blue | Cell being explored |
| 🟥 Red | Dead end — backtracking |
| 🟩 Green | Final solution path |
| 🟨 Yellow | Start `(1,1)` |
| 🩷 Pink | End `(n-2, n-2)` |

---

## 🗂️ Project Structure

```
Maze_Solver/
│
├── main.cpp          # Entry point — accepts maze size as CLI arg
├── maze.hpp          # Maze class declaration
├── maze.cpp          # Maze generation (recursive backtracking)
├── solver.hpp        # Solver class declaration
├── solver.cpp        # DFS solver — logs every step to search_steps.txt
│
├── gif_maker.py      # Reads maze + steps, renders animated GIF with imageio
├── app.py            # Streamlit web UI — runs binary, calls gif_maker, shows result
│
├── packages.txt      # Tells Streamlit Cloud to install g++
├── setup.sh          # Compiles the C++ binary on the server
├── requirements.txt  # Python dependencies
├── .gitignore
└── README.md
```

---

## ⚙️ How It Works

```
User clicks "Generate & Solve"
        │
        ▼
app.py calls ./maze_solver <size>        ← subprocess
        │
        ├── maze.cpp generates a random maze  →  maze.txt
        └── solver.cpp runs DFS               →  solved_maze.txt
                                              →  search_steps.txt
        │
        ▼
gif_maker.py reads maze.txt + search_steps.txt
        │
        ├── Paints each VISIT / BACK / PATH step as a frame
        └── Stitches frames into maze_animation.gif   ← imageio
        │
        ▼
app.py displays the GIF + stats in the browser
```

### What `search_steps.txt` looks like

```
VISIT 1 1
VISIT 1 2
VISIT 1 3
BACK  1 3
VISIT 2 2
...
PATH  1 2
PATH  1 1
```

Each line is one recursive call. `VISIT` = exploring, `BACK` = dead end, `PATH` = confirmed solution (written on the way back up the call stack).

---

## 🚀 Running Locally

### 1. Clone the repo

```bash
git clone https://github.com/Prateek-1110/Maze_Solver.git
cd Maze_Solver
```

### 2. Compile the C++ solver

```bash
g++ -O2 -o maze_solver main.cpp maze.cpp solver.cpp
```

### 3. Set up Python environment

```bash
python -m venv venv
source venv/bin/activate      # Mac/Linux
# or
venv\Scripts\activate         # Windows

pip install -r requirements.txt
```

### 4. Launch the app

```bash
streamlit run app.py
```

Open `http://localhost:8501` in your browser.

---

## 🧪 Testing Without the UI

Run the C++ binary directly to verify it works:

```bash
./maze_solver 21
```

This writes three files:
- `maze.txt` — the generated maze grid (0 = open, 1 = wall)
- `solved_maze.txt` — same grid with `2` marking the solution path
- `search_steps.txt` — every step the solver took

Then generate the GIF standalone:

```bash
python gif_maker.py
```

---

## 📦 Dependencies

### C++
Standard library only (`<vector>`, `<fstream>`, `<random>`) — no external libs needed.

### Python

| Package | Purpose |
|---------|---------|
| `streamlit` | Web UI |
| `imageio` | GIF encoding |
| `numpy` | Pixel array manipulation |

---

## 🌐 Deployment (Streamlit Community Cloud)

The app is live at: **[your-app-url.streamlit.app]**

Streamlit Cloud runs Linux, so the C++ binary is compiled fresh on their server at startup using:
- `packages.txt` — tells the server to install `g++`
- `setup.sh` — runs the compile command
- `app.py` — checks for the binary at startup and compiles it automatically if missing

---

## 🧠 Things Learned

- How recursive backtracking works for both maze generation and DFS solving
- Using `ofstream` in C++ to log structured output consumed by another process
- `numpy` array slicing for fast pixel painting (much faster than per-pixel loops)
- `imageio.mimsave()` for GIF encoding with frame duration control
- `subprocess.run()` to call compiled binaries from Python
- Streamlit's layout system (`st.columns`, `st.slider`, `st.markdown` with inline HTML)
- Deploying an app that requires a C++ compile step at runtime on a cloud server

---

## 📄 License

MIT — use it, break it, learn from it.
