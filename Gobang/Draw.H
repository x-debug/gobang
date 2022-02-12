/*
FileName:Draw.H
Brief:Draw.cpp的头文件
*/
#include <WINDOWS.H>
#include "FiveMain.H"

#ifndef _DRAW_FIVE_
#define _DRAW_FIVE_

#define MAX_FIVE_WIDTH		568
#define MAX_FIVE_HEIGH		540
#define FIVE_WIDTH_BORDER	32
#define FIVE_HEIGH_BORDER	18
#define ONE_AREA			36/*棋格大小*/
#define ONE_CHESS			28

int		DrawGrid(HDC	hdcGrid);
int		DrawChess(HDC	hChess,int x,int y,int c);
#endif