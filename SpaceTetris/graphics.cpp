#include "graphics.h"
#include <vector>
#include <cmath>
#include <cstdlib> 


//---------------------------------------


struct Star {
    float x, y, brightness, speed; //star, twinkle, speed
};

struct Particle {
    float x, y;
    float lifetime; //particle (also stars) fade in and out time
};

// Static globals only inside graphics.cpp:
static Texture2D background;
static std::vector<Star> stars;
static std::vector<Particle> particles;
static float starTimer = 0.0f;

//colors for pieces
Color colors[8] = {
    {0, 0, 0, 255},
    {255, 182, 193, 255},  // pastel pink
    {173, 216, 230, 255},  // light blue
    {152, 251, 152, 255},  // light green
    {221, 160, 221, 255},  // pastel purple
    {240, 230, 140, 255},  // pastel yellow
    {255, 160, 122, 255},  // pastel orange
    {176, 224, 230, 255}   // pastel cyan
};

void InitStars(int count) {
    stars.clear();
    for (int i = 0; i < count; i++) {
        stars.push_back({
            static_cast<float>(rand() % 400),
            static_cast<float>(rand() % 600),
            static_cast<float>(rand() % 100) / 100.0f,
            0.2f + (static_cast<float>(rand() % 100) / 500.0f)
        });
    }
}

void InitGraphics() {
    background = LoadTexture("assets/Space.jpeg"); //loads background
    InitStars(50); //loads star
    particles.clear(); //clears particles 
}

//loaded graphic resources
void UnloadGraphics() {
    UnloadTexture(background);
}

//makes color pop
Color CycleColor(Color baseColor, float time) {
    float glow = 0.5f + 0.5f * sin(time * 5);
    return (Color){
        static_cast<unsigned char>(baseColor.r * glow),
        static_cast<unsigned char>(baseColor.g * glow),
        static_cast<unsigned char>(baseColor.b * glow),
        baseColor.a
    };
}

//spawn particles

void SpawnParticles(int lineY, Vector2 offset, int blockSize) {
    for (int i = 0; i < 10; i++) {
        particles.push_back({
            offset.x + static_cast<float>(rand() % (blockSize * 10)),
            offset.y + lineY * blockSize + static_cast<float>(rand() % blockSize),
            0.5f + (static_cast<float>(rand() % 100) / 200.0f)
        });
    }
}

void DrawBackground() {
    float scaleX = 400.0f / background.width;
    float scaleY = 600.0f / background.height;
    DrawTextureEx(background, (Vector2){0, 0}, 0, scaleX, WHITE);


    //star twinkle effect 
    starTimer += GetFrameTime();
    for (auto& s : stars) {
        s.brightness += s.speed * GetFrameTime();
        if (s.brightness > 1.0f) s.brightness = 0.5f;
        if (s.brightness < 0.5f) s.brightness = 1.0f;
    }
    for (auto& s : stars) {
        //making stars white pixels
        DrawPixel(static_cast<int>(s.x), static_cast<int>(s.y), Fade(WHITE, s.brightness));
    }
}

void DrawField(const int field[20][10], int blockSize, const Vector2& offset) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[i][j]) {
                DrawRectangle(offset.x + j * blockSize, offset.y + i * blockSize, blockSize - 2, blockSize - 2, colors[field[i][j]]);
            }
        }
    }
}

//makes pieces glow just like the real tetris game does when being placed
void DrawCurrentPiece(const std::vector<Point>& a, int blockSize, const Vector2& offset, const Color colors[], int color) {
    float glowTime = GetTime();
    for (int i = 0; i < 4; i++) {
        Color glowCol = CycleColor(colors[color], glowTime);
        DrawRectangle(offset.x + a[i].x * blockSize - 3, offset.y + a[i].y * blockSize - 3, blockSize + 6, blockSize + 6, Fade(glowCol, 0.3f));
    }
    for (int i = 0; i < 4; i++) {
        DrawRectangle(offset.x + a[i].x * blockSize, offset.y + a[i].y * blockSize, blockSize - 2, blockSize - 2, colors[color]);
    }
}

void DrawParticles() {
    for (size_t i = 0; i < particles.size();) {
        particles[i].lifetime -= GetFrameTime();
        if (particles[i].lifetime <= 0) {
            particles.erase(particles.begin() + i);
        } else {
            DrawCircleV({particles[i].x, particles[i].y}, 2, Fade(WHITE, particles[i].lifetime * 2));
            i++;
        }
    }
}

//score table and highscore table
void DrawScore(int score, int highScore) {
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
    DrawText(TextFormat("High Score: %d", highScore), 10, 35, 20, WHITE);
}

//fade in game over screen
void DrawGameOverScreen(int screenWidth, int screenHeight) {
    static float gameOverAlpha = 0.0f;
    gameOverAlpha += GetFrameTime();
    if (gameOverAlpha > 1.0f) gameOverAlpha = 1.0f;

    Color pastelPink = {255, 182, 193, static_cast<unsigned char>(gameOverAlpha * 255)};
    DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, pastelPink);
    DrawText("Press SPACE to Restart", screenWidth / 2 - MeasureText("Press SPACE to Restart", 20) / 2, screenHeight / 2 + 30, 20, Fade(WHITE, gameOverAlpha));
}
