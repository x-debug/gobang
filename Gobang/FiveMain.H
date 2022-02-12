#include <windows.h>
#define Round(x) (((x) >= 0.0) ? ((int)((x) + 0.5)) : (-(int)(-(x) + 0.5)))
#ifndef _FIVE_MAIN_
#define _FIVE_MAIN_
extern	BOOL	g_bStart;
extern	int		g_Chess[15][15];
extern	BOOL	g_bCtrlFlag;
extern	int		g_LastX;extern	int		g_LastY;
VOID	Five_Draw(HWND	hWnd);
VOID	Five_Mouse(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
VOID	Five_Timer(HWND hwnd, UINT id);
VOID	ResetFiveGame(HWND	hWnd);
VOID	ResetDraw(HWND	hWnd);
VOID CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);
#endif