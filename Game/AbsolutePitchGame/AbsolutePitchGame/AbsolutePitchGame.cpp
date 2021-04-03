#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;

const int Tone[8] = { 523, 587, 659, 698, 784, 880, 988, 1046 };
const string name[8] = { "도", "레", "미", "파", "솔", "라", "시", "도" };

int main()
{
	int selectTone = 0;
	int select = 0;

	srand((unsigned int)time(NULL));

	while (1)
	{
		for (int i = 0; i < 8; i++)
		{
			cout << name[i] << "(" << i + 1 << ") ";
			Beep(Tone[i], 500);
		}

		cout << "종료(0) ";
		Sleep(500);

		cout << "!!준비!!" << endl;
		Sleep(1000);
		selectTone = rand() % 8;
		Beep(Tone[selectTone], 500);

		select = _getch() - '1';

		if (select == selectTone)
		{
			cout << "GOOD" << endl;
		}
		else if (select == -1)
		{
			cout << "게임종료" << endl;
			return 0;
		}
		else
		{
			cout << "NOT " << name[selectTone] << endl;
		}
	}
	return 0;
}