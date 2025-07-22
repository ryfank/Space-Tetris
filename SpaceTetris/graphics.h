#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "raylib.h"
#include <vector>
#include "types.h" 

//---------------------------------------

void InitGraphics();
void UnloadGraphics();

extern Color colors[8];

void DrawBackground();
void DrawField(const int field[20][10], int blockSize, const Vector2& offset);
void DrawCurrentPiece(const std::vector<Point>& a, int blockSize, const Vector2& offset, const Color colors[], int color);
void DrawParticles();
void DrawScore(int score, int highScore);
void DrawGameOverScreen(int screenWidth, int screenHeight);

//---------------------------------------

#endif // GRAPHICS_H
