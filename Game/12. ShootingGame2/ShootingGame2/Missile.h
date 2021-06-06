#pragma once

class Missile
{
private:
	int x;
	int y;

	bool isUp;

public:
	void setMissile(int _x, int _y, bool _isUp);
	void drawMissile();
	bool checkEnd();

	bool checkCollision(int _x, int _y, bool _isUp, bool isMissileCheck);

	int getX();
	int getY();
	bool getIsUp();
};