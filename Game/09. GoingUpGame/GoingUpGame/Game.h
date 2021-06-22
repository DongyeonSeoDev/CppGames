#pragma once

#include <vector>
#include <ctime>

using namespace std;

//방향키 번호
#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

//점수 저장
struct Score
{
	int score;
};

//플레이어 좌표
extern int playerX, playerY;

//적과 아이템 좌표
extern vector<int> enemyX, enemyY;
extern vector<int> itemX, itemY, itemData;

extern Score score;

extern int bestScore;

extern int height;
extern int speed;
extern clock_t startTime;

extern int minusSpeed; //마이너스 스피드
extern bool isInvincibility; //현재 무적인지 확인
extern int startItemHeight; //무적 유지 시간

void inputCheck();
void currentState();
void createEnemy(int creatEnemyProbability);
void createItem();
void collisionEnemy();
void collisionItem();
void gameOver();