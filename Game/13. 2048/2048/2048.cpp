#include "Game.h"

using namespace std;

int main()
{
	setConsoleView();

	initData();
	initDraw();

	createNumber();
	createNumber();

	while (true)
	{
		getKey();
		checkGameOver();
	}

	return 0;
}