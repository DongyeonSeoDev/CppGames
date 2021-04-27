#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

void clrscr()
{
	system("cls");
}

int currentX, currentY;
int totalFill;

char ttt[3][4] =
{
	"   ",
	"   ",
	"   "
};

char ShowMap[10][10] =
{
	"+++++++++",
	"+++++++++",
	"++.|.|.++",
	"++-----++",
	"++.|.|.++",
	"++-----++",
	"++.|.|.++",
	"++-----++",
	"+++++++++",
	"+++++++++"
};

void displayScreen()
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			gotoXY(x, y);
			_putch(ShowMap[y][x]);
		}
	}

	gotoXY(currentX, currentY);
	_putch('^');

	gotoXY(12, 2);
	puts("Z:선택");

	gotoXY(12, 4);
	puts("^:위치");

	gotoXY(12, 6);
	puts("Q:종료");

	gotoXY(12, 12);
}

void move(int dir)
{
	int dir_x = 0, dir_y = 0;

	switch (dir)
	{
	case LEFT:
		dir_x = -2;
		break;
	case RIGHT:
		dir_x = 2;
		break;
	case UP:
		dir_y = -2;
		break;
	case DOWN:
		dir_y = 2;
		break;
	}

	if (ShowMap[currentY + dir_y][currentX + dir_x] != '+')
	{
		currentX += dir_x;
		currentY += dir_y;
	}
}

bool selectUser()
{
	int x = (currentX / 2) - 1;
	int y = (currentY - 3) / 2;

	if (ttt[x][y] == ' ')
	{
		ttt[x][y] = 1;

		ShowMap[currentY - 1][currentX] = '0';

		return true;
	}

	return false;
}

void selectCom()
{
	int x, y;

	do
	{
		x = rand() % 3;
		y = rand() % 3;
	} while (ttt[x][y] != ' ');

	ttt[x][y] = 2;

	currentX = (x + 1) * 2;
	currentY = y * 2 + 3;

	ShowMap[currentY - 1][currentX] = 'X';
}

int checkWin()
{
	totalFill++;

	for (int i = 0; i < 3; i++)
	{
		if (ttt[0][i] == 1 && ttt[1][i] == 1 && ttt[2][i] == 1) return 1;
		if (ttt[0][i] == 2 && ttt[1][i] == 2 && ttt[2][i] == 2) return 2;

		if (ttt[i][0] == 1 && ttt[i][1] == 1 && ttt[i][2] == 1) return 1;
		if (ttt[i][0] == 2 && ttt[i][1] == 2 && ttt[i][2] == 2) return 2;
	}

	if (ttt[0][0] == 1 && ttt[1][1] == 1 && ttt[2][2] == 1) return 1;
	if (ttt[0][0] == 2 && ttt[1][1] == 2 && ttt[2][2] == 2) return 2;

	if (ttt[2][0] == 1 && ttt[1][1] == 1 && ttt[0][2] == 1) return 1;
	if (ttt[2][0] == 2 && ttt[1][1] == 2 && ttt[0][2] == 2) return 2;

	if (totalFill == 9) return 3;

	return 0;
}

void showResult(int gameEnd)
{
	gotoXY(10, 8);

	if (gameEnd == 1)
	{
		puts("당신이 이겼습니다.");
	}
	else if (gameEnd == 2)
	{
		puts("컴퓨터가 이겼습니다.");
	}
	else
	{
		puts("비겼습니다.");
	}
}

int main()
{
	srand((unsigned)time(NULL));

	int ch;
	int gameEnd = 0; // 0 진행중, 1 이김, 2 짐, 3 비김

	currentX = 2;
	currentY = 3;
	totalFill = 0;

	do
	{
		displayScreen();

		ch = _getch();

		if (ch == 0xE0 || ch == 0)
		{
			ch = _getch();

			switch (ch)
			{
			case LEFT:
			case RIGHT:
			case UP:
			case DOWN:
				move(ch);
				break;
			}
		}
		else
		{
			ch = tolower(ch);

			if (ch == 'q')
			{
				clrscr();
				exit(0);
			}
			else if (ch == 'z')
			{
				if (selectUser())
				{
					displayScreen();
					gameEnd = checkWin();

					if (gameEnd != 0)
					{
						break;
					}

					selectCom();
					displayScreen();
					gameEnd = checkWin();
				}
			}
		}

	} while (gameEnd == 0);

	showResult(gameEnd);
	ch = _getch();

	return 0;
}