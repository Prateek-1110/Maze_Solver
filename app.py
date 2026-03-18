import streamlit as st
import subprocess
import os
import time
from gif_maker import generate_gif

# ── Page config ────────────────────────────────────────────────────────────────
st.set_page_config(
    page_title="Maze Solver",
    page_icon="🌀",
    layout="centered",
)

# ── Custom CSS ─────────────────────────────────────────────────────────────────
st.markdown("""
<style>
@import url('https://fonts.googleapis.com/css2?family=Space+Mono:wght@400;700&family=Inter:wght@300;400;600&display=swap');

html, body, [class*="css"] {
    font-family: 'Inter', sans-serif;
    background-color: #0d0f14;
    color: #e8e6de;
}

h1, h2, h3 {
    font-family: 'Space Mono', monospace;
}

/* Header */
.hero {
    text-align: center;
    padding: 2.5rem 0 1rem 0;
}
.hero h1 {
    font-size: 2.8rem;
    letter-spacing: -1px;
    background: linear-gradient(135deg, #50c878 30%, #50a0dc 100%);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    margin-bottom: 0.3rem;
}
.hero p {
    color: #888;
    font-size: 0.95rem;
    font-weight: 300;
}

/* Legend */
.legend {
    display: flex;
    gap: 1.2rem;
    justify-content: center;
    flex-wrap: wrap;
    margin: 1.2rem 0;
}
.legend-item {
    display: flex;
    align-items: center;
    gap: 0.4rem;
    font-size: 0.8rem;
    color: #aaa;
}
.dot {
    width: 12px;
    height: 12px;
    border-radius: 3px;
}

/* Stats bar */
.stats-bar {
    background: #1a1d26;
    border: 1px solid #2a2d3a;
    border-radius: 10px;
    padding: 1rem 1.5rem;
    display: flex;
    gap: 2rem;
    justify-content: center;
    margin: 1rem 0;
    font-family: 'Space Mono', monospace;
}
.stat {
    text-align: center;
}
.stat-val {
    font-size: 1.4rem;
    color: #50c878;
}
.stat-lbl {
    font-size: 0.7rem;
    color: #666;
    text-transform: uppercase;
    letter-spacing: 1px;
}

/* Slider label */
.stSlider label { color: #aaa !important; font-size: 0.85rem; }

/* Button */
.stButton > button {
    background: linear-gradient(135deg, #50c878, #50a0dc);
    color: #0d0f14;
    font-family: 'Space Mono', monospace;
    font-weight: 700;
    font-size: 1rem;
    border: none;
    border-radius: 8px;
    padding: 0.7rem 2rem;
    width: 100%;
    cursor: pointer;
    transition: opacity 0.2s;
}
.stButton > button:hover { opacity: 0.85; }

/* Error / info boxes */
.err-box {
    background: #2a1515;
    border: 1px solid #c84040;
    border-radius: 8px;
    padding: 1rem;
    color: #e88;
    font-family: 'Space Mono', monospace;
    font-size: 0.8rem;
}
</style>
""", unsafe_allow_html=True)

# ── Hero header ────────────────────────────────────────────────────────────────
st.markdown("""
<div class="hero">
    <h1>🌀 Maze Solver</h1>
    <p>Recursive backtracking — visualised step by step</p>
</div>
""", unsafe_allow_html=True)

# ── Colour legend ──────────────────────────────────────────────────────────────
st.markdown("""
<div class="legend">
    <div class="legend-item"><div class="dot" style="background:#50a0dc"></div> Exploring</div>
    <div class="legend-item"><div class="dot" style="background:#dc6450"></div> Backtrack</div>
    <div class="legend-item"><div class="dot" style="background:#50c878"></div> Solution</div>
    <div class="legend-item"><div class="dot" style="background:#ffd23c"></div> Start</div>
    <div class="legend-item"><div class="dot" style="background:#ff78c8"></div> End</div>
</div>
""", unsafe_allow_html=True)

st.divider()

# ── Controls ───────────────────────────────────────────────────────────────────
col1, col2 = st.columns([2, 1])

with col1:
    maze_size = st.slider(
        "Maze size (n × n)",
        min_value=5,
        max_value=51,
        value=21,
        step=2,          # Keep it odd so carvePassages works correctly
        help="Odd numbers only — even values are auto-adjusted by the solver.",
    )

