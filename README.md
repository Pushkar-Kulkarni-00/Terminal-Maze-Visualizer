# Terminal Maze Visualizer

Animated maze generator and solver written in C.  
Generates a perfect 31×31 maze and visualizes the solving process live in the terminal using ANSI escape codes.

## Features
- Depth-first maze generation
- Recursive backtracking solver
- Live terminal animation
- No external dependencies

## Build and Run
```
gcc maze.c -o maze
./maze
```
## How it Works
Maze is carved using recursive DFS, guaranteeing no loops.  
Solver marks every visited cell, backtracks on dead ends, and prints the path in real time.

## License
MIT
