#pragma once

#include <Windows.h>

//���� ���� �̸�
#define FNAME "score"

//Ŀ�� �̵�
void gotoXY(int x, int y);
//Ŀ�� �Ⱥ��̰� ����
void setcursor(bool i, DWORD size);
//����
void Save();
//�ҷ�����
void Load();

char getCH();