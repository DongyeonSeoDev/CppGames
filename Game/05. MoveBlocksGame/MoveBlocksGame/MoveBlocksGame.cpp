#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

char Stage[10][16] =
{
	"+++++++++++++++",
	"+++++++++++++++",
	"++++&  ++++++++",
	"++++ OO++++++++",
	"++++ O ++++.+++",
	"++++++ ++++.+++",
	"++++++     .+++",
	"+++++    +  +++",
	"+++++    ++++++",
	"+++++++++++++++"
};

enum class eBPullDir
{
	none,
	right,
	left,
	up,
	down
};

eBPullDir bPullDir;
char backgroundMap[10][16];
int currentX, currentY;
int totalMove;
bool bPull;

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

void initScreen()
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			gotoXY(x, y);
			_putch(backgroundMap[y][x]);
		}
	}

	gotoXY(currentX, currentY);
	_putch('&');
}

bool checkEnd()
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			if (Stage[y][x] == '.' && backgroundMap[y][x] != 'O')
			{
				return false;
			}
		}
	}

	return true;
}

bool bPullPositionCheck(int dir_x, int dir_y, int x, int y)
{
	if (backgroundMap[currentY + dir_y + y][currentX + dir_x + x] == ' ' || backgroundMap[currentY + dir_y + y][currentX + dir_x + x] == '.')
	{
		if (Stage[currentY + y][currentX + x] == '.')
		{
			backgroundMap[currentY + y + dir_y][currentX + x + dir_x] = '.';
		}
		else {
			backgroundMap[currentY + y][currentX + x] = ' ';
		}

		backgroundMap[currentY + y + dir_y][currentX + x + dir_x] = '8';
	}
	else
	{
		return false;
	}

	return true;
}

void move(int dir)
{
	int dir_x = 0, dir_y = 0;

	switch (dir)
	{
	case LEFT:
		dir_x = -1;
		break;
	case RIGHT:
		dir_x = 1;
		break;
	case UP:
		dir_y = -1;
		break;
	case DOWN:
		dir_y = 1;
		break;
	}

	if (backgroundMap[currentY + dir_y][currentX + dir_x] != '+')
	{
		if (backgroundMap[currentY + dir_y][currentX + dir_x] == 'O')
		{
			if (backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] == ' '
				|| backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] == '.')
			{
				if (Stage[currentY + dir_y][currentX + dir_x] == '.')
				{
					backgroundMap[currentY + dir_y][currentX + dir_x] = '.';
				}
				else {
					backgroundMap[currentY + dir_y][currentX + dir_x] = ' ';
				}

				backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] = 'O';
			}
			else
			{
				return;
			}
		}

		if (bPull)
		{
			switch (bPullDir)
			{
			case eBPullDir::right:
				if (!bPullPositionCheck(dir_x, dir_y, 1, 0))
					return;

				break;

			case eBPullDir::left:
				if (!bPullPositionCheck(dir_x, dir_y, -1, 0))
					return;

				break;
			case eBPullDir::up:
				if (!bPullPositionCheck(dir_x, dir_y, 0, -1))
					return;

				break;
			case eBPullDir::down:
				if (!bPullPositionCheck(dir_x, dir_y, 0, 1))
					return;

				break;
			}
		}

		currentX += dir_x;
		currentY += dir_y;
		totalMove++;
	}
}

void changeBPullImage(char ch)
{
	switch (bPullDir)
	{
	case eBPullDir::right:
		backgroundMap[currentY][currentX + 1] = ch;
		break;
	case eBPullDir::left:
		backgroundMap[currentY][currentX - 1] = ch;
		break;
	case eBPullDir::up:
		backgroundMap[currentY - 1][currentX] = ch;
		break;
	case eBPullDir::down:
		backgroundMap[currentY + 1][currentX] = ch;
		break;
	}
}

void checkBPull(eBPullDir e)
{
	if (bPull)
	{
		bPull = false;
		bPullDir = eBPullDir::none;
	}
	else
	{
		bPull = true;
		bPullDir = e;
	}
}

void checkBPullDir()
{
	if (backgroundMap[currentY - 1][currentX] == 'O')
	{
		checkBPull(eBPullDir::up);
	}

	if (backgroundMap[currentY + 1][currentX] == 'O')
	{
		checkBPull(eBPullDir::down);
	}

	if (backgroundMap[currentY][currentX + 1] == 'O')
	{
		checkBPull(eBPullDir::right);
	}

	if (backgroundMap[currentY][currentX - 1] == 'O')
	{
		checkBPull(eBPullDir::left);
	}
}

int main()
{
	int ch;

	memcpy(backgroundMap, Stage, sizeof(backgroundMap));

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			if (Stage[y][x] == '&')
			{
				currentX = x;
				currentY = y;
				backgroundMap[y][x] = ' ';
			}
		}
	}

	clrscr();
	totalMove = 0;
	bPull = false;
	bPullDir = eBPullDir::none;

	while (true)
	{
		initScreen();

		ch = _getch();

		// 방향키
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
		// 일반키
		else
		{
			ch = tolower(ch);

			if (ch == 'q')
			{
				clrscr();
				exit(0);
			}
			else if (ch == 'p')
			{
				if (bPull)
				{
					bPull = false;

					changeBPullImage('O');

					bPullDir = eBPullDir::none;
				}
				else
				{
					checkBPullDir();
					changeBPullImage('8');
				}
			}
		}

		if (checkEnd())
		{
			clrscr();
			gotoXY(10, 4);
			printf("잘 풀었습니다. 아무 키나 누르세요.");
			_getch();
			clrscr();
			exit(0);
			break;
		}
	}

	return 0;
}