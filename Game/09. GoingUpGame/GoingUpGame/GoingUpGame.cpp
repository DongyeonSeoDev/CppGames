#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

#define mapXSize 40
#define mapYSize 22

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

int playerX, playerY;

vector<int> enemyX, enemyY;
vector<int> itemX, itemY, itemData;

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

	for (int i = 0; i < (int)itemData.size(); i++)
	{
		gotoXY(itemX[i], itemY[i]);

		if (itemData[i] == 0)
		{
			cout << "0";
		}
		else
		{
			cout << "1";
		}
	}

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
	int minusSpeed = 0;

	bool isInvincibility = false;
	int startItemHeight = 0;

	playerX = 27;
	playerY = 20;

	clock_t start = clock();
	PlaySound(TEXT("Music.wav"), NULL, SND_ASYNC | SND_LOOP);

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

			if (playerY < 5) playerY = 5;
		}
		if (GetAsyncKeyState(VK_DOWN)) { //아래
			playerY++;

			if (playerY > 24) playerY = 24;
		}

		system("cls");

		cout << "높이: " << height << "m" << endl;
		cout << "스피드: " << speed << endl;

		cout << "시간: " << difftime(clock(), start) / CLOCKS_PER_SEC << "초" << endl;

		if (isInvincibility) cout << "무적시간" << endl;
		else cout << endl;

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
			enemyY.push_back(4);
		}

		if (rand() % 100 < 1)
		{
			itemX.push_back(rand() % 19 + 18);
			itemY.push_back(4);
			itemData.push_back(0);
		}

		if (rand() % 100 < 1)
		{
			itemX.push_back(rand() % 19 + 18);
			itemY.push_back(4);
			itemData.push_back(1);
		}

		for (int i = 0; i < (int)enemyX.size(); i++)
		{
			if (!isInvincibility && playerX == enemyX[i] && (playerY == enemyY[i] || playerY == enemyY[i] + 1))
			{
				system("cls");
				cout << "높이: " << height << "m" << endl;
				cout << "스피드: " << speed << endl;
				cout << "시간: " << difftime(clock(), start) / CLOCKS_PER_SEC << "초" << endl;
				gotoXY(10, 10);
				cout << "게임오버" << endl << endl << endl << endl << endl << endl << endl;
				Beep(988, 1000);
				system("pause");
				return 0;
			}

			enemyY[i]++;

			if (enemyY[i] > 24)
			{
				enemyX.erase(enemyX.begin() + i);
				enemyY.erase(enemyY.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < (int)itemData.size(); i++)
		{
			if (playerX == itemX[i] && (playerY == itemY[i] || playerY == itemY[i] + 1))
			{
				if (itemData[i] == 0)
				{
					minusSpeed += 1;
				}
				else
				{
					isInvincibility = true;
					startItemHeight = height;
				}

				itemX.erase(itemX.begin() + i);
				itemY.erase(itemY.begin() + i);
				itemData.erase(itemData.begin() + i);
				i--;
				continue;
			}

			itemY[i]++;

			if (itemY[i] > 24)
			{
				itemX.erase(itemX.begin() + i);
				itemY.erase(itemY.begin() + i);
				itemData.erase(itemData.begin() + i);
				i--;
			}
		}
		
		height++;

		speed = height / 100 - minusSpeed;
		creatEnemyProbability = height / 5;

		if (speed < 0) speed = 0;
		else if (speed > 5) speed = 5;

		if (creatEnemyProbability < 20) creatEnemyProbability = 20;
		else if (creatEnemyProbability > 100) creatEnemyProbability = 100;

		if (isInvincibility && height - startItemHeight >= 30)
		{
			isInvincibility = false;
		}

		Sleep(50 - speed * 10);
	}
}