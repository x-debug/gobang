/*############################################################################################
*FileName:Draw.cpp
*Brief:
*�������̺����ӵĻ��ӵ�����
*#############################################################################################*/
#include "Draw.H"
#include "FiveMain.H"

int		DrawGrid(HDC	hdcGrid)
/*
Brief:��ֱ�߻�������,�������̵�����
*/
{
	          
	POINT	tagOldPoint;
	for (int i=0	;i<15	;i++)
	{
		MoveToEx(hdcGrid	,FIVE_WIDTH_BORDER,FIVE_HEIGH_BORDER+i*ONE_AREA,&tagOldPoint);
		LineTo(hdcGrid	,MAX_FIVE_WIDTH-FIVE_WIDTH_BORDER,FIVE_HEIGH_BORDER+i*ONE_AREA);
	}

	for (int j=0	;j<15	;j++)
	{
		MoveToEx(hdcGrid	,FIVE_WIDTH_BORDER+j*ONE_AREA,FIVE_HEIGH_BORDER,&tagOldPoint);
		LineTo(hdcGrid	,FIVE_WIDTH_BORDER+j*ONE_AREA,MAX_FIVE_HEIGH-FIVE_HEIGH_BORDER);
	}
	return 0;
}

int		DrawChess(HDC	hChess,int y,int x,int c)
/*
Brief:�ڵ�λ(X,Y)������ɫ����ΪC������
*/
{
	POINT	tagPoint;
	HPEN	hPen=CreatePen(PS_SOLID	,1	,RGB(255,255,255));
	HPEN	hOldPen=(HPEN)SelectObject(hChess	,hPen);
	MoveToEx(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2,&tagPoint);
	LineTo(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2+ONE_CHESS,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2);
	
	MoveToEx(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2+ONE_CHESS,&tagPoint);
	LineTo(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2+ONE_CHESS,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2+ONE_CHESS);
	
	MoveToEx(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2,&tagPoint);
	LineTo(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2+ONE_CHESS);
	
	MoveToEx(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2+ONE_CHESS,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2,&tagPoint);
	LineTo(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2+ONE_CHESS,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2+ONE_CHESS);
	SelectObject(hChess	,(HGDIOBJ)hOldPen);
	DeleteObject(hPen);
	if (1	==	c)
	{
		HBRUSH	 hBrush=CreateSolidBrush(RGB(80,80,80));
		HBRUSH	hOldBrush=(HBRUSH)SelectObject(hChess	,hBrush);
		Ellipse(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2,FIVE_WIDTH_BORDER+x*ONE_AREA+ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA+ONE_CHESS/2);
		SelectObject(hChess	,(HGDIOBJ)hOldBrush);
		DeleteObject(hBrush);
	}else if (2	== c)
	{
		HBRUSH	 hBrush=CreateSolidBrush(RGB(192,0,78));
		HBRUSH	hOldBrush=(HBRUSH)SelectObject(hChess	,hBrush);
		Ellipse(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2,FIVE_WIDTH_BORDER+x*ONE_AREA+ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA+ONE_CHESS/2);
		SelectObject(hChess	,(HGDIOBJ)hOldBrush);
		DeleteObject(hBrush);
	}
	if(x	==	g_LastX	&&	y	==	g_LastY)
	{
		HPEN	hPen=CreatePen(PS_SOLID	,1	,RGB(255,0,0));
		HPEN	hOldPen=(HPEN)SelectObject(hChess	,hPen);
		MoveToEx(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2,&tagPoint);
		LineTo(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2+ONE_CHESS,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2);

		MoveToEx(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2+ONE_CHESS,&tagPoint);
		LineTo(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2+ONE_CHESS,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2+ONE_CHESS);

		MoveToEx(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2,&tagPoint);
		LineTo(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2+ONE_CHESS);

		MoveToEx(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2+ONE_CHESS,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2,&tagPoint);
		LineTo(hChess	,FIVE_WIDTH_BORDER+x*ONE_AREA-ONE_CHESS/2+ONE_CHESS,FIVE_HEIGH_BORDER+y*ONE_AREA-ONE_CHESS/2+ONE_CHESS);
		SelectObject(hChess	,(HGDIOBJ)hOldPen);
		DeleteObject(hPen);
	}
	return 0;
}
