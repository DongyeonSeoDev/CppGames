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

	int getX();
	int getY();
};