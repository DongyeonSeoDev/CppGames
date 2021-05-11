#include "Note.h"
#include "Console.h"
#include <iostream>

using namespace std;

void Note::initNote()
{
	index = rand() % 7 + 1;
	x = index * 2;
	y = 0;
}

void Note::drawNote()
{
	gotoXY(x, y);
	setTextColor(14);
	cout << "Q";
	setTextColor(15);
}

void Note::downNote()
{
	y++;
}

void Note::checkEnd()
{
	if (y == 12)
	{
		initNote();
	}
}

void Note::checkInput()
{
	if (checkNote(input()))
	{
		playerSound();
		initNote();
	}
}

bool Note::checkNote(int input)
{
	return index == input && y == 11;
}

void Note::playerSound()
{
	int tone[7] = { 523, 587, 659, 698, 784, 880, 988 };
	beep(tone[index - 1], 500);
}