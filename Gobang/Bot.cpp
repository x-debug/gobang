/*
########################################################################################
*FileName:Bot.cpp
*Brief:
*实现人工智能判断和下棋
########################################################################################
*/
#include "Bot.H"
#include "FiveMain.H"
#include "Draw.h"
#define	FIVE_MODEL_COUNT	15
/*
########################################################################################
[棋型表]A代表同样颜色?代表空位
M[?AAAA?]300000->400000
AM[AAAAA]200000->500000
M[AAA?A]3000->3500
A[?AAA?]2700
[??AAA??]3000
[AA?AA]2600
[AAAA?]2500
[?A?AA?]800
[???AA???]650
M[A??AA]600->1000
[A?A?A]550
[AAA??]500
[??A?A??]250
[?A??A?]200
[AA???]150
########################################################################################
*/
static	g_Five_Model[FIVE_MODEL_COUNT][10]=\
{/*空格用0表示,相同颜色用1表示,不同颜色或者保留或者障碍用2表示*/
	{6,0,1,1,1,1,0,2,2,2},{5,1,1,1,0,1,2,2,2,2},\
	{7,0,0,1,1,1,0,0,2,2},{5,1,1,0,1,1,2,2,2,2},{5,1,1,1,1,0,2,2,2,2},\
	{6,0,1,0,1,1,0,2,2,2},{8,0,0,0,1,1,0,0,0,2},{5,1,0,0,1,1,2,2,2,2},\
	{5,1,0,1,0,1,2,2,2,2},{5,1,1,1,0,0,2,2,2,2},{7,0,0,1,0,1,0,0,2,2},\
	{6,0,1,0,0,1,0,2,2,2},{5,1,1,0,0,0,2,2,2,2},{5,1,1,1,1,1,2,2,2,2}\
//	{5,0,1,1,1,0,2,2,2,2}
};

static	g_Five_Value[FIVE_MODEL_COUNT]={400000,3500,3000,2600,2500,800,650,1000,550,500,250,200,150,500000/*,2700*/};
int	g_Five_Model_Attack[15][15]={0};/*黑色(攻击)棋型表,Note:这个棋型表只适合一层搜索*/
int g_Five_Model_Deattack[15][15]={0};
BOOL	g_bFive_Model_Attack[15][15]={TRUE};
BOOL	g_bFive_Model_Deattack[15][15]={TRUE};

int MateModel(int tagFive[10])
{
	int i,j,k,pFlag;
	int Sc,Ret,Max=0;
	for (i=0	;i<FIVE_MODEL_COUNT	;i++)
	{
		Sc=tagFive[0]-g_Five_Model[i][0]+1;/*比较的次数,这里用全模式匹配,没有优化算法*/
		if(Sc<=0)continue;
		for (j=1	;j<=Sc	;j++)/*正向反向都需要比较*/
		{
			pFlag=1;
			for (k=0	;k<g_Five_Model[i][0]	;k++)
			{
					if(g_Five_Model[i][k+1]	!=	tagFive[j+k])
					{
						pFlag=0;
						break;
					}
			}
			if(1	==	pFlag)
			{
				Ret	=	g_Five_Value[i];
				break;
			}else
			{
				for (j=tagFive[0]	;Sc>0	;--Sc,--j)
				{
					pFlag=1;
					for (k=0	;k<g_Five_Model[i][0]	;k++)
					{
						if (g_Five_Model[i][k+1]	!=	tagFive[j-k])
						{
							pFlag=0;
							break;
						}
					}
					if(1	==	pFlag)
					{
						Ret	=	g_Five_Value[i];
						break;
					}
				}
			}
		}
		if(Ret	>	Max)Max=Ret;
	}
	return Max;
}

