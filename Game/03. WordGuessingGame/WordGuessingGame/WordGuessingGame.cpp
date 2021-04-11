#include <iostream>
#include <conio.h>
#include <string.h>
using namespace std;

struct tag_Question {
	string question;
	string answer;
	int wordCount;
};

tag_Question question[] = {
	{"*****", "apple", 5},
	{"*******", "english", 7},
	{"********", "computer", 8},
	{"****", "game", 4},
	{"********", "february", 8}
};

int main()
{
	cout << "---------------------------------" << endl;
	cout << "|     단어 맞히기 게임          |" << endl;
	cout << "---------------------------------" << endl;
	cout << "|   설명 : 알파벳을 누르세요.   |" << endl;
	cout << "---------------------------------" << endl;

	string tempQuestion[] = { question[0].question, question[1].question, question[2].question, question[3].question, question[4].question };
	int questionCount = 5;
	char ch;

	for (int i = 0; i < questionCount; i++)
	{
		cout << endl << endl;
		cout << i + 1 <<"번째 문제" << endl;
		cout << tempQuestion[i];

		while (tempQuestion[i] != question[i].answer)
		{
			ch = _getch();
			cout << " " << ch << endl;

			for (int j = 0; j < question[i].wordCount; j++)
			{
				if (ch == question[i].answer[j])
				{
					tempQuestion[i][j] = ch;
				}
			}

			cout << tempQuestion[i];
		}
	}

	cout << endl;

	return 0;
}