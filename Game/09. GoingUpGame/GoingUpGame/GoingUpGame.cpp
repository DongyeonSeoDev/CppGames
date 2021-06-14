#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

#define mapXSize 40
#define mapYSize 23

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWV 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define FNAME "score"

int playerX, playerY;

vector<int> enemyX, enemyY;
vector<int> itemX, itemY, itemData;

struct Score
{
	int score;
};

Score score;

int bestScore = 0;

char map[mapYSize][mapXSize] =
{
	"---------------------------------------",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"---------------------------------------"
};

char map2[mapYSize][mapXSize] =
{
	"---------------------------------------",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"---------------------------------------"
};

char map3[mapYSize][mapXSize] =
{
	"---------------------------------------",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"●                                   ●",
	"▼                                   ▼",
	"★                                   ★",
	"---------------------------------------"
};

char startMap[mapYSize][mapXSize + 1] =
{
	"■■■■■■■■■■■■■■■■■■■■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■              UP! 게임              ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■   설명을 보려면 Q키를 눌러주세요   ■",
	"■                                    ■",
	"■    시작하려면 S키를 눌러주세요     ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■■■■■■■■■■■■■■■■■■■■"
};

char descriptionMap[mapYSize][mapXSize + 1] =
{
	"■■■■■■■■■■■■■■■■■■■■",
	"■                                    ■",
	"■                설명                ■",
	"■                                    ■",
	"■   ▲: 플레이어   ♥: 무적 아이템   ■",
	"■   ◆: 적   ♣: 스피드 다운 아이템  ■",
	"■                                    ■",
	"■    키보드 화살표키로 플레이어를    ■",
	"■           움직일 수 있다.          ■",
	"■                                    ■",
	"■     적에 닿으면 게임오버 된다.     ■",
	"■                                    ■",
	"■    무적 아이템을 먹으면 잠시동안   ■",
	"■            무적이 된다.            ■",
	"■                                    ■",
	"■     스피드 다운 아이템을 먹으면    ■",
	"■         스피드가 느려진다.         ■",
	"■                                    ■",
	"■   최대한 높이 올라가는 게임이다.   ■",
	"■                                    ■",
	"■    돌아가려면 X키를 눌러주세요     ■",
	"■                                    ■",
	"■■■■■■■■■■■■■■■■■■■■"
};

