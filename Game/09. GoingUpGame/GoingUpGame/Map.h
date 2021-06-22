#pragma once

//∏  ªÁ¿Ã¡Ó
#define mapXSize 40
#define mapYSize 23

extern char map[mapYSize][mapXSize];
extern char map2[mapYSize][mapXSize];
extern char map3[mapYSize][mapXSize];
extern char startMap[mapYSize][mapXSize + 1];
extern char descriptionMap[mapYSize][mapXSize + 1];
extern char gameOverMap[mapYSize][mapXSize + 1];

void start();
void description();
void showGameOver();
void drawMap(char map[mapYSize][mapXSize]);