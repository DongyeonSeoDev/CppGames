#include "Map.h"

#include <iostream>

#include "Color.h"
#include "Game.h"
#include "System.h"

using namespace std;

//맵 디자인
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

//시작 화면
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

//설명 화면
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

//게임오버 화면
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

//게임 화면
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