
#include <iostream>
#include <time.h>
#include <vector>

#include "Console.h"
#include "Missile.h"

using namespace std;

bool bMoveDown;
int y;
int spawnEnemyProbability = 20;

vector<Missile> missiles, myMissiles;

void setConsoleView()
{
	system("mode con:cols=60 lines=24");
	system("title SHOOTING GAME");
}

int main()
{
	bMoveDown = true;
	y = 0;

	missiles.clear();

	srand((unsigned)time(NULL));

	setConsoleView();

	int key;
	int score = 0;
	bool gamePlay = true;

	while (gamePlay)
	{
		key = getKeyDown();
		key = tolower(key);

		if (key == 'a')
		{
			Missile myMissile;
			myMissile.setMissile(y);

			myMissiles.push_back(myMissile);
		}

		if (rand() % 100 < spawnEnemyProbability)
		{
			Missile missile;
			missile.setMissile(-1);

			missiles.push_back(missile);
		}

		for (int i = 0; i < (int)missiles.size(); i++)
		{
			missiles[i].moveMissile();
			missiles[i].drawMissile();
		}

		for (int i = 0; i < (int)myMissiles.size(); i++)
		{
			myMissiles[i].moveMissile();
			myMissiles[i].drawMissile();
		}

		gotoXY(2, y);
		cout << "▶";
		gotoXY(59, 19);

		gotoXY(0, 20);
		cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
		gotoXY(0, 22);
		cout << "점수: " << score;

		if (bMoveDown)
		{
			y++;

			if (y > 19)
			{
				y = 19;
				bMoveDown = false;
			}
		}
		else
		{
			y--;

			if (y < 0)
			{
				y = 0;
				bMoveDown = true;
			}
		}

		for (int i = 0; i < (int)missiles.size(); i++)
		{
			if (missiles[i].checkPlayer(2, y, bMoveDown))
			{
				gamePlay = false;
				break;
			}

			if (missiles[i].checkEnd())
			{
				missiles.erase(missiles.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < (int)myMissiles.size(); i++)
		{
			if (myMissiles[i].checkEnd())
			{
				myMissiles.erase(myMissiles.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < (int)myMissiles.size(); i++)
		{
			for (int j = 0; j < (int)missiles.size(); j++)
			{
				if (myMissiles[i].checkCollision(missiles[j]))
				{
					myMissiles.erase(myMissiles.begin() + i);
					i--;

					missiles.erase(missiles.begin() + j);
					break;
				}
			}
		}

		score++;

		if (score >= 300)
		{
			spawnEnemyProbability = 50;
		}

		sleep(50);
		clrscr();
	}

	cout << "게임오버" << endl;
	cout << "점수: " << score << endl;

	return 0;
}