int DoFastValuation(int x,int y,int Five_Model_Ary[15][15]	,BOOL	Five_Model_BOOL[15][15],int Color)
{
	int i,j,si,sj,ei,ej;char Buffer[255]={0};
	int k,m;int tagFive[10]={2};
	si=x-4;ei=x+4;sj=y-4;ej=y+4;
	/*计算开始边界和结束边界*/
	if (si<0)si=0;if(ei>14)ei=14;if(sj<0)sj=0;if(ej>14)ej=14;
	for (i=sj;i<=ej;i++)
	{
		for (j=si;j<=ei;j++)
		{
			if(Five_Model_BOOL[i][j]	==	FALSE)
			{
				g_Five_Model_Attack[i][j]=0;
				continue;
			}
			/*下面来说抽取模式数组*/
			for(k=1	;k<10	;k++)
				tagFive[k]=2;
			tagFive[0]=9;tagFive[5]=1;
			for (k=j-1,m=0	;k>=0&&k<=14&&m<4	;--k,m++)
			{
				if(g_Chess[i][k]	==	Color)
					tagFive[4-m]=1;
				else if (0	==	g_Chess[i][k])
					tagFive[4-m]=0;
				else
					break;
			}
			for (k=j+1,m=0	;k>=0&&k<=14&&m<4	;++k,m++)
			{
				if(g_Chess[i][k]	==	Color)
					tagFive[6+m]=1;
				else if (0	==	g_Chess[i][k])
					tagFive[6+m]=0;
				else
					break;
			}
			Five_Model_Ary[i][j]=MateModel(tagFive);
			
			for(k=1	;k<10	;k++)
				tagFive[k]=2;
			tagFive[0]=9;tagFive[5]=1;
			for (k=i-1,m=0	;k>=0&&k<=14&&m<4	;--k,m++)
			{
				if(g_Chess[k][j]	==	Color)
					tagFive[4-m]=1;
				else if (0	==	g_Chess[k][j])
					tagFive[4-m]=0;
				else
					break;
			}
			for (k=i+1,m=0	;k>=0&&k<=14&&m<4	;++k,m++)
			{
				if(g_Chess[k][j]	==	Color)
					tagFive[6+m]=1;
				else if (0	==	g_Chess[k][j])
					tagFive[6+m]=0;
				else
					break;
			}
			Five_Model_Ary[i][j]+=MateModel(tagFive);
			
			for(k=1	;k<10	;k++)
				tagFive[k]=2;
			tagFive[0]=9;tagFive[5]=1;
			for (k=i-1,m=1	;k>=0&&k<=14&&m<5	;--k,m++)
			{
				if(g_Chess[k][j-m]	==	Color)
					tagFive[5-m]=1;
				else if (0	==	g_Chess[k][j-m])
					tagFive[5-m]=0;
				else
					break;
			}
			for (k=i+1,m=1	;k>=0&&k<=14&&m<5	;++k,m++)
			{
				if(g_Chess[k][j+m]	==	Color)
					tagFive[5+m]=1;
				else if (0	==	g_Chess[k][j+m])
					tagFive[5+m]=0;
				else
					break;
			}
			Five_Model_Ary[i][j]+=MateModel(tagFive);
			
			for(k=1	;k<10	;k++)
				tagFive[k]=2;
			tagFive[0]=9;tagFive[5]=1;
			for (k=i-1,m=1	;k>=0&&k<=14&&m<5	;--k,m++)
			{
				if(g_Chess[k][j+m]	==	Color)
					tagFive[5-m]=1;
				else if (0	==	g_Chess[k][j+m])
					tagFive[5-m]=0;
				else
					break;
			}
			for (k=i+1,m=1	;k>=0&&k<=14&&m<5	;++k,m++)
			{
				if(g_Chess[k][j-m]	==	Color)
					tagFive[5+m]=1;
				else if (0	==	g_Chess[k][j-m])
					tagFive[5+m]=0;
				else
					break;
			}
			Five_Model_Ary[i][j]+=MateModel(tagFive);
		}
	}
	return 0;
}

