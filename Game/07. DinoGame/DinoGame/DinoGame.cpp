#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define DINO_TOP_Y 1
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_X 45
#define TREE_BOTTOM_Y 20
#define BULLET_X 8
#define BULLET_Y 21
#define JUMP 1
#define SHOT 2

void gotoXY(int x, int y)
{
    HANDLE hOut;
    COORD Cur;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Cur.X = x * 2;
    Cur.Y = y;
    SetConsoleCursorPosition(hOut, Cur);
}

void clrscr()
{
    system("cls");
}

bool bLegFlag;

void setConsoleView()
{
    system("mode con:cols=100 lines=25");
    system("title 공룡 게임");
}

void drawDino(int posY)
{
    gotoXY(0, posY);
    cout << "        $$$$$$$ " << endl;
    cout << "       $$ $$$$$$" << endl;
    cout << "       $$$$$$$$$" << endl;
    cout << "$      $$$      " << endl;
    cout << "$$     $$$$$$$  " << endl;
    cout << "$$$   $$$$$     " << endl;
    cout << " $$  $$$$$$$$$$ " << endl;
    cout << " $$$$$$$$$$$    " << endl;
    cout << "  $$$$$$$$$$    " << endl;
    cout << "    $$$$$$$$    " << endl;
    cout << "     $$$$$$     " << endl;

    if (bLegFlag)
    {
        cout << "     $    $$$   " << endl;
        cout << "     $$         ";
    }
    else
    {
        cout << "     $$$  $     " << endl;
        cout << "          $$    ";
    }

    bLegFlag = !bLegFlag;
}

void drawTree(int posX)
{
    gotoXY(posX, TREE_BOTTOM_Y);
    cout << "$$$$";
    gotoXY(posX, TREE_BOTTOM_Y + 1);
    cout << " $$ ";
    gotoXY(posX, TREE_BOTTOM_Y + 2);
    cout << " $$ ";
    gotoXY(posX, TREE_BOTTOM_Y + 3);
    cout << " $$ ";
    gotoXY(posX, TREE_BOTTOM_Y + 4);
    cout << " $$ ";
}

void drawGameover(int score)
{
    gotoXY(10, 10);
    cout << "GAME OVER!!";
    gotoXY(10, 11);
    cout << "SCORE: " << score;
}

void drawBullet(int posX)
{
    gotoXY(posX, BULLET_Y);
    cout << "O" << endl;
}

void drawScore(int score)
{
    gotoXY(40, 0);
    cout << "Score: " << score;
}

int getKeyDown()
{
    if (_kbhit() != 0)
    {
        switch (_getch())
        {
        case 'j':
            return JUMP;
            break;
        case 'a':
            return SHOT;
            break;
        }
    }

    return 0;
}

int main(void)
{
    bLegFlag = false;
    bool isJumping = false;
    bool isBottom = true;
    bool isGameover = false;
    bool isShot = false;

    const int gravity = 3;

    int dinoY = DINO_BOTTOM_Y;
    int treeX = TREE_BOTTOM_X;
    int bulletX = BULLET_X;
    int score = 0;

    setConsoleView();

    while (true)
    {
        switch (getKeyDown())
        {
        case JUMP:
            if (isBottom && !isGameover)
            {
                isJumping = true;
                isBottom = false;
            }
            break;
        case SHOT:
            if (!isShot && !isGameover)
            {
                isShot = true;
            }
            break;
        }
        if (treeX <= 6 && dinoY >= DINO_BOTTOM_Y - 4)
        {
            isGameover = true;
        }

        if (!isGameover)
        {
            if (isJumping)
            {
                dinoY -= gravity;
            }
            else
            {
                dinoY += gravity;
            }

            if (dinoY <= DINO_TOP_Y)
            {
                dinoY = DINO_TOP_Y;
                isJumping = false;
            }
            else if (dinoY >= DINO_BOTTOM_Y)
            {
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            treeX -= 2;

            if (treeX <= 0)
            {
                treeX = TREE_BOTTOM_X;
            }
            else if (treeX - 1 <= bulletX && treeX + 1 >= bulletX && isShot)
            {
                treeX = TREE_BOTTOM_X;
                isShot = false;
                bulletX = BULLET_X;
                score++;
            }

            if (isShot)
            {
                bulletX += 1;
                drawBullet(bulletX);

                if (bulletX >= 45)
                {
                    isShot = false;
                    bulletX = BULLET_X;
                }
            }

            drawDino(dinoY);
            drawTree(treeX);
            drawScore(score);
        }
        else
        {
            drawGameover(score);
        }

        Sleep(80);
        clrscr();
    }

    return 0;
}