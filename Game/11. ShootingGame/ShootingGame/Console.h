#include <Windows.h>
#include <conio.h>

extern void gotoXY(int x, int y);
extern void setTextColor(int color);
extern void clrscr();
extern void beep(int tone, int delay);
extern void sleep(int delay);
extern int getKeyDown();