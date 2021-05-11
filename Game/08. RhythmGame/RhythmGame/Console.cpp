#include <Windows.h>
#include <conio.h>

void gotoXY(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void setTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clrscr()
{
	system("cls");
}

void beep(int tone, int delay)
{
	Beep(tone, delay);
}

void sleep(int delay)
{
	Sleep(delay);
}

int input()
{
	if (_kbhit())
	{
		return _getch() - '0';
	}

	return 0;
}