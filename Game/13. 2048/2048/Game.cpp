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

void start()
{
	setTextColor(14);
	gotoXY(0, 2);
	cout << "★★★★★★★★★★★★★★★★";

	setTextColor(2);
	gotoXY(11, 6);
	cout << "2048 게임";

	setTextColor(3);
	gotoXY(11, 12);
	cout << "시작하려면";
	gotoXY(7, 13);
	cout << "아무키나 눌러주세요";

	setTextColor(5);
	gotoXY(8, 19);
	cout << "HIGHSCORE: " << Load();

	setTextColor(14);
	gotoXY(0, 23);
	cout << "★★★★★★★★★★★★★★★★";

	setTextColor(15);

	getKeyDown();

	clrscr();
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
	cout << "→, ←, ↑, ↓ : 이동";

	gotoXY(MAP_X + 7, MAP_Y + 16);
	cout << "Q: 종료" << endl;
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
	key = tolower(key);

	if (key == KEY_DIRECTION)
	{
		if (bGameOver) return;

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
	else if (key == 'q')
	{
		clrscr();
		setTextColor(15);
		gotoXY(0, 0);
		exit(0);
	}

	if (bChange)
	{
		createNumber();
	}
}

void checkGameOver()
{
	if (bGameOver) return;

	showScore();

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

	gotoXY(MAP_X + 6, MAP_Y + 22);
	cout << "GAME OVER!!";

	drawGame();
}

void showScore()
{
	int score = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			score += board[i][j] > 10000 ? board[i][j] - 10000 : board[i][j];
		}
	}

	int highScore = Load();

	if (score > highScore)
	{
		highScore = score;
		Save(highScore);
	}

	setTextColor(15);
	gotoXY(MAP_X + 6, MAP_Y + 18);
	cout << "SCORE: " << score;
	gotoXY(MAP_X + 4, MAP_Y + 20);
	cout << "HIGHSCORE: " << highScore;
}

void Save(int highSocre)
{
	FILE* fp = 0;
	fopen_s(&fp, FNAME, "w");

	if (fp)
	{
		fwrite(&highSocre, sizeof(highSocre), 1, fp);
		fclose(fp);
	}
}

int Load()
{
	int highScore = 0;

	FILE* fp = 0;
	fopen_s(&fp, FNAME, "r");
	if (fp)
	{
		fread(&highScore, sizeof(highScore), 1, fp);
		fclose(fp);
	}

	return highScore;
}