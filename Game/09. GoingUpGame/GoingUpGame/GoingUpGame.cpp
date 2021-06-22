#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include "Map.h"
#include "Color.h"
#include "System.h"
#include "Game.h"
#include "Sound.h"

using namespace std;

int main()
{
	Load();

	system("title UP! 게임");
	setcursor(false, 1);
	SoundSystem();

	srand((unsigned)time(NULL));

	height = 0; //현재 높이
	speed = 0; //현재 속도
	int creatEnemyProbability = 10; //적 생성 확률

	minusSpeed = 0; //마이너스 스피드
	isInvincibility = false; //현재 무적인지 확인
	startItemHeight = 0; //무적 유지 시간

	playerX = 27;
	playerY = 21;

	start();

	while (true)
	{
		char ch = getCH();
		ch = tolower(ch);

		if (ch == 's') //s면 게임 시작
		{
			Beep(784, 200);
			break;
		}
		else if (ch == 'q') //q면 설명 화면
		{
			Beep(698, 200);
			description();

			while (true)
			{
				char ch = getCH();
				ch = tolower(ch);

				if (ch == 'x') //x면 돌아가기
				{
					Beep(698, 200);
					start();
					break;
				}
			}
		}
	}

	startTime = clock(); //시간 시작
	PlaySound(TEXT("Music.wav"), NULL, SND_ASYNC | SND_LOOP); //노래 재생

	while (true)
	{
		//입력 체크
		inputCheck();

		system("cls");

		//현재 상태
		currentState();

		//높이별로 맵 출력
		if (height % 3 == 0)
		{
			drawMap(map);
		}
		else if (height % 3 == 1)
		{
			drawMap(map2);
		}
		else
		{
			drawMap(map3);
		}

		createEnemy(creatEnemyProbability); //적 생성

		createItem(); //아이템 생성

		collisionEnemy(); //적 충돌 체크

		collisionItem(); //아이템 충돌 체크

		//플레이어 이동
		height++;

		//스피드와 적 확률 확인
		speed = height / 100 - minusSpeed;
		creatEnemyProbability = height / 5;

		//스피드 예외처리
		if (speed < 0) speed = 0;
		else if (speed > 5) speed = 5;

		//적 생성 확률 예외처리
		if (creatEnemyProbability < 20) creatEnemyProbability = 20;
		else if (creatEnemyProbability > 100) creatEnemyProbability = 100;

		//아이템 시간이 끝났는지 확인
		if (isInvincibility && height - startItemHeight >= 30)
		{
			isInvincibility = false;
		}

		//높이가 100의 배수라면 효과음 재생
		if (height % 100 == 0)
		{
			Play(1, 1);
		}

		pSystem->update();

		Sleep(50 - speed * 10);
	}

	return 0;
}