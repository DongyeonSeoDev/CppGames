#include <iostream>
#include <time.h>

#include "Note.h"
#include "Console.h"

using namespace std;

void drawScreen()
{
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "|               |" << endl;
	cout << "  1 2 3 4 5 6 7  " << endl;

	gotoXY(1, 10);
	setTextColor(1);
	cout << "---------------";
	setTextColor(15);
}

int main()
{
	srand((unsigned)time(NULL));

	int index = rand() % 7 + 1;

	Note* note = new Note();
	note->initNote();

	while (true)
	{
		drawScreen();

		note->drawNote();

		gotoXY(16, 12);

		note->downNote();
		note->checkEnd();
		note->checkInput();

		sleep(100);
		system("cls");
	}

	return 0;
}