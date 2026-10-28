 # 🕹️ Terminal Tetris in C++
    
  A fast, terminal-based implementation of the classic Tetris game built from scratch in C++ using the `ncurses` library for Linux.
    
    
  ## Features
    
  - **Classic Gameplay**: All 7 standard Tetrominoes (I, O, T, L, S, J, Z) with complete 4-state rotations.
    - **Flicker-Free Rendering**: Smooth double-buffered terminal rendering via `ncurses`.
    - **Decoupled Game Loop**: 50 FPS input responsiveness decoupled from gravity fall speed.
    - **Universal Collision System**: Precise boundary checks, obstacle detection, and line clearing.
    - **Dynamic Difficulty**: Fall speed automatically accelerates every 3 lines cleared.
    - **Live Scoreboard**: Dedicated side panel tracking current score and cleared lines.
    
    ---
    
    ## Controls
    
    | Key | Action |
    | :--- | :--- |
    | `←` / `KEY_LEFT` | Move Left |
    | `→` / `KEY_RIGHT` | Move Right |
    | `↓` / `KEY_DOWN` | Soft Drop (Accelerate downward) |
    | `↑` / `KEY_UP` | Rotate Piece (Clockwise) |
    | `Q` / `q` | Quit Game Safely |
    
    ---
    
    ##  Requirements & Installation
    
    ### 1. Prerequisites (Ubuntu / Linux Mint / Debian)
    Make sure you have `g++` and the `ncurses` development library installed:
    
    \`\`\`bash
    sudo apt update
    sudo apt install g++ libncurses-dev
    \`\`\`
    
    ### 2. Clone the Repository
    \`\`\`bash
    git clone https://github.com/kyaramshivaprasad37/Tetris-Game.git
    cd Tetris-Game
    \`\`\`
    
    ### 3. Compile & Run
    Compile using `g++` with the `-lncurses` flag:

    \`\`\`bash
    g++ -Wall -Wextra main.cpp -lncurses -o tetris
    ./tetris
    \`\`\`

    ---

    ## Engineering & Architecture

    - **State Representation**: The board is modeled as an in-memory 2D grid, while all 7 tetrominoes and their 4 rotation states are precomputed
    ￹into a 4D matrix (`Pieces[7][4][4][4]`) for $O(1)$ lookup time.
    - **Unified Collision Checking (`canPieceFit`)**: A single collision algorithm verifies boundaries, floor contact, and stacked obstacles across
    ￹movement and gravity.
    - **Dual-Window Interface**: Built using two independent `ncurses` window buffers (`win` for the playfield and `scoreBoard` for stats).

    ---

    ## Future Roadmap

    - [ ] Add `ncurses` color pairs for authentic piece colors.
    - [ ] Safe rotation / wall kicks.
    - [ ] "Next Piece" preview box inside the scoreboard.
    - [ ] Persistent high-score saving to disk.

    ---

    ## 👤 Author
    Developed by **Shivaprasad**
