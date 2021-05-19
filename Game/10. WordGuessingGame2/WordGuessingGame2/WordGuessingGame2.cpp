#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void gotoXY(int x, int y)
{
	COORD cur;
	cur.X = x * 2;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}

	return 0;
}

vector<string> pastWord;
vector<string> strWords;

void SetConsoleView()
{
	system("mode con:cols=50 lines=20");
	system("title WORD GAME");
}

void DrawReadyGame()
{
	system("cls");
	gotoXY(5, 2);
	cout << "==============================";
	gotoXY(5, 3);
	cout << "========= WORD GAME ==========";
	gotoXY(5, 4);
	cout << "==============================";
	gotoXY(6, 6);
	cout << "시작하려면 's를 누르세요";
	gotoXY(20, 18);
}

bool ReadyGame()
{
	DrawReadyGame();

	while (true)
	{
		int key = GetKeyDown();
		key = tolower(key);

		if (key == 's')
		{
			return true;
		}
	}

	return false;
}

void SetWords()
{
	string str[4] = { "apple", "banana", "code", "program" };

	ifstream readFromFile("words.txt");

	if (!readFromFile.is_open())
	{
		ofstream writeToFile("words.txt");

		for (int i = 0; i < 4; i++)
		{
			string temp = str[i];
			if (i < 3)
			{
				temp += "\n";
			}

			writeToFile.write(temp.c_str(), temp.size());
			strWords.push_back(str[i]);
		}

		writeToFile.close();
	}
	else
	{
		while (!readFromFile.eof())
		{
			string temp;
			getline(readFromFile, temp);
			strWords.push_back(temp);
		}

		readFromFile.close();
	}
}

void DrawStartGame()
{
	system("cls");

	gotoXY(5, 8);
	cout << "past = ";
	for (int i = 0; i < (int)pastWord.size(); i++)
	{
		cout << pastWord[i] << " ";
	}

	gotoXY(5, 12);
	cout << "input = ";
}

void StartGame()
{
	srand((unsigned)time(NULL));

	SetWords();

	while (true)
	{
		int num = rand() % (int)strWords.size();
		bool isSame = false;
		string strOriginal = strWords[num];
		int originalLen = (int)strOriginal.length();

		string strQuestion;
		for (int i = 0; i < originalLen; i++)
		{
			strQuestion += "_";
		}

		while (true)
		{
			DrawStartGame();
			isSame = false;

			gotoXY(5, 5);
			for (int i = 0; i < originalLen; i++)
			{
				cout << strQuestion[i] << " ";
			}
			cout << endl;

			gotoXY(9, 12);
			string strInput;
			cin >> strInput;

			for (int i = 0; i < (int)pastWord.size(); i++)
			{
				if (pastWord[i] == strInput)
				{
					isSame = true;
					break;
				}
			}

			if (isSame) continue;

			pastWord.push_back(strInput);

			if (strInput.length() == 1)
			{
				for (int i = 0; i < originalLen; i++)
				{
					if (strOriginal[i] == strInput[0])
					{
						strQuestion[i] = strInput[0];
					}
				}
			}
			else if (strInput.length() > 1)
			{
				if (strOriginal == strInput)
				{
					pastWord.clear();
					break;
				}
			}
		}

		DrawStartGame();
	}
}

int main()
{
	SetConsoleView();

	while (true)
	{
		if (ReadyGame())
		{
			StartGame();
		}
	}

	return 0;
}