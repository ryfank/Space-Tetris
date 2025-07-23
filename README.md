# Space-Tetris
Made with raylib

# How to Play :

  - Up arrow key for rotating the pieces
  - down arrow key for faster landing
  - left arrow to move the piece left
  - right arrow to move the piece right
  - Space bar will restart the game if player loses

# Installation
**When downloading, open terminal and use these commands to run and compile the game**
### macOS
clang++ main.cpp game.cpp graphics.cpp -o SpaceTetris -lraylib -framework OpenGL -framework Cocoa
-framework IOKit -framework CoreAudio -framework CoreVideo -pthread -std=c++17

./SpaceTetris


### Windows
g++ main.cpp game.cpp graphics.cpp -o SpaceTetris.exe -lraylib -lopengl32 -lgdi32 -lwinmm
./SpaceTetris.exe

just copy and paste those command in terminal.

# Game Preview

![Alt Text](https://github.com/user-attachments/assets/a519c5e7-ef65-4e54-a5a3-66d4cfb57df6)
