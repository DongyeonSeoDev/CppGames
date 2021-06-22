#include "Game.h"

#include <iostream>
#include <Windows.h>
#include <ctime>

#include "System.h"
#include "Color.h"
#include "Map.h"
#include "Sound.h"

using namespace std;

//�÷��̾� ��ǥ
int playerX, playerY;

//���� ������ ��ǥ
vector<int> enemyX, enemyY;
vector<int> itemX, itemY, itemData;

Score score;

int bestScore;

int height;
int speed;
clock_t startTime;

int minusSpeed = 0; //���̳ʽ� ���ǵ�
bool isInvincibility = false; //���� �������� Ȯ��
int startItemHeight = 0; //���� ���� �ð�

void inputCheck()
{
	if (GetAsyncKeyState(VK_LEFT)) { //����
		playerX--;

		if (playerX < 19) playerX = 19;
	}
	if (GetAsyncKeyState(VK_RIGHT)) { //������
		playerX++;

		if (playerX > 35) playerX = 35;
	}
	if (GetAsyncKeyState(VK_UP)) { //��
		playerY--;

		if (playerY < 5) playerY = 5;
	}
	if (GetAsyncKeyState(VK_DOWN)) { //�Ʒ�
		playerY++;

		if (playerY > 25) playerY = 25;
	}
}

void currentState()
{
	scolor(GREEN);
	gotoXY(40, 6);
	cout << "����: " << height << "m" << endl;
	scolor(YELLOW);
	gotoXY(40, 8);
	cout << "���ǵ�: " << speed << endl;
	scolor(LIGHTBLUE);
	gotoXY(40, 10);
	cout << "�ð�: " << difftime(clock(), startTime) / CLOCKS_PER_SEC << "��" << endl;
	scolor(MAGENTA);
	scolor(LIGHTMAGENTA);
	gotoXY(40, 12);
	if (isInvincibility) cout << "�����ð�" << endl;
}

void createEnemy(int creatEnemyProbability)
{
	//�� ����
	if (rand() % 100 < creatEnemyProbability)
	{
		int randomX = rand() % 17 + 19;
		enemyX.push_back(randomX);
		enemyY.push_back(4);

		//�� �߰� ����
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
	//������ ����
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
	//�� �浹 Ȯ��
	for (int i = 0; i < (int)enemyX.size(); i++)
	{
		if (!isInvincibility && playerX == enemyX[i] && (playerY == enemyY[i] || playerY == enemyY[i] + 1))
		{
			gameOver();
		}

		//�� �̵�
		enemyY[i]++;

		//�� ������ ��ġ Ȯ��
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
	//������ �浹 Ȯ��
	for (int i = 0; i < (int)itemData.size(); i++)
	{
		if (playerX == itemX[i] && (playerY == itemY[i] || playerY == itemY[i] + 1))
		{
			if (itemData[i] == 0) //������ 1�� ȿ�� ����
			{
				minusSpeed += 1;
			}
			else //������ 2�� ȿ�� ����
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

		//������ �̵�
		itemY[i]++;

		//������ ��������ġ Ȯ��
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
	//���ӿ����� ����
	if (bestScore < height)
	{
		bestScore = height;
		Save();
	}

	showGameOver();
	gotoXY(23, 13);
	scolor(GREEN);
	cout << "����: " << height << "m" << endl;
	gotoXY(23, 15);
	scolor(YELLOW);
	cout << "���ǵ�: " << speed << endl;
	gotoXY(23, 17);
	scolor(LIGHTBLUE);
	cout << "�ð�: " << difftime(clock(), startTime) / CLOCKS_PER_SEC << "��" << endl;
	gotoXY(0, 26);
	scolor();
	PlaySound(NULL, 0, 0);
	Beep(988, 1000);

	while (true)
	{
		char ch = getCH();
		ch = tolower(ch);

		if (ch == 'q') //q�� ������ ����
		{
			exit(0);
		}
	}
}