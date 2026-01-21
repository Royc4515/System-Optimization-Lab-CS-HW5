# 🚀 System-Optimization-Lab-CS-HW5

![Language: C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Language: Python](https://img.shields.io/badge/Language-Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Language: Bash](https://img.shields.io/badge/Language-Bash-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white)
![Focus: Performance](https://img.shields.io/badge/Focus-Performance-FF4500?style=for-the-badge)
![Status: Complete](https://img.shields.io/badge/Status-Complete-success?style=for-the-badge)

Comprehensive computer architecture project focusing on **system-level optimization**, **multiprocessing**, and **algorithmic problem solving**.

---

## 📂 Project Structure

```text
System-Optimization-Lab-CS-HW5/
├── 🚀 Part 1/                  # Performance Optimization
│   ├── main.c                  # Entry point (Driver)
│   ├── vowel_counting.c        # [OPTIMIZED] Forking, LUTs, Unrolling
│   ├── run_stats.sh            # Benchmark script (Original vs Optimized)
│   └── create-buffer.py        # Test data generator
│
└── 🧠 Part 2/                  # Algorithms & Interview Prep
    ├── 2A/                     # Manual Optimization
    │   ├── buy_and_sell.c      # Best Time to Buy/Sell Stock (Optimized C)
    │   └── buy_and_sell.py     # Reference Python implementation
    └── 2B/                     # AI & Vibe Coding
        ├── rotting_fruit.py    # Rotting Oranges (AI Generated)
        └── visualization.py    # BFS Visualization Tool
```

---

## ⚡ Part 1: Performance Optimization

**Goal**: Optimize legacy C code processing large memory buffers.
**Result**: Reduced execution time from **6.2s** to **0.51s** (~12x Speedup).

### 🏆 Performance Metrics

| Metric | Original (Baseline) | Optimized (Final) | Improvement |
| :--- | :--- | :--- | :--- |
| **Execution Time** | ~6.20s | **~0.51s** | **12.1x Faster** 🚀 |
| **Method calls** | Standard | Branchless / Inlined | Reduced Overhead |
| **Concurrency** | Single Thread | Multi-Process (`fork`) | Parallelized |

### 🛠️ Technical Challenges & Optimizations
The solution had to strictly adhere to legacy constraints (no `-O2/3`, no threads, no SIMD).

*   **Process-Level Parallelism**: Used `fork()` to offload heavy Pi-pattern matching to a separate process, maximizing CPU core usage without threads.
*   **Lookup Tables (LUT)**: Replaced 50+ conditional branches with O(1) memory access using a 256-entry table.
*   **Loop Unrolling**: Manually unrolled critical loops (16x stride) to minimize branch overhead and improve pipelining.
*   **Branchless Logic**: Implemented bitwise counting mechanisms to avoid pipeline flushes from branch misprediction.
*   **Register Hinting**: Strategically used `register` variables to optimize memory access patterns.

### 💻 How to Run
```bash
# 1. Generate Test Data
python3 create-buffer.py 100000000 > input.txt

# 2. Run Benchmark
./run_stats.sh both
```

---

## 🧠 Part 2: Algorithmic Problems

### 2A: Interview Optimization
**Problem**: [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
*   **Approach**: Manual low-level optimization in C.
*   **Techniques**: Pointer arithmetic, unrolled traversals, and branchless min/max logic to solve the classic algorithm faster than standard implementations.

### 2B: "Vibe Coding" (AI Assisted)
**Problem**: [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
*   **Approach**: Fully AI-driven development.
*   **Outcome**: A correct Python solution using BFS plus a **custom visualization tool** to watch the "rot" spread across the grid step-by-step.

---

## 🎓 Skills Learned & Applied

### 🖥️ System Programming
*   **Multiprocessing**: Gained deep understanding of `fork()`, process memory isolation, and OS scheduling.
*   **Memory Architecture**: Analyzed cache locality and designed data access patterns to minimize cache misses (`stride=1000` analysis).
*   **Low-Level C**: Mastered bitwise manipulation, pointers, and manual compiler optimization techniques.

### 📐 Algorithmic Design
*   **Complexity Analysis**: Reduced Time Complexity for critical paths.
*   **Graph Algorithms**: Applied BFS for grid simulations (Rotting Oranges).
*   **Greedy Patterns**: Solved optimization problems (Stock Trading).

### 🛠️ Modern Tooling
*   **Automation**: Bash scripting for rigorous performance benchmarking.
*   **AI Collaboration**: Leveraging LLMs for rapid prototyping and visualization tools.
