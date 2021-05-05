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
#define BIRD_BOTTOM_X 45
#define BIRD_BOTTOM_Y 2
#define UPBULLET_X 6
#define UPBULLET_Y 10

#define JUMP 1
#define SHOT 2
#define UPSHOT 3

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
    cout << "O";
}

void drawUpBullet(int posY)
{
    gotoXY(UPBULLET_X, posY);
    cout << "O";
}

void drawScore(int score)
{
    gotoXY(40, 0);
    cout << "Score: " << score;
}

void drawBird(int posX)
{
    gotoXY(posX, BIRD_BOTTOM_Y);
    cout << "$$$$$$$$$$";
    gotoXY(posX, BIRD_BOTTOM_Y + 1);
    cout << "$$$$$$$$$$";
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
        case 'u':
            return UPSHOT;
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
    bool isUp = false;

    const int gravity = 3;

    int dinoY = DINO_BOTTOM_Y;
    int treeX = TREE_BOTTOM_X;
    int bulletX = BULLET_X;
    int upBulletY = UPBULLET_Y;
    int score = 0;
    int birdX = BIRD_BOTTOM_X;

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
                isUp = false;
            }
            break;
        case UPSHOT:
            if (!isShot && !isGameover)
            {
                isShot = true;
                isUp = true;
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
            else if (treeX - 1 <= bulletX && treeX + 1 >= bulletX && isShot && !isUp)
            {
                treeX = TREE_BOTTOM_X;
                isShot = false;
                bulletX = BULLET_X;
                score++;
            }

            birdX -= 1;

            if (birdX <= 0)
            {
                birdX = BIRD_BOTTOM_X;
            }
            else if (birdX <= UPBULLET_X && birdX + 10 >= UPBULLET_X && BIRD_BOTTOM_Y <= upBulletY + 2 && BIRD_BOTTOM_Y >= upBulletY - 2 && isShot && isUp)
            {
                birdX = BIRD_BOTTOM_X;
                isShot = false;
                upBulletY = UPBULLET_Y;
                score++;
            }

            if (isShot)
            {
                if (isUp)
                {
                    upBulletY -= 1;
                    drawUpBullet(upBulletY);

                    if (upBulletY <= 0)
                    {
                        isShot = false;
                        upBulletY = UPBULLET_Y;
                    }
                }
                else
                {
                    bulletX += 1;
                    drawBullet(bulletX);

                    if (bulletX >= 45)
                    {
                        isShot = false;
                        bulletX = BULLET_X;
                    }
                }
            }

            drawDino(dinoY);
            drawTree(treeX);
            drawBird(birdX);
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