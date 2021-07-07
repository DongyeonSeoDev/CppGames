#include "Game.h"

using namespace std;

int main()
{
	setConsoleView();

	start();

	initData();
	initDraw();

	createNumber();
	createNumber(); 

	showScore();

	while (true)
	{
		getKey();
		checkGameOver();
	}

	return 0;
}