/*
#################################################################################################
*FileName:FiveMain.cpp
*Brief:
*��Ҫ�������������Ļ滭,��Ӧ�����Ϣ
#################################################################################################
*/
#include "FiveMain.H"
#include "Draw.H"
#include "Bot.H"
/*########################################GLOBAL VARIANT#########################################*/
BOOL	g_bStart=FALSE;/*��ʼ��־λ*/
int		g_Chess[15][15]={0};/*����λ�ñ�־��,State:1�����ɫ,2�����ɫ*/
BOOL	g_bCtrlFlag=FALSE;/*����ʱ���Ʊ�־*/
int		g_LastX,g_LastY;/*��һ��(X,Y)��*/
VOID	Five_Draw(HWND	hWnd)
/*
�����ͼ�Ȳ���
*/
{
		HDC	hMem;HBITMAP	hBitmap;
		tagRECT	Rect;
		int ClientW,ClientH;
		GetClientRect(hWnd	,&Rect);
		/*�ͻ����Ĵ�С*/
		ClientW	=	Rect.right-Rect.left;ClientH	=	Rect.bottom-Rect.top;
		HDC	hdcGrid=GetDC(hWnd);
		hMem	=	CreateCompatibleDC(NULL);
		hBitmap	=	CreateCompatibleBitmap(hdcGrid	,ClientW	,ClientH);
		HBITMAP	hOldBitmap=(HBITMAP)SelectObject(hMem	,(HGDIOBJ)hBitmap);
		Rect.left=0;Rect.top=0;Rect.right=ClientW;Rect.bottom=ClientH;
		HBRUSH	hBrush=CreateSolidBrush(RGB(255,255,255));
		FillRect(hMem	,&Rect	,hBrush);
		/*���Ʊ����*/
		DrawGrid(hMem);
		/*�����ӣ�������������*/
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
		/*����֧��˫����*/
		BitBlt(hdcGrid	,0	,0	,ClientW	,ClientH	,hMem	,0	,0	,SRCCOPY);
		DeleteObject((HGDIOBJ)hBrush);
		DeleteObject((HGDIOBJ)hBitmap);
		DeleteDC(hMem);
		ReleaseDC(hWnd	,hdcGrid);
}

int		CoordtoXY(int x,int y,int *i,int *j)
/*ʹ���������㾫ȷ���ڽ����(x,y)��*/
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
	if (FALSE	==	g_bCtrlFlag)/*���ͬ����־*/
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
			g_LastX=j;g_LastY=i;/*��¼���һ�����ӵ㣬Ϊ�˱�ʶ���������״̬*/
			g_Chess[i][j]=1;g_bFive_Model_Deattack[i][j]=FALSE;g_bFive_Model_Attack[i][j]=FALSE;/*Ϊ�˺����������ٶ��Ż������︶һ����־ֵ*/
			Rect.left=x-ONE_AREA;Rect.right=x+ONE_AREA;Rect.top=y-ONE_AREA;Rect.bottom=y+ONE_AREA;
			InvalidateRect(hwnd	,&Rect	,TRUE);
			if(IsWin(j,i,1)==1)/*�ж�ʤ��ֵ*/
			{
				ResetFiveGame(hwnd);
				MessageBox(hwnd	,TEXT("�ڷ�ʤ��"),TEXT("��ʾ"),MB_OK);
				ResetDraw(hwnd);
			}
			g_bCtrlFlag=TRUE;
		}
	}
}

VOID	Five_Timer(HWND hwnd, UINT id)
/*
ʱ�䴥������,�ü�ʱ��ȥ�ȴ��û�������ϡ�
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