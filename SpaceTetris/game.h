#ifndef GAME_H
#define GAME_H

#include <vector>
#include "raylib.h"
#include "types.h"  

//---------------------------------------

//For board size
extern const int boardWidth;
extern const int boardHeight;

//shape data
extern int shapes[7][4];

// Game state variables
extern std::vector<Point> a; // piece blocks
extern int field[20][10]; //Board matrix
extern int color; //Current piece color index
extern bool gameOver;

extern int score;
extern int highScore;

// important Functions
void InitGame();
bool CheckCollision(const std::vector<Point>& piece);
void RestartGame();
void UpdateGame(float deltaTime, Sound blip);

//---------------------------------------

#endif 