with col2:
    speed = st.selectbox("Animation speed", ["Fast", "Normal", "Slow"], index=0)

speed_map = {"Fast": (5, 30), "Normal": (2, 20), "Slow": (1, 12)}
frame_skip, fps = speed_map[speed]

st.markdown("<br>", unsafe_allow_html=True)
run = st.button("⚡ Generate & Solve")

# ── Core logic ─────────────────────────────────────────────────────────────────
SOLVER_BINARY = "./maze_solver"   # compiled binary name

if run:
    # ── 1. Check binary exists ─────────────────────────────────────────────────
    if not os.path.isfile(SOLVER_BINARY):
        st.markdown(f"""
        <div class="err-box">
        ❌ Binary <code>{SOLVER_BINARY}</code> not found.<br><br>
        Compile first:<br>
        <code>g++ -O2 -o maze_solver main.cpp maze.cpp solver.cpp</code>
        </div>
        """, unsafe_allow_html=True)
        st.stop()

    # ── 2. Run the C++ solver ──────────────────────────────────────────────────
    with st.spinner("🔧 Generating & solving maze..."):
        t0 = time.time()
        result = subprocess.run(
            [SOLVER_BINARY, str(maze_size)],
            capture_output=True,
            text=True,
        )
        cpp_time = time.time() - t0

    if result.returncode != 0:
        st.markdown(f"""
        <div class="err-box">
        ❌ Solver crashed:<br><pre>{result.stderr}</pre>
        </div>
        """, unsafe_allow_html=True)
        st.stop()

    # ── 3. Count steps for the stats bar ──────────────────────────────────────
    steps_count = 0
    backtracks  = 0
    if os.path.isfile("search_steps.txt"):
        with open("search_steps.txt") as f:
            for line in f:
                parts = line.strip().split()
                if parts:
                    steps_count += 1
                    if parts[0] == "BACK":
                        backtracks += 1

    path_len = 0
    if os.path.isfile("solved_maze.txt"):
        with open("solved_maze.txt") as f:
            for line in f:
                path_len += line.count("2")

    # ── 4. Stats bar ──────────────────────────────────────────────────────────
    st.markdown(f"""
    <div class="stats-bar">
        <div class="stat">
            <div class="stat-val">{maze_size}×{maze_size}</div>
            <div class="stat-lbl">Grid Size</div>
        </div>
        <div class="stat">
            <div class="stat-val">{steps_count}</div>
            <div class="stat-lbl">Steps Explored</div>
        </div>
        <div class="stat">
            <div class="stat-val">{backtracks}</div>
            <div class="stat-lbl">Backtracks</div>
        </div>
        <div class="stat">
            <div class="stat-val">{path_len}</div>
            <div class="stat-lbl">Path Length</div>
        </div>
        <div class="stat">
            <div class="stat-val">{cpp_time*1000:.0f}ms</div>
            <div class="stat-lbl">Solve Time</div>
        </div>
    </div>
    """, unsafe_allow_html=True)

    # ── 5. Generate the animated GIF ──────────────────────────────────────────
    with st.spinner("🎨 Rendering animation..."):
        gif_path = generate_gif(
            maze_file="maze.txt",
            steps_file="search_steps.txt",
            output_gif="maze_animation.gif",
            frame_skip=frame_skip,
            fps=fps,
            hold_last=40,
        )

    # ── 6. Display ─────────────────────────────────────────────────────────────
    st.success("✅ Done!")
    st.image(gif_path, caption=f"{maze_size}×{maze_size} maze — {steps_count} steps explored", use_container_width=True)

    # Download button
    with open(gif_path, "rb") as f:
        st.download_button(
            label="⬇️ Download GIF",
            data=f,
            file_name="maze_solution.gif",
            mime="image/gif",
        )

# ── Footer ─────────────────────────────────────────────────────────────────────
st.markdown("<br>", unsafe_allow_html=True)
st.markdown(
    "<p style='text-align:center;color:#444;font-size:0.75rem;font-family:Space Mono,monospace;'>"
    "built with C++ · Python · Streamlit</p>",
    unsafe_allow_html=True,
)