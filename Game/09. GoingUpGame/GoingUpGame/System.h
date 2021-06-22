#pragma once

#include <Windows.h>

//저장 파일 이름
#define FNAME "score"

//커서 이동
void gotoXY(int x, int y);
//커서 안보이게 설정
void setcursor(bool i, DWORD size);
//저장
void Save();
//불러오기
void Load();

char getCH();