char gameOverMap[mapYSize][mapXSize + 1] =
{
	"■■■■■■■■■■■■■■■■■■■■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■              게임오버              ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■    종료하려면 Q키를 눌러주세요     ■",
	"■                                    ■",
	"■                                    ■",
	"■                                    ■",
	"■■■■■■■■■■■■■■■■■■■■"
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

void scolor(unsigned short text = 15, unsigned short back = 0)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void Save()
{
	score.score = bestScore;

	FILE* fp = 0;
	fopen_s(&fp, FNAME, "w");

	if (fp)
	{
		fwrite(&score, sizeof(Score), 1, fp);
		fclose(fp);
	}
}

void Load()
{
	FILE* fp = 0;
	fopen_s(&fp, FNAME, "r");
	if (fp)
	{
		fread(&score, sizeof(Score), 1, fp);
		fclose(fp);

		bestScore = score.score;
	}
}

void start()
{
	system("cls");

	scolor(YELLOW);
	cout << endl << endl << endl << endl;
	for (int i = 0; i < mapYSize; i++)
	{
		cout << "                                   ";

		for (int j = 0; j < mapXSize + 1; j++)
		{
			cout << startMap[i][j];
		}

		cout << endl;
	}

	gotoXY(23, 12);
	scolor(GREEN);
	cout << "최고 높이: " << bestScore << "m" << endl;
	scolor();
}

void description()
{
	system("cls");
	
	scolor(LIGHTGREEN);
	cout << endl << endl << endl << endl;
	for (int i = 0; i < mapYSize; i++)
	{
		cout << "                                   ";

		for (int j = 0; j < mapXSize + 1; j++)
		{
			cout << descriptionMap[i][j];
		}

		cout << endl;
	}
	scolor();
}

void gameOver()
{
	system("cls");

	scolor(LIGHTRED);
	cout << endl << endl << endl << endl;
	for (int i = 0; i < mapYSize; i++)
	{
		cout << "                                   ";

		for (int j = 0; j < mapXSize + 1; j++)
		{
			cout << gameOverMap[i][j];
		}

		cout << endl;
	}
	scolor();
}

void drawMap(char map[mapYSize][mapXSize])
{
	scolor(YELLOW);
	for (int i = 0; i < mapYSize; i++)
	{
		cout << "                                   ";

		for (int j = 0; j < mapXSize; j++)
		{
			cout << map[i][j];
		}

		cout << endl;
	}

	scolor(LIGHTCYAN);
	gotoXY(playerX, playerY);
	cout << "▲";

	for (int i = 0; i < (int)itemData.size(); i++)
	{
		gotoXY(itemX[i], itemY[i]);

		if (itemData[i] == 0)
		{
			scolor(LIGHTBLUE);
			cout << "♣";
		}
		else
		{
			scolor(LIGHTGREEN);
			cout << "♥";
		}
	}

	for (int i = 0; i < (int)enemyX.size(); i++)
	{
		gotoXY(enemyX[i], enemyY[i]);
		scolor(LIGHTRED);
		cout << "◆";
	}

	scolor();
}

int main()
{
	Load();

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
	playerY = 21;

	start();

	while (true)
	{
		char ch = _getch();
		ch = tolower(ch);

		if (ch == 's')
		{
			Beep(784, 200);
			break;
		}
		else if (ch == 'q')
		{
			Beep(698, 200);
			description();

			while (true)
			{
				char ch = _getch();
				ch = tolower(ch);

				if (ch == 'x')
				{
					Beep(698, 200);
					start();
					break;
				}
			}
		}
	}

	clock_t start = clock();
	PlaySound(TEXT("Music.wav"), NULL, SND_ASYNC | SND_LOOP);

	while (true)
	{
		if (GetAsyncKeyState(VK_LEFT)) { //왼쪽
			playerX--;

			if (playerX < 19) playerX = 19;
		}
		if (GetAsyncKeyState(VK_RIGHT)) { //오른쪽
			playerX++;

			if (playerX > 35) playerX = 35;
		}
		if (GetAsyncKeyState(VK_UP)) { //위
			playerY--;

			if (playerY < 5) playerY = 5;
		}
		if (GetAsyncKeyState(VK_DOWN)) { //아래
			playerY++;

			if (playerY > 25) playerY = 25;
		}

		system("cls");

		scolor(GREEN);
		cout << "높이: " << height << "m" << endl;
		scolor(YELLOW);
		cout << "스피드: " << speed << endl;
		scolor(LIGHTBLUE);
		cout << "시간: " << difftime(clock(), start) / CLOCKS_PER_SEC << "초" << endl;
		scolor();

		if (isInvincibility) cout << "무적시간" << endl;
		else cout << endl;

		if (height % 3 == 0)
		{
			drawMap(map);
		}
		else if (height % 3 == 1)
		{
			drawMap(map2);
		}
		else
		{
			drawMap(map3);
		}

		if (rand() % 100 < creatEnemyProbability)
		{
			enemyX.push_back(rand() % 17 + 19);
			enemyY.push_back(4);
		}

		if (rand() % 100 < 1)
		{
			itemX.push_back(rand() % 17 + 19);
			itemY.push_back(4);
			itemData.push_back(0);
		}

		if (rand() % 100 < 1)
		{
			itemX.push_back(rand() % 17 + 19);
			itemY.push_back(4);
			itemData.push_back(1);
		}

		for (int i = 0; i < (int)enemyX.size(); i++)
		{
			if (!isInvincibility && playerX == enemyX[i] && (playerY == enemyY[i] || playerY == enemyY[i] + 1))
			{
				if (bestScore < height)
				{
					bestScore = height;
					Save();
				}

				gameOver();
				gotoXY(23, 13);
				scolor(GREEN);
				cout << "높이: " << height << "m" << endl;
				gotoXY(23, 15);
				scolor(YELLOW);
				cout << "스피드: " << speed << endl;
				gotoXY(23, 17);
				scolor(LIGHTBLUE);
				cout << "시간: " << difftime(clock(), start) / CLOCKS_PER_SEC << "초" << endl;
				gotoXY(0, 26);
				scolor();
				PlaySound(NULL, 0, 0);
				Beep(988, 1000);

				while (true)
				{
					char ch = _getch();
					ch = tolower(ch);

					if (ch == 'q')
					{
						return 0;
					}
				}
			}

			enemyY[i]++;

			if (enemyY[i] > 25)
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

			if (itemY[i] > 25)
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