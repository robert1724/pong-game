# pong-game
OpenGL 2D Pong with a customizable paddle-building phase using drag-and-drop, AABB collision detection, DFS connectivity validation and score-based win/loss conditions with animations

Spaceship Editor
  - Players build their ship on a 9×17 grid using drag-and-drop before starting the game.
  - Players can build the ship however they want but it is recommended to stay on a horizontal line
    
Block Types
  - Solid (marked with 1 in implementation) = Basic 1×1 gray block 
  - Bumper (marked with 2 in implementation) = Gray block + yellow semicircle on top (3 columns wide)
  - Cannon (marked with 3 in implementation) = Gray block + barrel + semicircle base + trapezoid tip

Editor Mechanics
  - **Left click + drag** from the left panel to place a block on the grid
  - **Right click** on a grid cell to remove a block
  - **Green squares** in the top bar show remaining block slots (max 10)
  - **Start button**: green when ship is valid, red when invalid
    
Validation (DFS-based)
  - The editor checks the ship before allowing the game to start:
  - At least 1 block placed
  - All blocks must be **connected** (verified via DFS flood-fill)
  - No blocks above cannons or bumpers
  - No bumpers adjacent to each other
  - No cannon placed within 1 cell of a bumper
    
Pong Game
  - Two mirrored copies of the custom ship serve as paddles on opposite sides of the field.
    
Controls
  - Player 1 (Left) uses W to move the ship upwards and S to move the ship downwards
  - Player 2 (Right) uses ↑ to move the ship upwards and ↓ to move the ship downwards

Physics
  - Ball reflection on paddle uses angle-based deflection:
      - angle = (ball_y - paddle_center) / (paddle_height / 2) vx = speed * cos(angle) vy = speed * sin(angle)
  - Wall bounce: vertical speed inverts on top/bottom walls
  - Goal detection: ball past left/right edge scores a point for the opponent
    
Features
  - **Score system** — first to **5 points** wins (displayed as colored circles)
  - **Bumper speed boost** — ball speed increases by **10%** on bumper contact
  - **Paddle animation** — 1.5× vertical scale animation on collision (0.25s duration)
  - **Win screen** — blue or red fullscreen for 3 seconds, then auto-close
