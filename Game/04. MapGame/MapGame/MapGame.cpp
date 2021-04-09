#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int currentX, currentY;

char ShowMap[20][21] = {
	"++++++++++++++++++++",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"+..................+",
	"++++++++++++++++++++"
};

void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

void keyPrint()
{
	gotoXY(30, 2);
	cout << "Q : 종료";
	gotoXY(30, 3);
	cout << "Z : 현재 위치에 X표시 하기";
	gotoXY(30, 4);
	cout << "A : 상하좌우에 있는 벽 제거 (테두리 벽은 제외)";
	gotoXY(30, 5);
	cout << "B : 상하좌우에 있는 테두리 벽을 제거, 대칭되는 위치의 벽도 같이 제거";
	gotoXY(34, 6);
	cout << "(사라진 벽을 통과하면 대칭되는 위치로 나옴)";
}

void displayScreen()
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			gotoXY(x, y);
			_putch(ShowMap[y][x]);
		}
	}

	gotoXY(currentX, currentY);
	_putch('0');
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

	if (currentX + dir_x == -1)
	{
		currentX = 19;
	}
	else if (currentX + dir_x == 20)
	{
		currentX = 0;
	}
	else if (currentY + dir_y == -1)
	{
		currentY = 19;
	}
	else if (currentY + dir_y == 20)
	{
		currentY = 0;
	}
	else if (ShowMap[currentY + dir_y][currentX + dir_x] != '+')
	{
		currentX += dir_x;
		currentY += dir_y;
	}
}

void wall()
{
	int wall[10] = { 0, };

	for (int i = 0; i < 10; i++)
	{
		bool different = true;

		do
		{
			wall[i] = rand() % 324 + 1;

			for (int j = 0; j < i; j++)
			{
				if (wall[i] == wall[j] && wall[i] == 0)
				{
					different = false;
					break;
				}
			}

		} while (!different);
	}

	for (int i = 0; i < 10; i++)
	{
		ShowMap[wall[i] / 18 + 1][wall[i] % 18 + 1] = '+';
	}
}

void setcursor(bool i, DWORD size) {
	CONSOLE_CURSOR_INFO c = { 0 };
	c.dwSize = size;
	c.bVisible = i;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

int main()
{
	int ch;
	currentX = 1;
	currentY = 1;

	srand((unsigned int)time(NULL));
	setcursor(false, 1);
	wall();
	keyPrint();

	while (true)
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
				gotoXY(0, 20);
				exit(0);
			}
			else if (ch == 'z')
			{
				ShowMap[currentY][currentX] = 'X';
			}
			else if (ch == 'a')
			{
				if (currentX + 1 != 19)
					ShowMap[currentY][currentX + 1] = '.';

				if (currentX - 1 != 0)
					ShowMap[currentY][currentX - 1] = '.';

				if (currentY + 1 != 19)
					ShowMap[currentY + 1][currentX] = '.';

				if (currentY - 1 != 0)
					ShowMap[currentY - 1][currentX] = '.';
			}
			else if (ch == 'b')
			{
				if (currentX + 1 == 19 || currentX - 1 == 0)
				{
					ShowMap[currentY][0] = '.';
					ShowMap[currentY][19] = '.';
				}

				if (currentY + 1 == 19 || currentY - 1 == 0)
				{
					ShowMap[0][currentX] = '.';
					ShowMap[19][currentX] = '.';
				}

				if ((currentX == 0 || currentX == 19))
				{
					if (currentY + 1 < 21)
					{
						ShowMap[currentY + 1][0] = '.';
						ShowMap[currentY + 1][19] = '.';
					}

					if (currentY - 1 > -1)
					{
						ShowMap[currentY - 1][0] = '.';
						ShowMap[currentY - 1][19] = '.';
					}
				}

				if ((currentY == 0 || currentY == 19))
				{
					if (currentX + 1 < 21)
					{
						ShowMap[0][currentX + 1] = '.';
						ShowMap[19][currentX + 1] = '.';
					}

					if (currentX - 1 > -1)
					{
						ShowMap[0][currentX - 1] = '.';
						ShowMap[19][currentX - 1] = '.';
					}
				}
			}
		}
	}

	return 0;
}