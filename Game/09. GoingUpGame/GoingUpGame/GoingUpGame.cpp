﻿#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

#define mapXSize 40
#define mapYSize 22

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

int playerX, playerY;

const int enemyCount = 10;

int enemyX[enemyCount], enemyY[enemyCount]; //enemy 여러개 만들기

char map[mapYSize][mapXSize] =
{
	"---------------------------------------",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"---------------------------------------"
};

char map2[mapYSize][mapXSize] =
{
	"---------------------------------------",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"@                                     @",
	"*                                     *",
	"---------------------------------------",
};

void gotoXY(int x, int y)
{
	COORD Cur;
	Cur.X = x * 2;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void setcursor(bool i, DWORD size) 
{
	CONSOLE_CURSOR_INFO c = { 0 };
	c.dwSize = size;
	c.bVisible = i;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

void drawMap(char map[mapYSize][mapXSize])
{
	for (int i = 0; i < mapYSize; i++)
	{
		cout << "                                   ";

		for (int j = 0; j < mapXSize; j++)
		{
			cout << map[i][j];
		}

		cout << endl;
	}

	cout << endl << endl << endl;

	gotoXY(playerX, playerY);
	cout << "&";

	for (int i = 0; i < enemyCount; i++)
	{
		gotoXY(enemyX[i], enemyY[i]);
		cout << "%";
	}
}

int main()
{
	system("title UP! 게임");
	setcursor(false, 1);

	srand((unsigned)time(NULL));

	int height = 0;

	playerX = 27;
	playerY = 20;

	for (int i = 0; i < enemyCount; i++)
	{
		enemyX[i] = rand() % 19 + 18;
		enemyY[i] = rand() % 4 + 2;
	}

	while (true)
	{
		system("cls");

		cout << "현재 높이: " << height << "m" << endl;

		if (GetAsyncKeyState(VK_LEFT)) { //왼쪽
			playerX--;

			if (playerX < 18) playerX = 18;
		}
		if (GetAsyncKeyState(VK_RIGHT)) { //오른쪽
			playerX++;

			if (playerX > 36) playerX = 36;
		}
		if (GetAsyncKeyState(VK_UP)) { //위
			playerY--;
			
			if (playerY < 2) playerY = 2;
		}
		if (GetAsyncKeyState(VK_DOWN)) { //아래
			playerY++;

			if (playerY > 21) playerY = 21;
		}

		for (int i = 0; i < enemyCount; i++)
		{
			if (playerX == enemyX[i] && (playerY == enemyY[i] || playerY == enemyY[i] + 1))
			{
				gotoXY(10, 10);
				cout << "게임오버" << endl;
				return 0;
			}

			enemyY[i]++;

			if (enemyY[i] > 21)
			{
				enemyX[i] = rand() % 19 + 18;
				enemyY[i] = rand() % 4 + 2;
			}
		}

		if (height % 2 == 0)
		{
			drawMap(map);
		}
		else
		{
			drawMap(map2);
		}
		height++;

		Sleep(10);
	}
}