#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
using namespace std;

#define mapXSize 40
#define mapYSize 22

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

int playerX, playerY;

vector<int> enemyX, enemyY;

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

	for (int i = 0; i < (int)enemyX.size(); i++)
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
	int speed = 0;
	int creatEnemyProbability = 10;

	playerX = 27;
	playerY = 20;

	while (true)
	{
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

		system("cls");

		cout << "현재 높이: " << height << endl;
		cout << "현재 스피드: " << speed << " t: " << creatEnemyProbability << endl;

		if (height % 2 == 0)
		{
			drawMap(map);
		}
		else
		{
			drawMap(map2);
		}

		if (rand() % 100 < creatEnemyProbability)
		{
			enemyX.push_back(rand() % 19 + 18);
			enemyY.push_back(2);
		}

		for (int i = 0; i < (int)enemyX.size(); i++)
		{
			if (playerX == enemyX[i] && (playerY == enemyY[i] || playerY == enemyY[i] + 1))
			{
				system("cls");
				cout << "현재 높이: " << height << endl;
				cout << "현재 스피드: " << speed << " t: " << creatEnemyProbability << endl;
				gotoXY(10, 10);
				cout << "게임오버" << endl << endl << endl << endl << endl << endl << endl;
				Sleep(1000);
				system("pause");
				return 0;
			}

			enemyY[i]++;

			if (enemyY[i] > 21)
			{
				enemyX.erase(enemyX.begin() + i);
				enemyY.erase(enemyY.begin() + i);
				i--;
			}
		}
		
		height++;

		speed = height / 100;
		creatEnemyProbability = height / 10;

		if (speed > 10) speed = 10;

		if (creatEnemyProbability < 20) creatEnemyProbability = 20;
		else if (creatEnemyProbability > 100) creatEnemyProbability = 100;

		Sleep(100 - speed * 10);
	}
}