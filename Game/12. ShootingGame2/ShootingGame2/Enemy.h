#pragma once

class Enemy
{
private:
	int x;
	int y;

public:
	void setEnemy();
	void drawEnemy();
	bool checkEnd();
	bool checkPlayer(int playerX, int playerY);

	int getX();
	int getY();
};