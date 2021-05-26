#include "Missile.h"
#include "Console.h"

#include <iostream>

using namespace std;

void Missile::setMissile(int _y)
{
	if (_y == -1)
	{
		x = 59;
		y = rand() % 20;

		bMoveLeft = true;
	}
	else
	{
		x = 3;
		y = _y;
		
		bMoveLeft = false;
	}
}

void Missile::moveMissile()
{
	if (bMoveLeft)
	{
		x--;
	}
	else
	{
		x++;
	}
}

void Missile::drawMissile()
{
	if (x < 1 || x > 58) return;

	gotoXY(x, y);

	if (bMoveLeft)
	{
		setTextColor(1);
		cout << "¢¸";
		setTextColor(15);
	}
	else
	{
		setTextColor(14);
		cout << "¡æ";
		setTextColor(15);
	}
}

bool Missile::checkEnd()
{
	if (bMoveLeft)
	{
		if (x < 1)
		{
			return true;
		}
	}
	else
	{
		if (x > 58)
		{
			return true;
		}
	}

	return false;
}

bool Missile::checkCollision(Missile missile)
{
	if ((x == missile.x || x - 1 == missile.x) && y == missile.y)
	{
		return true;
	}

	return false;
}

bool Missile::checkPlayer(int playerX, int playerY, bool bMoveDown)
{
	if (bMoveDown)
	{
		if ((x == playerX || x + 1 == playerX) && (y == playerY || y + 1 == playerY))
		{
			return true;
		}
	}
	else
	{
		if ((x == playerX || x + 1 == playerX) && (y == playerY || y - 1 == playerY))
		{
			return true;
		}
	}

	return false;
}