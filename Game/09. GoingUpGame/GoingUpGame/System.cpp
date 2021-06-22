#include "System.h"

#include <Windows.h>
#include <iostream>
#include <conio.h>

#include "Game.h"

//커서 이동
void gotoXY(int x, int y)
{
	COORD Cur;
	Cur.X = x * 2;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

//커서 안보이게 설정
void setcursor(bool i, DWORD size)
{
	CONSOLE_CURSOR_INFO c = { 0 };
	c.dwSize = size;
	c.bVisible = i;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

//저장
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

//불러오기
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

char getCH()
{
	return _getch();
}