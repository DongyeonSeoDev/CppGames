#pragma once

class Missile
{
private:
	int x;
	int y;

	bool bMoveLeft; // �������� �̵� ����

public:
	void setMissile(int _y);
	void moveMissile();
	void drawMissile();

	bool checkEnd();
	bool checkCollision(Missile missile);
	bool checkPlayer(int playerX, int playerY, bool bMoveDown);
};