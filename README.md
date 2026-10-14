# Blackout Atlas — Campus Network Failure & Recovery Simulator

**Blackout Atlas** is a Data Structures and Algorithms (DSA) campus network simulator that models network partitions and calculates minimum-cost recovery topologies using Graph Algorithms.

## Features
- **Graph Representation**: Undirected weighted graph representing 6 campus buildings and 8 transmission connections.
- **BFS Network Diagnosis**: Breadth-First Search rooted at Main Block (0) to evaluate full campus reachability and detect partitions.
- **Prim's Algorithm (Minimum Spanning Tree)**: Identifies the optimal subset of working and repairable connections to reconnect the entire campus at minimum additional repair cost.
- **Interactive Visual Simulator (`index.html` / `visualizer.html`)**:
  - Frosted Blueprint theme with ambient glow canvas and dark mode toggle.
  - Interactive link operations: mark connections as *Working*, *Failed (Repairable)*, or *Unavailable*.
  - Step-by-step playback controller with speed control (0.5x, 1.0x, 2.0x).
  - 8-Step Viva Demo Scenario.
  - Interactive Prim Recovery Action Bar to restore recommended links and verify full network recovery.
- **C++ Console Engine (`main.cpp`)**: Clean, comment-free C++17 implementation designed for academic viva evaluation.

---

## Campus Topology
### Buildings (Vertices)
- **0**: Main Block (Central Server & Gateway)
- **1**: Library
- **2**: Computer Lab
- **3**: Hostel
- **4**: Administration
- **5**: Medical Centre

### Connections & Repair Costs (Edges)
1. Main Block — Library: Cost 4
2. Main Block — Administration: Cost 3
3. Library — Computer Lab: Cost 2
4. Library — Administration: Cost 5
5. Computer Lab — Hostel: Cost 4
6. Hostel — Medical Centre: Cost 3
7. Administration — Medical Centre: Cost 6
8. Computer Lab — Administration: Cost 2

---

## Deployment on Render
This project is configured for **Render Static Sites**:
- **Build Command**: *(leave blank)*
- **Publish Directory**: `.` (Root)
- **Routes**: Automatically serves `index.html`.
