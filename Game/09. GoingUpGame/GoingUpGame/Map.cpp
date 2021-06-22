#include "Map.h"

#include <iostream>

#include "Color.h"
#include "Game.h"
#include "System.h"

using namespace std;

//�� ������
char map[mapYSize][mapXSize] =
{
	"---------------------------------------",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"---------------------------------------"
};

char map2[mapYSize][mapXSize] =
{
	"---------------------------------------",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"---------------------------------------"
};

char map3[mapYSize][mapXSize] =
{
	"---------------------------------------",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"��                                   ��",
	"---------------------------------------"
};

char startMap[mapYSize][mapXSize + 1] =
{
	"���������������������",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��              UP! ����              ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��   ������ ������ QŰ�� �����ּ���   ��",
	"��                                    ��",
	"��    �����Ϸ��� SŰ�� �����ּ���     ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"���������������������"
};

char descriptionMap[mapYSize][mapXSize + 1] =
{
	"���������������������",
	"��                                    ��",
	"��                ����                ��",
	"��                                    ��",
	"��   ��: �÷��̾�   ��: ���� ������   ��",
	"��   ��: ��   ��: ���ǵ� �ٿ� ������  ��",
	"��                                    ��",
	"��    Ű���� ȭ��ǥŰ�� �÷��̾    ��",
	"��           ������ �� �ִ�.          ��",
	"��                                    ��",
	"��     ���� ������ ���ӿ��� �ȴ�.     ��",
	"��                                    ��",
	"��    ���� �������� ������ ��õ���   ��",
	"��            ������ �ȴ�.            ��",
	"��                                    ��",
	"��     ���ǵ� �ٿ� �������� ������    ��",
	"��         ���ǵ尡 ��������.         ��",
	"��                                    ��",
	"��   �ִ��� ���� �ö󰡴� �����̴�.   ��",
	"��                                    ��",
	"��    ���ư����� XŰ�� �����ּ���     ��",
	"��                                    ��",
	"���������������������"
};

char gameOverMap[mapYSize][mapXSize + 1] =
{
	"���������������������",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��              ���ӿ���              ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"��    �����Ϸ��� QŰ�� �����ּ���     ��",
	"��                                    ��",
	"��                                    ��",
	"��                                    ��",
	"���������������������"
};

//���� ȭ��
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
	cout << "�ְ� ����: " << bestScore << "m" << endl;
	scolor();
}

//���� ȭ��
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

//���ӿ��� ȭ��
void showGameOver()
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

//���� ȭ��
void drawMap(char map[mapYSize][mapXSize])
{
	scolor(YELLOW);
	gotoXY(0, 4);
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
	cout << "��";

	for (int i = 0; i < (int)itemData.size(); i++)
	{
		gotoXY(itemX[i], itemY[i]);

		if (itemData[i] == 0)
		{
			scolor(LIGHTBLUE);
			cout << "��";
		}
		else
		{
			scolor(LIGHTGREEN);
			cout << "��";
		}
	}

	for (int i = 0; i < (int)enemyX.size(); i++)
	{
		gotoXY(enemyX[i], enemyY[i]);
		scolor(LIGHTRED);
		cout << "��";
	}

	scolor();
}