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
	"++++++   ++++++",
	"++++&  @ ++++++",
	"++++ OO++++++++",
	"++++ O ++++.+++",
	"+++++  ++++.+++",
	"+++++      .+++",
	"+++++    @  +++",
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
int beforeX, beforeY;
int printX[10], printY[10];
int printCount = 0;
int portalX[2], portalY[2];
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

void setcursor(bool i, DWORD size) 
{
	CONSOLE_CURSOR_INFO c = { 0 };
	c.dwSize = size;
	c.bVisible = i;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
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

	gotoXY(20, 2);
	puts("불럭 이동 게임");

	gotoXY(20, 4);
	puts("Q : 종료");

	gotoXY(20, 6);
	puts("P : 당기기");

	gotoXY(20, 8);
	printf("이동 횟수 : %d", totalMove);
}

void addPrintXYPosition(int x, int y)
{
	printX[printCount] = x;
	printY[printCount] = y;
	printCount++;
}

void printStage()
{
	for (int i = 0; i < printCount; i++)
	{
		gotoXY(printX[i], printY[i]);
		_putch(backgroundMap[printY[i]][printX[i]]);
	}

	gotoXY(currentX, currentY);
	_putch('&');

	gotoXY(beforeX, beforeY);
	_putch(backgroundMap[beforeY][beforeX]);

	gotoXY(20, 8);
	printf("이동 횟수 : %d", totalMove);
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
			backgroundMap[currentY + y][currentX + x] = '.';
			addPrintXYPosition(currentX + x, currentY + y);
		}
		else if (Stage[currentY + y][currentX + x] == '@')
		{
			backgroundMap[currentY + y][currentX + x] = '@';
			addPrintXYPosition(currentX + x, currentY + y);
		}
		else {
			backgroundMap[currentY + y][currentX + x] = ' ';
			addPrintXYPosition(currentX + x, currentY + y);
		}

		backgroundMap[currentY + y + dir_y][currentX + x + dir_x] = '8';
		addPrintXYPosition(currentX + x + dir_x, currentY + y + dir_y);
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
			if (backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] == ' ' || backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] == '.')
			{
				if (Stage[currentY + dir_y][currentX + dir_x] == '.')
				{
					backgroundMap[currentY + dir_y][currentX + dir_x] = '.';
					addPrintXYPosition(currentX + dir_x, currentY + dir_y);
				}
				else if (Stage[currentY + dir_y][currentX + dir_x] == '@') 
				{
					backgroundMap[currentY + dir_y][currentX + dir_x] = '@';
					addPrintXYPosition(currentX + dir_x, currentY + dir_y);
				}
				else {
					backgroundMap[currentY + dir_y][currentX + dir_x] = ' ';
					addPrintXYPosition(currentX + dir_x, currentY + dir_y);
				}

				backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] = 'O';
				addPrintXYPosition(currentX + dir_x * 2, currentY + dir_y * 2);
			}
			else if (backgroundMap[currentY + dir_y * 2][currentX + dir_x * 2] == '@')
			{
				if (currentY + dir_y * 2 == portalY[0] && currentX + dir_x * 2 == portalX[0])
				{
					if (backgroundMap[portalY[1]][portalX[1]] == 'O')
					{
						backgroundMap[portalY[0]][portalX[0]] = 'O';
						addPrintXYPosition(portalX[0], portalY[0]);
					}
					else
					{
						backgroundMap[portalY[1]][portalX[1]] = 'O';
						addPrintXYPosition(portalX[1], portalY[1]);
						backgroundMap[portalY[0]][portalX[0]] = '@';
						addPrintXYPosition(portalX[0], portalY[0]);
					}
				}
				else
				{
					if (backgroundMap[portalY[0]][portalX[0]] == 'O')
					{
						backgroundMap[portalY[1]][portalX[1]] = 'O';
						addPrintXYPosition(portalX[1], portalY[1]);
					}
					else
					{
						backgroundMap[portalY[0]][portalX[0]] = 'O';
						addPrintXYPosition(portalX[0], portalY[0]);
						backgroundMap[portalY[1]][portalX[1]] = '@';
						addPrintXYPosition(portalX[1], portalY[1]);
					}
				}

				if (Stage[currentY + dir_y][currentX + dir_x] == '.')
				{
					backgroundMap[currentY + dir_y][currentX + dir_x] = '.';
					addPrintXYPosition(currentX + dir_x, currentY + dir_y);
				}
				else if (Stage[currentY + dir_y][currentX + dir_x] == '@') {
					backgroundMap[currentY + dir_y][currentX + dir_x] = '@';
					addPrintXYPosition(currentX + dir_x, currentY + dir_y);
				}
				else {
					backgroundMap[currentY + dir_y][currentX + dir_x] = ' ';
					addPrintXYPosition(currentX + dir_x, currentY + dir_y);
				}
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

		beforeX = currentX;
		beforeY = currentY;
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
		addPrintXYPosition(currentX + 1, currentY);
		break;
	case eBPullDir::left:
		backgroundMap[currentY][currentX - 1] = ch;
		addPrintXYPosition(currentX - 1, currentY);
		break;
	case eBPullDir::up:
		backgroundMap[currentY - 1][currentX] = ch;
		addPrintXYPosition(currentX, currentY - 1);
		break;
	case eBPullDir::down:
		backgroundMap[currentY + 1][currentX] = ch;
		addPrintXYPosition(currentX, currentY + 1);
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

void findStageObject()
{
	int portalCount = 0;

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

			if (Stage[y][x] == '@')
			{
				portalX[portalCount] = x;
				portalY[portalCount] = y;
				portalCount++;
			}
		}
	}
}

int main()
{
	int ch;

	memcpy(backgroundMap, Stage, sizeof(backgroundMap));
	setcursor(false, 1);

	findStageObject();

	clrscr();
	totalMove = 0;
	bPull = false;
	bPullDir = eBPullDir::none;

	initScreen();

	while (true)
	{
		printStage();
		printCount = 0;
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
			printf("축하합니다. 스테이지를 클리어 하였습니다.  (종료하려면 아무 키나 눌러주세요)");
			ch = _getch();
			clrscr();
			exit(0);
			break;
		}
	}

	return 0;
}