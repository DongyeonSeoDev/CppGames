#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "fmod.hpp"
#include "fmod_errors.h"

using namespace std;
using namespace FMOD;

//맵 사이즈
#define mapXSize 40
#define mapYSize 23

//방향키 번호
#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

//색깔
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

//저장 파일 이름
#define FNAME "score"

//플레이어 좌표
int playerX, playerY;

//적과 아이템 좌표
vector<int> enemyX, enemyY;
vector<int> itemX, itemY, itemData;

//점수 저장
struct Score
{
	int score;
};

Score score;

int bestScore = 0;

//FOMD 변수
System* pSystem;
Sound* pSound[2];
Channel* pChannel[2];

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

//색깔 변경
void scolor(unsigned short text = 15, unsigned short back = 0)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

//사운드 시스템
void SoundSystem()
{
	System_Create(&pSystem);

	pSystem->init(2, FMOD_INIT_NORMAL, NULL);

	pSystem->createSound("sound1.wav", FMOD_DEFAULT, NULL, &pSound[0]);
	pSystem->createSound("sound2.wav", FMOD_DEFAULT, NULL, &pSound[1]);
}

//소리 재생
void Play(int Sound_num, int channelNumber) 
{
	pSystem->playSound(pSound[Sound_num], NULL, 0, &pChannel[channelNumber]);
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

int main()
{
	Load();

	system("title UP! 게임");
	setcursor(false, 1);
	SoundSystem();

	srand((unsigned)time(NULL));

	int height = 0; //현재 높이
	int speed = 0; //현재 속도
	int creatEnemyProbability = 10; //적 생성 확률
	int minusSpeed = 0; //마이너스 스피드

	bool isInvincibility = false; //현재 무적인지 확인
	int startItemHeight = 0; //무적 유지 시간

	playerX = 27;
	playerY = 21;

	start();

	while (true)
	{
		char ch = _getch();
		ch = tolower(ch);

		if (ch == 's') //s면 게임 시작
		{
			Beep(784, 200);
			break;
		}
		else if (ch == 'q') //q면 설명 화면
		{
			Beep(698, 200);
			description();

			while (true)
			{
				char ch = _getch();
				ch = tolower(ch);

				if (ch == 'x') //x면 돌아가기
				{
					Beep(698, 200);
					start();
					break;
				}
			}
		}
	}

	clock_t start = clock(); //시간 시작
	PlaySound(TEXT("Music.wav"), NULL, SND_ASYNC | SND_LOOP); //노래 재생

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

		//현재 상태
		scolor(GREEN);
		gotoXY(40, 6);
		cout << "높이: " << height << "m" << endl;
		scolor(YELLOW);
		gotoXY(40, 8);
		cout << "스피드: " << speed << endl;
		scolor(LIGHTBLUE);
		gotoXY(40, 10);
		cout << "시간: " << difftime(clock(), start) / CLOCKS_PER_SEC << "초" << endl;
		scolor(MAGENTA);
		scolor(LIGHTMAGENTA);
		gotoXY(40, 12);
		if (isInvincibility) cout << "무적시간" << endl;

		//높이별로 맵 출력
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

		//적 생성
		if (rand() % 100 < creatEnemyProbability)
		{
			int randomX = rand() % 17 + 19;
			enemyX.push_back(randomX);
			enemyY.push_back(4);

			//적 추가 생성
			if (randomX > 2 && randomX < 33)
			{
				if (rand() % 100 < 20)
				{
					enemyX.push_back(randomX + 1);
					enemyY.push_back(4);
				}
				
				if (rand() % 100 < 20)
				{
					enemyX.push_back(randomX - 1);
					enemyY.push_back(4);
				}

				if (rand() % 100 < 20)
				{
					enemyX.push_back(randomX);
					enemyY.push_back(5);
				}
			}
		}

		//아이템 생성
		if (speed - minusSpeed > 0 && rand() % 100 < 1)
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

		//적 충돌 확인
		for (int i = 0; i < (int)enemyX.size(); i++)
		{
			if (!isInvincibility && playerX == enemyX[i] && (playerY == enemyY[i] || playerY == enemyY[i] + 1))
			{
				//게임오버시 실행
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

					if (ch == 'q') //q를 누르면 종료
					{
						return 0;
					}
				}
			}

			//적 이동
			enemyY[i]++;

			//적 마지막 위치 확인
			if (enemyY[i] > 25)
			{
				enemyX.erase(enemyX.begin() + i);
				enemyY.erase(enemyY.begin() + i);
				i--;
			}
		}

		//아이템 충돌 확인
		for (int i = 0; i < (int)itemData.size(); i++)
		{
			if (playerX == itemX[i] && (playerY == itemY[i] || playerY == itemY[i] + 1))
			{
				if (itemData[i] == 0) //아이템 1번 효과 실행
				{
					minusSpeed += 1;
				}
				else //아이템 2번 효과 실행
				{
					isInvincibility = true;
					startItemHeight = height;
				}

				itemX.erase(itemX.begin() + i);
				itemY.erase(itemY.begin() + i);
				itemData.erase(itemData.begin() + i);
				i--;

				Play(0, 0);

				continue;
			}

			//아이템 이동
			itemY[i]++;

			//아이템 마지막위치 확인
			if (itemY[i] > 25)
			{
				itemX.erase(itemX.begin() + i);
				itemY.erase(itemY.begin() + i);
				itemData.erase(itemData.begin() + i);
				i--;
			}
		}

		//플레이어 이동
		height++;

		//스피드와 적 확률 확인
		speed = height / 100 - minusSpeed;
		creatEnemyProbability = height / 5;

		//스피드 예외처리
		if (speed < 0) speed = 0;
		else if (speed > 5) speed = 5;

		//적 생성 확률 예외처리
		if (creatEnemyProbability < 20) creatEnemyProbability = 20;
		else if (creatEnemyProbability > 100) creatEnemyProbability = 100;

		if (isInvincibility && height - startItemHeight >= 30)
		{
			isInvincibility = false;
		}

		//높이가 100의 배수라면 효과음 재생
		if (height % 100 == 0)
		{
			Play(1, 1);
		}

		pSystem->update();

		Sleep(50 - speed * 10);
	}

	return 0;
}