int DoValuation(int Five_Model_Ary[15][15]	,BOOL	Five_Model_BOOL[15][15],int Color)
/*
对各个点位进行扫描估值,棋型表如上一个静态变量中g_Five_Model
*/
{
	int i,j,k,m;
	int tagFive[10]={2};
	for (i=0	;i<15	;i++)
	{
		for (j=0	;j<15	;j++)
		{
			if(Five_Model_BOOL[i][j]	==	FALSE)
			{
				g_Five_Model_Attack[i][j]=0;
				continue;
			}
			for(k=1	;k<10	;k++)
				tagFive[k]=2;
			tagFive[0]=9;tagFive[5]=1;
			for (k=j-1,m=0	;k>=0&&k<=14&&m<4	;--k,m++)
			{
				if(g_Chess[i][k]	==	Color)
					tagFive[4-m]=1;
				else if (0	==	g_Chess[i][k])
					tagFive[4-m]=0;
				else
					break;
			}
			for (k=j+1,m=0	;k>=0&&k<=14&&m<4	;++k,m++)
			{
				if(g_Chess[i][k]	==	Color)
					tagFive[6+m]=1;
				else if (0	==	g_Chess[i][k])
					tagFive[6+m]=0;
				else
					break;
			}
			Five_Model_Ary[i][j]=MateModel(tagFive);

			for(k=1	;k<10	;k++)
				tagFive[k]=2;
			tagFive[0]=9;tagFive[5]=1;
			for (k=i-1,m=0	;k>=0&&k<=14&&m<4	;--k,m++)
			{
				if(g_Chess[k][j]	==	Color)
					tagFive[4-m]=1;
				else if (0	==	g_Chess[k][j])
					tagFive[4-m]=0;
				else
					break;
			}
			for (k=i+1,m=0	;k>=0&&k<=14&&m<4	;++k,m++)
			{
				if(g_Chess[k][j]	==	Color)
					tagFive[6+m]=1;
				else if (0	==	g_Chess[k][j])
					tagFive[6+m]=0;
				else
					break;
			}
			Five_Model_Ary[i][j]+=MateModel(tagFive);

			for(k=1	;k<10	;k++)
				tagFive[k]=2;
			tagFive[0]=9;tagFive[5]=1;
			for (k=i-1,m=1	;k>=0&&k<=14&&m<5	;--k,m++)
			{
				if(g_Chess[k][j-m]	==	Color)
					tagFive[5-m]=1;
				else if (0	==	g_Chess[k][j-m])
					tagFive[5-m]=0;
				else
					break;
			}
			for (k=i+1,m=1	;k>=0&&k<=14&&m<5	;++k,m++)
			{
				if(g_Chess[k][j+m]	==	Color)
					tagFive[5+m]=1;
				else if (0	==	g_Chess[k][j+m])
					tagFive[5+m]=0;
				else
					break;
			}
			Five_Model_Ary[i][j]+=MateModel(tagFive);

			for(k=1	;k<10	;k++)
				tagFive[k]=2;
			tagFive[0]=9;tagFive[5]=1;
			for (k=i-1,m=1	;k>=0&&k<=14&&m<5	;--k,m++)
			{
				if(g_Chess[k][j+m]	==	Color)
					tagFive[5-m]=1;
				else if (0	==	g_Chess[k][j+m])
					tagFive[5-m]=0;
				else
					break;
			}
			for (k=i+1,m=1	;k>=0&&k<=14&&m<5	;++k,m++)
			{
				if(g_Chess[k][j-m]	==	Color)
					tagFive[5+m]=1;
				else if (0	==	g_Chess[k][j-m])
					tagFive[5+m]=0;
				else
					break;
			}
			Five_Model_Ary[i][j]+=MateModel(tagFive);
		}
	}  
	return 0;
}

int ComputeMax(int	Five_Model_Type[15][15],BOOL	Five_Model_BOOL[15][15],int *ri,int *rj)
{
	int i,j,Max=0;
	(*ri)=(*rj)=0;
	for (i=0	;i<15	;i++)
	{
		for (j=0	;j<15	;j++)
		{
			if(FALSE	==	Five_Model_BOOL[i][j])
				continue;
			if(Five_Model_Type[i][j]	>	Max)
			{
				Max=Five_Model_Type[i][j];
				(*ri)=i;(*rj)=j;
			}
		}
	}
	return Max;
}

