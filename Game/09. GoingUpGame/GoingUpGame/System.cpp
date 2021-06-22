#include "System.h"

#include <Windows.h>
#include <iostream>
#include <conio.h>

#include "Game.h"

//Ŀ�� �̵�
void gotoXY(int x, int y)
{
	COORD Cur;
	Cur.X = x * 2;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

//Ŀ�� �Ⱥ��̰� ����
void setcursor(bool i, DWORD size)
{
	CONSOLE_CURSOR_INFO c = { 0 };
	c.dwSize = size;
	c.bVisible = i;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

//����
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

//�ҷ�����
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