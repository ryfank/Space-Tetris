#include "raylib.h"
#include "game.h"
#include "graphics.h"
#include <ctime>


//------------------------------------------


int main() {
    srand(time(0));
    InitWindow(400, 600, "Space Tetris");
    InitAudioDevice();

    InitGraphics();
    InitGame();

    //load music and sound effects
    Music music = LoadMusicStream("assets/Music.mp3");
    Sound blip = LoadSound("assets/Blip.wav");
    PlayMusicStream(music);

    Vector2 offset = {50, 50};
    const int blockSize = 30;


    SetTargetFPS(60);


    //game loops until user closes window
    while (!WindowShouldClose()) {
        UpdateMusicStream(music);

        UpdateGame(GetFrameTime(), blip);

        //if gameover, press space to play again
        if (gameOver && IsKeyPressed(KEY_SPACE)) {
            RestartGame();
            PlayMusicStream(music);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        //clear background for the space.jpeg

        DrawBackground();
        DrawField(field, blockSize, offset);
        DrawCurrentPiece(a, blockSize, offset, colors, color);
        DrawParticles(); //for the stars in the background
        DrawScore(score, highScore); //puts highscore

        if (gameOver) DrawGameOverScreen(GetScreenWidth(), GetScreenHeight());

        EndDrawing();
    }

    UnloadMusicStream(music);
    UnloadSound(blip);
    UnloadGraphics();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
