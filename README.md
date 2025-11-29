# maze-runner-c

A terminal-based maze generator, interactive maze game, and auto-solver written in C.  
The program generates a perfect maze using randomized DFS carving, places collectibles, and supports both manual play (arrow keys) and an automated solver with visual backtracking.

## Features
- Randomized DFS maze generation  
- Real-time terminal rendering with ANSI escape sequences  
- Collectibles that increase score  
- Auto-solver using depth-first search with path visualization  
- Manual player mode with arrow-key controls  
- Single-file C implementation  

## Build & Run

### Linux / macOS
```bash
gcc main.c -o maze -O2
./maze
```

### Windows (MinGW)
```bash
gcc main.c -o maze.exe
maze.exe
```

(Note: The program uses conio.h for key input. MSVC users must replace getch().)

## Controls (Single-Player Mode)
- Up Arrow = Move up  
- Down Arrow = Move down  
- Right Arrow = Move right  
- Left Arrow = Move left  
- # = Trigger auto-solver from current position  

## How It Works

### Maze Generation
- The grid starts fully closed (all walls).  
- A recursive DFS carves paths by jumping two cells at a time.  
- Some carved cells become collectibles worth +5 points.  
- Entrance = top row, Exit = bottom row.

### Rendering
- Uses ANSI escape codes for:  
  - Cursor movement  
  - Coloring  
  - Live incremental updates  

### Solver
- DFS-based pathfinder with backtracking.  
- Visually marks visited nodes.  
- Updates score dynamically.

## Project Structure
maze-runner-c/
├── main.c
└── README.md

## Possible Future Enhancements
- ncurses-based rendering  
- Adjustable maze sizes  
- Timer or difficulty system  
- Seed-based reproducible mazes  
- GIF demos and screenshots  

## License
MIT License
