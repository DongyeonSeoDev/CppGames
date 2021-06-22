#include "Color.h"

#include <Windows.h>

//»ö±ò º¯°æ
void scolor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}