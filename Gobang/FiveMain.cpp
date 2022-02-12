/*
#################################################################################################
*FileName:FiveMain.cpp
*Brief:
*主要处理关于五子棋的绘画,相应鼠标消息
#################################################################################################
*/
#include "FiveMain.H"
#include "Draw.H"
#include "Bot.H"
/*########################################GLOBAL VARIANT#########################################*/
BOOL	g_bStart=FALSE;/*起始标志位*/
int		g_Chess[15][15]={0};/*棋盘位置标志表,State:1代表黑色,2代表白色*/
BOOL	g_bCtrlFlag=FALSE;/*下棋时控制标志*/
int		g_LastX,g_LastY;/*上一个(X,Y)点*/
VOID	Five_Draw(HWND	hWnd)
/*
处理绘图等操作
*/
{
		HDC	hMem;HBITMAP	hBitmap;
		tagRECT	Rect;
		int ClientW,ClientH;
		GetClientRect(hWnd	,&Rect);
		/*客户区的大小*/
		ClientW	=	Rect.right-Rect.left;ClientH	=	Rect.bottom-Rect.top;
		HDC	hdcGrid=GetDC(hWnd);
		hMem	=	CreateCompatibleDC(NULL);
		hBitmap	=	CreateCompatibleBitmap(hdcGrid	,ClientW	,ClientH);
		HBITMAP	hOldBitmap=(HBITMAP)SelectObject(hMem	,(HGDIOBJ)hBitmap);
		Rect.left=0;Rect.top=0;Rect.right=ClientW;Rect.bottom=ClientH;
		HBRUSH	hBrush=CreateSolidBrush(RGB(255,255,255));
		FillRect(hMem	,&Rect	,hBrush);
		/*绘制表格区*/
		DrawGrid(hMem);
		/*花棋子，画出整个数组*/
		for (int i=0	;i<15	;i++)
		{
			for (int j=0	;j<15	;j++)
			{
				if (1	==	g_Chess[i][j])
					DrawChess(hMem	,i,j,1);
				else if (2	==	g_Chess[i][j])
					DrawChess(hMem	,i,j,2);
			}
		}
		/*这里支持双缓存*/
		BitBlt(hdcGrid	,0	,0	,ClientW	,ClientH	,hMem	,0	,0	,SRCCOPY);
		DeleteObject((HGDIOBJ)hBrush);
		DeleteObject((HGDIOBJ)hBitmap);
		DeleteDC(hMem);
		ReleaseDC(hWnd	,hdcGrid);
}

int		CoordtoXY(int x,int y,int *i,int *j)
/*使点击的坐标点精确落在界面的(x,y)上*/
{
	double m1=x,m2=y;
	m1=(m1-FIVE_WIDTH_BORDER)/ONE_AREA;
	m2=(m2-FIVE_HEIGH_BORDER)/ONE_AREA;
	m1=Round(m1);m2=Round(m2);
	(*j)=(int)m1;(*i)=(int)m2;
	return 0;
}

VOID	Five_Mouse(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	int i,j;
	tagRECT	Rect;
	if (FALSE	==	g_bCtrlFlag)/*鼠标同步标志*/
	{
		if (TRUE	==	g_bStart)
		{
			if((x<FIVE_WIDTH_BORDER	||	x>MAX_FIVE_WIDTH-FIVE_WIDTH_BORDER)	\
			||	(y<FIVE_HEIGH_BORDER	||	y>MAX_FIVE_HEIGH-FIVE_HEIGH_BORDER))
			{
				MessageBeep(-1);
				return ;
			}	
			CoordtoXY(x,y,&i,&j);
			if(0	!=	g_Chess[i][j])
			{
				MessageBeep(-1);
				return ;
			}
			g_LastX=j;g_LastY=i;/*记录最后一个下子点，为了标识最近的棋子状态*/
			g_Chess[i][j]=1;g_bFive_Model_Deattack[i][j]=FALSE;g_bFive_Model_Attack[i][j]=FALSE;/*为了后面搜索的速度优化，这里付一个标志值*/
			Rect.left=x-ONE_AREA;Rect.right=x+ONE_AREA;Rect.top=y-ONE_AREA;Rect.bottom=y+ONE_AREA;
			InvalidateRect(hwnd	,&Rect	,TRUE);
			if(IsWin(j,i,1)==1)/*判断胜负值*/
			{
				ResetFiveGame(hwnd);
				MessageBox(hwnd	,TEXT("黑方胜出"),TEXT("提示"),MB_OK);
				ResetDraw(hwnd);
			}
			g_bCtrlFlag=TRUE;
		}
	}
}

VOID	Five_Timer(HWND hwnd, UINT id)
/*
时间触发函数,用计时器去等待用户输入完毕。
*/
{
	if(g_bCtrlFlag	==TRUE)
	{
		BotMain(hwnd);
		g_bCtrlFlag=FALSE;
	}
}

VOID CALLBACK TimerProc(
						HWND hwnd,         
						UINT uMsg,
						UINT_PTR idEvent,  
						DWORD dwTime       
						)
{
	if(g_bCtrlFlag	==TRUE)
	{
		BotMain(hwnd);
		g_bCtrlFlag=FALSE;
	}
}

VOID	ResetFiveGame(HWND	hWnd)
{
	g_bStart=FALSE;g_bCtrlFlag=FALSE;
	KillTimer(hWnd	,8001);
	InvalidateRect(hWnd	,NULL	,TRUE);
}

VOID	ResetDraw(HWND	hWnd)
{
	int i,j;
	for (i=0	;i<15	;i++)
		for(j=0	;j<15	;j++)
		{
				g_Chess[i][j]=0;g_Five_Model_Attack[i][j]=0;g_Five_Model_Deattack[i][j]=0;
				g_bFive_Model_Attack[i][j]=g_bFive_Model_Deattack[i][j]=TRUE;
		}
	InvalidateRect(hWnd	,NULL	,TRUE);
}