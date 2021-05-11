#pragma once

class Note
{
private:
	int index = 1; //1~7
	int x = 0;
	int y = 0;

public:
	void initNote();

	void drawNote();
	void downNote();

	void checkEnd();
	void checkInput();
	bool checkNote(int input);

	void playerSound();
};