#include "game.h"
#include <cstdlib>
#include <ctime>


//---------------------------------------

std::vector<Point> a(4);
int field[20][10] = {0};
int color;
int score = 0;
int highScore = 0;
bool gameOver = false;

int shapes[7][4] = {
    {1,3,5,7}, {2,4,5,7}, {3,5,4,6},
    {3,5,4,7}, {2,3,5,7}, {3,5,7,6}, {2,3,4,5}
};

//timer and speed
static float timer = 0.0f;
static float delay = 0.3f;

// collision check
bool CheckCollision(const std::vector<Point>& a);


//---------------------------------------


//start game, piece starts falling
void InitGame() {
    color = 1 + rand() % 7; // random shape
    int n = rand() % 7; //random colour 
    for (int i = 0; i < 4; i++) {
        a[i].x = shapes[n][i] % 2 + 10 / 2 - 1;
        a[i].y = shapes[n][i] / 2;
    }
    // Reset field and score if starting fresh
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 10; j++)
            field[i][j] = 0;
    score = 0;
    gameOver = false;
    timer = 0.0f;
    delay = 0.3f;
}

//game updates each frame

void UpdateGame(float deltaTime, Sound blip) {
    if (gameOver) return; // if game over, update stops

    timer += deltaTime;

    int dx = 0;
    bool rotate = false;

    if (IsKeyPressed(KEY_RIGHT)) dx = 1;
    if (IsKeyPressed(KEY_LEFT)) dx = -1;
    if (IsKeyPressed(KEY_UP)) rotate = true;
    if (IsKeyDown(KEY_DOWN)) delay = 0.05f; 
    else delay = 0.3f;

    // Move horizontally
    std::vector<Point> b = a; // backup
    for (int i = 0; i < 4; i++) a[i].x += dx;
    if (CheckCollision(a)) a = b;

    // Rotates  pieces 
    if (rotate) {
        b = a;
        Point p = a[1]; // center of rotation
        for (int i = 0; i < 4; i++) {
            int x = a[i].y - p.y;
            int y = a[i].x - p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
        }
        if (CheckCollision(a)) a = b;
    }

    // Move down with timer
    if (timer > delay) {
        b = a;
        for (int i = 0; i < 4; i++) a[i].y += 1;

        if (CheckCollision(a)) {
            //place a piece into field
            for (int i = 0; i < 4; i++) {
                field[b[i].y][b[i].x] = color;
            }
            PlaySound(blip);

            //Spawn new piece
            int n = rand() % 7;
            color = 1 + rand() % 7;
            for (int i = 0; i < 4; i++) {
                a[i].x = shapes[n][i] % 2 + 10 / 2 - 1;
                a[i].y = shapes[n][i] / 2;
            }

            //check if game over
            for (int i = 0; i < 4; i++) {
                if (field[a[i].y][a[i].x]) {
                    gameOver = true;
                    break;
                }
            }

            timer = 0; // resets gravity timer
        } else {
            timer = 0; // if no collisons, it can keep falling
        }
    }

    //clears completed lines
    int k = 19;
    for (int i = 19; i >= 0; i--) {
        int count = 0;
        for (int j = 0; j < 10; j++) {
            if (field[i][j]) count++;
            field[k][j] = field[i][j];
        }
        if (count < 10) k--;
        else {
            score += 100;
            if (score > highScore) highScore = score;
            // Can spawn particles 
        }
    }
}

//---------------------------------------

//reinitializing to restart

void RestartGame() {
    InitGame();
}

//to check if pieces collide with wall/floor/existing blocks
bool CheckCollision(const std::vector<Point>& a) {
    for (auto& p : a) {
        if (p.x < 0 || p.x >= 10 || p.y >= 20) return true;
        if (p.y >= 0 && field[p.y][p.x]) return true;
    }
    return false;
}
