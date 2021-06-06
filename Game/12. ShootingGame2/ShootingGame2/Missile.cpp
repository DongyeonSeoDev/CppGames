#include "Missile.h"
#include "Console.h"

#include <iostream>
using namespace std;

void Missile::setMissile(int _x, int _y, bool _isUp)
{
	x = _x;
	y = _y;
	isUp = _isUp;
}

void Missile::drawMissile()
{
	gotoXY(x, y);

	if (isUp)
	{
		setTextColor(2);
		y--;
	}
	else
	{
		setTextColor(5);
		y += 2;
	}
	
	cout << "¡Ü";
	setTextColor(15);
}

bool Missile::checkEnd()
{
	if (y < 0 && isUp)
	{
		return true;
	}
	else if (y > 39 && !isUp)
	{
		return true;
	}

	return false;
}

bool Missile::checkCollision(int _x, int _y, bool _isUp, bool isMissileCheck)
{
	if (!isMissileCheck)
	{
		if (isUp != _isUp) return false;

		if (isUp == true && x == _x && (y == _y || y - 1 == _y))
		{
			return true;
		}
		else if (isUp == false && x == _x && (y == _y || y - 1 == _y))
		{
			return true;
		}
	}
	else
	{
		if (isUp != _isUp && x == _x && (y == _y || y - 1 == _y))
		{
			return true;
		}
	}

	return false;
}

int Missile::getX()
{
	return x;
}

int Missile::getY()
{
	return y;
}

bool Missile::getIsUp()
{
	return isUp;
}