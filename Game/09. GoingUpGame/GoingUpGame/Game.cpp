#include "Game.h"

#include <iostream>
#include <Windows.h>
#include <ctime>

#include "System.h"
#include "Color.h"
#include "Map.h"
#include "Sound.h"

using namespace std;

//플레이어 좌표
int playerX, playerY;

//적과 아이템 좌표
vector<int> enemyX, enemyY;
vector<int> itemX, itemY, itemData;

Score score;

int bestScore;

int height;
int speed;
clock_t startTime;

int minusSpeed = 0; //마이너스 스피드
bool isInvincibility = false; //현재 무적인지 확인
int startItemHeight = 0; //무적 유지 시간

void inputCheck()
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
}

void currentState()
{
	scolor(GREEN);
	gotoXY(40, 6);
	cout << "높이: " << height << "m" << endl;
	scolor(YELLOW);
	gotoXY(40, 8);
	cout << "스피드: " << speed << endl;
	scolor(LIGHTBLUE);
	gotoXY(40, 10);
	cout << "시간: " << difftime(clock(), startTime) / CLOCKS_PER_SEC << "초" << endl;
	scolor(MAGENTA);
	scolor(LIGHTMAGENTA);
	gotoXY(40, 12);
	if (isInvincibility) cout << "무적시간" << endl;
}

void createEnemy(int creatEnemyProbability)
{
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
}

void createItem()
{
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
}

void collisionEnemy()
{
	//적 충돌 확인
	for (int i = 0; i < (int)enemyX.size(); i++)
	{
		if (!isInvincibility && playerX == enemyX[i] && (playerY == enemyY[i] || playerY == enemyY[i] + 1))
		{
			gameOver();
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
}

void collisionItem()
{
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
}

void gameOver()
{
	//게임오버시 실행
	if (bestScore < height)
	{
		bestScore = height;
		Save();
	}

	showGameOver();
	gotoXY(23, 13);
	scolor(GREEN);
	cout << "높이: " << height << "m" << endl;
	gotoXY(23, 15);
	scolor(YELLOW);
	cout << "스피드: " << speed << endl;
	gotoXY(23, 17);
	scolor(LIGHTBLUE);
	cout << "시간: " << difftime(clock(), startTime) / CLOCKS_PER_SEC << "초" << endl;
	gotoXY(0, 26);
	scolor();
	PlaySound(NULL, 0, 0);
	Beep(988, 1000);

	while (true)
	{
		char ch = getCH();
		ch = tolower(ch);

		if (ch == 'q') //q를 누르면 종료
		{
			exit(0);
		}
	}
}