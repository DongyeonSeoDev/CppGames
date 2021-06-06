#include <iostream>
#include <time.h>
#include <vector>

#include "Console.h"
#include "Enemy.h"
#include "Missile.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

int x, y, missileCount;

bool isPlay = true;

vector<Enemy> enemies;
vector<Missile> myMissiles;

void setConsoleView()
{
	system("mode con:cols=40 lines=40");
	system("title SHOOTING GAME #2");
}

void initData()
{
	srand((unsigned)time(NULL));

	x = 10;
	y = 38;
	isPlay = true;

	missileCount = 0;

	enemies.clear();
	myMissiles.clear();
}

void checkDirection()
{
	int key = _getch();

	switch (key)
	{
	case UP:
		if (y > 0)
		{
			y--;
		}
		break;

	case DOWN:
		if (y < 39)
		{
			y++;
		}
		break;

	case RIGHT:
		if (x < 19)
		{
			x++;
		}
		break;

	case LEFT:
		if (x > 0)
		{
			x--;
		}
		break;
	}
}

void checkCollision()
{
	bool bCollision = false;

	do
	{
		bCollision = false;

		for (int i = 0; i < (int)myMissiles.size(); i++)
		{
			for (int j = 0; j < (int)enemies.size(); j++)
			{
				if (enemies[j].checkPlayer(x, y))
				{
					isPlay = false;
					return;
				}

				if (myMissiles[i].checkCollision(enemies[j].getX(), enemies[j].getY(), true, false))
				{
					myMissiles.erase(myMissiles.begin() + i);
					enemies.erase(enemies.begin() + j);
					bCollision = true;
					break;
				}
			}

			if (bCollision) break;

			if (myMissiles[i].checkCollision(x, y, false, false))
			{
				isPlay = false;
				return;
			}

			for (int j = 0; j < (int)myMissiles.size(); j++)
			{
				if (myMissiles[i].checkCollision(myMissiles[j].getX(), myMissiles[j].getY(), myMissiles[j].getIsUp(), true))
				{
					if (i > j)
					{
						myMissiles.erase(myMissiles.begin() + i);
						myMissiles.erase(myMissiles.begin() + j);
					}
					else
					{
						myMissiles.erase(myMissiles.begin() + j);
						myMissiles.erase(myMissiles.begin() + i);
					}

					bCollision = true;
					break;
				}
			}
		}

	} while (bCollision);
}

void drawPlayer()
{
	gotoXY(x, y);
	cout << "▲";

	gotoXY(19, 39);
}

int main()
{
	setConsoleView();

	initData();

	while (true)
	{
		int key = getKeyDown();
		key = tolower(key);

		if (key == 0xE0)
		{
			checkDirection();
		}
		else if (key == 'a')
		{
			if (missileCount == 0)
			{
				Missile missile;
				missile.setMissile(x, y, true);

				myMissiles.push_back(missile);

				missileCount = 3;
			}
		}

		if (rand() % 100 < 10)
		{
			Enemy enemy;
			enemy.setEnemy();

			enemies.push_back(enemy);
		}

		for (int i = 0; i < (int)enemies.size(); i++)
		{
			if (rand() % 100 < 5)
			{
				Missile missile;
				missile.setMissile(enemies[i].getX(), enemies[i].getY(), false);

				myMissiles.push_back(missile);
			}
		}

		checkCollision();

		if (!isPlay) break;

		for (int i = 0; i < (int)myMissiles.size(); i++)
		{
			myMissiles[i].drawMissile();
		}

		for (int i = 0; i < (int)enemies.size(); i++)
		{
			enemies[i].drawEnemy();
		}

		drawPlayer();

		for (int i = 0; i < (int)myMissiles.size(); i++)
		{
			if (myMissiles[i].checkEnd())
			{
				myMissiles.erase(myMissiles.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < (int)enemies.size(); i++)
		{
			if (enemies[i].checkEnd())
			{
				enemies.erase(enemies.begin() + i);
				i--;
			}
		}

		if (missileCount > 0)
		{
			missileCount--;
		}

		Sleep(100);
		clrscr();
	}

	return 0;
}