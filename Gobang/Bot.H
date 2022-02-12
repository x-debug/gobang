#include <windows.h>

#ifndef _FIVE_BOT_
#define _FIVE_BOT_
extern	int	g_Five_Model_Attack[15][15];
extern	int g_Five_Model_Deattack[15][15];
extern	BOOL	g_bFive_Model_Attack[15][15];
extern BOOL	g_bFive_Model_Deattack[15][15];

int BotMain(HWND	hWnd);
int IsWin(int x,int y,int color);
#endif