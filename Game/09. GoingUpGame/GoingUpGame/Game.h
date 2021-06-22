#pragma once

#include <vector>
#include <ctime>

using namespace std;

//����Ű ��ȣ
#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

//���� ����
struct Score
{
	int score;
};

//�÷��̾� ��ǥ
extern int playerX, playerY;

//���� ������ ��ǥ
extern vector<int> enemyX, enemyY;
extern vector<int> itemX, itemY, itemData;

extern Score score;

extern int bestScore;

extern int height;
extern int speed;
extern clock_t startTime;

extern int minusSpeed; //���̳ʽ� ���ǵ�
extern bool isInvincibility; //���� �������� Ȯ��
extern int startItemHeight; //���� ���� �ð�

void inputCheck();
void currentState();
void createEnemy(int creatEnemyProbability);
void createItem();
void collisionEnemy();
void collisionItem();
void gameOver();