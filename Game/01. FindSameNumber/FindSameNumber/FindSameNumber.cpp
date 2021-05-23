#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

void showKey()
{
	cout << "12345" << endl;
	cout << "qwert" << endl;
	cout << "asdfg" << endl;
	cout << "zxcvb" << endl;
	cout << endl << "위에 있는 키를 누르면 각 칸의 숫자가 보입니다." << endl;
	cout << "키를 2개를 누르면 됩니다." << endl;
	cout << "같은 숫자를 누르면 성공 다른 숫자를 누르면 실패 입니다." << endl << endl << endl;
	
	cout << "      -게임을 시작하려면 아무키나 눌러주세요-";

	_getch();

	system("cls");
}

int main()
{
	showKey();

	int answer[20];
	int index = 1;

	for (int i = 0; i < 20; i++)
	{
		answer[i] = -1;
	}

	srand((unsigned)time(NULL));

	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			do
			{
				index = rand() % 20;
			} while (answer[index] != -1);
			answer[index] = i;
		}
	}

	for (int i = 0; i < 20; i++)
	{
		gotoXY(i % 5, i / 5);
		cout << answer[i];
	}

	Sleep(3000);
	system("cls");

	for (int i = 0; i < 20; i++)
	{
		gotoXY(i % 5, i / 5);
		cout << "*";
	}

	char keyCode[20] = {
		'1', '2', '3', '4', '5',
		'q', 'w', 'e', 'r', 't',
		'a', 's', 'd', 'f', 'g',
		'z', 'x', 'c', 'v', 'b'
	};

	int selectIndex[2] = { 0, };
	int check = 0;
	int failCount = 0;
	int correntCount = 0;

	while (true)
	{
		int key = _getch();

		for (int i = 0; i < 20; i++)
		{
			if (key == keyCode[i] && answer[i] != -1)
			{
				if (check == 0 || selectIndex[0] != i)
				{
					selectIndex[check] = i;
					gotoXY(i % 5, i / 5);
					cout << answer[i];

					check++;

					break;
				}
			}
		}

		if (check == 2)
		{
			if (answer[selectIndex[0]] != answer[selectIndex[1]])
			{
				Sleep(1000);

				for (int i = 0; i < 2; i++)
				{
					gotoXY(selectIndex[i] % 5, selectIndex[i] / 5);
					cout << "*";
				}

				failCount++;
			}
			else
			{
				answer[selectIndex[0]] = -1;
				answer[selectIndex[1]] = -1;

				correntCount++;

				if (correntCount == 10)
				{
					system("cls");
					gotoXY(0, 0);
					cout << "클리어!" << endl;
					cout << "실패 횟수: " << failCount << endl;
					return 0;
				}
			}

			check = 0;
		}
	}

	return 0;
}