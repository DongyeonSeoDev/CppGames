#pragma once

#define MAP_X  4
#define MAP_Y  2

#define KEY_DIRECTION  224
#define KEY_LEFT       75
#define KEY_RIGHT	   77
#define KEY_UP         72
#define KEY_DOWN       80

#define FNAME "score"

extern int board[4][4];
extern bool bGameOver;

void setConsoleView();

void start();

void initData();

void initDraw();
void drawGame();

void createNumber();
bool moveNumber(int sX, int sY, int tX, int tY);

void getKey();

void checkGameOver();

void showScore();

void Save(int highScore);
int Load();