int Test_AttackAndDeattack(int	Five_Model_Type1[15][15],int	Five_Model_Type2[15][15],BOOL	Five_Model_BOOL[15][15],int *ri,int *rj)
{
	int i,j,Max=0,temp;(*ri)=(*rj)=0;
	for (i=0	;i<15	;i++)
	{
		for (j=0	;j<15	;j++)
		{
			if(FALSE	==	Five_Model_BOOL[i][j])
				continue;
			temp	=	Five_Model_Type1[i][j]+Five_Model_Type2[i][j];
			if(temp	>	Max)
			{
				Max=temp;(*ri)=i;(*rj)=j;
			}
		}
	}
	return 0;
}

int BotMain(HWND	hWnd)
{
	int i,j;
	/*用户下好后进行估值*/
	DoFastValuation(g_LastX	,g_LastY	,g_Five_Model_Attack	,g_bFive_Model_Attack,1);
	DoFastValuation(g_LastX	,g_LastY	,g_Five_Model_Deattack	,g_bFive_Model_Deattack,2);
	Test_AttackAndDeattack(g_Five_Model_Attack	,g_Five_Model_Deattack	,g_bFive_Model_Attack	,&i	,&j);
	g_Chess[i][j]=2;g_Five_Model_Deattack[i][j]=0;
	g_bFive_Model_Attack[i][j]=FALSE;g_bFive_Model_Deattack[i][j]=FALSE;
	g_LastX=j;g_LastY=i;
	if(1	==	IsWin(j,i,2))
	{
		ResetFiveGame(hWnd);
		MessageBox(hWnd,TEXT("白方胜出"),TEXT("提示"),MB_OK);
		ResetDraw(hWnd);
		return 0;
	}
	InvalidateRect(hWnd	,NULL	,TRUE);
	/*机器下好后进行估值*/
	DoFastValuation(g_LastX	,g_LastY	,g_Five_Model_Attack	,g_bFive_Model_Attack,1);
	DoFastValuation(g_LastX	,g_LastY	,g_Five_Model_Deattack	,g_bFive_Model_Deattack,2);
	OutputDebugString("Hello,Bot!");
	return 0;
}

int IsWin(int x,int y,int color)
/*
Brief:判断胜负情况,返回1为胜出
计算“米字”范围内，单条直线是否成5个棋子
*/
{
	int i=y;int j=x;
	int p,q;
	int sum=0;
	for (p=i,q=j;(p>=0&&p<=14)	&&	(q>=0&&q<=14);--q)
		if(color	==	g_Chess[p][q])
			++sum;
		else
			break;
	for (p=i,q=j;(p>=0&&p<=14)	&&	(q>=0&&q<=14);++q)
		if(color	==	g_Chess[p][q])
			++sum;
		else
			break;
	sum--;
	if(sum>=5)return 1;
	
	sum=0;
	for (p=i,q=j;(p>=0&&p<=14)	&&	(q>=0&&q<=14);--p)
		if(color	==	g_Chess[p][q])
			++sum;
		else
			break;
	for (p=i,q=j;(p>=0&&p<=14)	&&	(q>=0&&q<=14);++p)
		if(color	==	g_Chess[p][q])
			++sum;
		else
			break;
	sum--;
	if(sum>=5)return 1;

	sum=0;
	for (p=i,q=j;(p>=0&&p<=14)	&&	(q>=0&&q<=14);--p,--q)
		if(color	==	g_Chess[p][q])
			++sum;
		else
			break;
	for (p=i,q=j;(p>=0&&p<=14)	&&	(q>=0&&q<=14);++p,++q)
		if(color	==	g_Chess[p][q])
			++sum;
		else
			break;
	sum--;
	if(sum>=5)return 1;

	sum=0;
	for (p=i,q=j;(p>=0&&p<=14)	&&	(q>=0&&q<=14);--p,++q)
		if(color	==	g_Chess[p][q])
			++sum;
		else
			break;
	for (p=i,q=j;(p>=0&&p<=14)	&&	(q>=0&&q<=14);++p,--q)
		if(color	==	g_Chess[p][q])
			++sum;
		else
			break;
	sum--;
	if(sum>=5)return 1;

	return 0;
}

