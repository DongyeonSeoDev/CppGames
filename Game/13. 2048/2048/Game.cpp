#include "Game.h"

#include <iostream>
#include "Console.h"
using namespace std;

int board[4][4] = {
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
};

bool bGameOver = false;

void setConsoleView()
{
	system("mode con:cols=32 lines=26");
	system("title 2048 GAME");

	setNoCursor();
	srand((unsigned)time(NULL));
}

void initData()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			board[i][j] = 0;
		}
	}

	bGameOver = false;
}

void initDraw()
{
	setTextColor(15);

	gotoXY(MAP_X - 2, MAP_Y - 1);
	cout << "|----------------------|";

	for (int i = 0; i < 12; i++)
	{
		gotoXY(MAP_X - 2, MAP_Y + i);
		cout << "|                      |";
	}

	gotoXY(MAP_X - 2, MAP_Y + 12);
	cout << "|----------------------|";

	gotoXY(MAP_X, MAP_Y + 14);
	cout << "¡æ, ¡ç, ¡è, ¡é : ÀÌµ¿";
}

void drawGame()
{
	int num;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == 0)
			{
				setTextColor(8);
				gotoXY(MAP_X + j * 5, MAP_Y + i * 3);
				cout << "     ";
				gotoXY(MAP_X + j * 5, MAP_Y + i * 3 + 1);
				cout << "  +  ";
				gotoXY(MAP_X + j * 5, MAP_Y + i * 3 + 2);
				cout << "     ";
			}
			else
			{
				num = board[i][j] > 10000 ? board[i][j] - 10000 : board[i][j];
				int sum = 1;

				if (bGameOver)
				{
					setTextColor(8);
				}
				else
				{
					for (int k = 0; k < 12; k++)
					{
						sum *= 2;

						if (sum == num)
						{
							setTextColor(k + 1);
							break;
						}
					}
				}

				gotoXY(MAP_X + j * 5, MAP_Y + i * 3);
				cout << "|---|";
				gotoXY(MAP_X + j * 5, MAP_Y + i * 3 + 1);
				printf("%4d ", num);
				gotoXY(MAP_X + j * 5, MAP_Y + i * 3 + 2);
				cout << "|---|";

				if (bGameOver) sleep(200);
			}
		}
	}

	sleep(50);
}

void createNumber()
{
	int* empty[16] = { 0, };
	int count = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == 0)
			{
				empty[count] = &board[i][j];
				count++;
			}
		}
	}

	int random = rand() % count;
	int number = rand() % 100 < 20 ? 4 : 2;

	*empty[random] = number;
	drawGame();
	*empty[random] = 0;
	drawGame();
	*empty[random] = number;
	drawGame();
}

bool moveNumber(int sX, int sY, int tX, int tY)
{
	if (board[sY][sX] == 0 || board[sY][sX] > 10000) return false;
	if (board[tY][tX] != 0 && board[tY][tX] != board[sY][sX]) return false;

	if (board[tY][tX] == 0)
	{
		board[tY][tX] = board[sY][sX];
	}
	else if (board[tY][tX] == board[sY][sX])
	{
		board[tY][tX] *= 2;
		board[tY][tX] += 10000;
	}

	board[sY][sX] = 0;

	return true;
}

void getKey()
{
	bool bMove = false;
	bool bChange = false;

	int key = getKeyDown();

	if (key == KEY_DIRECTION)
	{
		key = getKeyDown();

		if (key == KEY_LEFT)
		{
			do
			{
				bMove = false;

				for (int i = 0; i < 4; i++)
				{
					for (int j = 1; j < 4; j++)
					{
						if (moveNumber(j, i, j - 1, i))
						{
							bMove = true;
							bChange = true;
						}
					}
				}

				if (bMove) drawGame();

			} while (bMove);
		}
		else if (key == KEY_RIGHT)
		{
			do
			{
				bMove = false;

				for (int i = 0; i < 4; i++)
				{
					for (int j = 2; j >= 0; j--)
					{
						if (moveNumber(j, i, j + 1, i))
						{
							bMove = true;
							bChange = true;
						}
					}
				}

				if (bMove) drawGame();

			} while (bMove);
		}
		else if (key == KEY_UP)
		{
			do
			{
				bMove = false;

				for (int i = 1; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (moveNumber(j, i, j, i - 1))
						{
							bMove = true;
							bChange = true;
						}
					}
				}

				if (bMove) drawGame();

			} while (bMove);
		}
		else if (key == KEY_DOWN)
		{
			do
			{
				bMove = false;

				for (int i = 2; i >= 0; i--)
				{
					for (int j = 0; j < 4; j++)
					{
						if (moveNumber(j, i, j, i + 1))
						{
							bMove = true;
							bChange = true;
						}
					}
				}

				if (bMove) drawGame();

			} while (bMove);
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (board[i][j] > 10000)
				{
					board[i][j] -= 10000;
				}
			}
		}
	}

	if (bChange)
	{
		createNumber();
	}
}

void checkGameOver()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == 0) return;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == board[i][j + 1] || board[i][j] == board[i + 1][j]) return;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (board[i][3] == board[i + 1][3]) return;
	}

	for (int j = 0; j < 3; j++)
	{
		if (board[3][j] == board[3][j + 1]) return;
	}

	bGameOver = true;

	setTextColor(15);

	gotoXY(MAP_X + 6, MAP_Y + 21);
	cout << "GAME OVER!!";

	drawGame();
}