#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "MainDlg.h"
#include "FiveMain.H"

BOOL	Main_Erase(HWND hwnd, HDC hdc)
{
	return TRUE;
}

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);
		HANDLE_MSG(hWnd,WM_PAINT,Five_Draw);
		HANDLE_MSG(hWnd,WM_LBUTTONDOWN,Five_Mouse);
		HANDLE_MSG(hWnd,WM_TIMER,Five_Timer);
		HANDLE_MSG(hWnd,WM_ERASEBKGND,Main_Erase);
	}

    return FALSE;
}

BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    return TRUE;
}

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {
		case IDD_ABOUT:
			MessageBox(hwnd	,TEXT("有Bug请发送到BigChen2012@gmail.com,谢谢!"),TEXT("提示"),MB_OK);	
			break;
		case IDD_START:
			ResetFiveGame(hwnd);
			ResetDraw(hwnd);
			g_bStart=TRUE;g_bCtrlFlag=FALSE;
			SetTimer(hwnd	,8001	,1000	,NULL);
			break;
		case IDD_RESET:
			ResetFiveGame(hwnd);
			ResetDraw(hwnd);
			g_bStart=TRUE;
			SetTimer(hwnd	,8001	,1000	,NULL);
			break;
		case IDD_QUIT:
			KillTimer(hwnd	,8001);
			EndDialog(hwnd,0);
			break;
        default:
		break;
    }
}

void Main_OnClose(HWND hwnd)
{
	KillTimer(hwnd	,8001);
    EndDialog(hwnd, 0);
}