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
	{"*****", "apple", 5}
};

int main()
{
	cout << "---------------------------------" << endl;
	cout << "|     단어 맞히기 게임          |" << endl;
	cout << "---------------------------------" << endl;
	cout << "|   설명 : 알파벳을 누르세요.   |" << endl;
	cout << "---------------------------------" << endl;

	string tempQuestion = question[0].question;
	char ch;
	cout << tempQuestion;

	while (tempQuestion != question[0].answer)
	{
		ch = _getch();
		cout << " " << ch << endl;

		for (int j = 0; j < question[0].wordCount; j++)
		{
			if (ch == question[0].answer[j])
			{
				tempQuestion[j] = ch;
			}
		}

		cout << tempQuestion;
	}

	return 0;
}