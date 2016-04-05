/***
*
*		2048小游戏程序v4.0
*
*       Copyright 陆依鸣. All rights reserved.
*
*		2015-11-10
*
*
****/
/***
*	version4.0： ---------------2015-11-10
*	1、改善画面，数字用颜色区分
*	2、新增计时和计步功能
****/
/***
*	version3.0：----------------2015-11-9
*	1、修复无效操作时也会生成数字的bug
*	2、原版游戏移动一次每个数字最多只能合并一次，但该程序会多次合并，如：8 4 4 0 执行向右操作后会变成 0 0 0 16
****/
/***
*	version2.0：----------------2015-11-9
*	1、方向键操作（v1.0采用输入U,D,L,R字符操作）
****/

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
using namespace std;
void init(int (&board)[4][4]);		//初始化棋盘
void randnum(int (&board)[4][4]);	//随机生成数字
void printboard(int (&board)[4][4]);//打印棋盘
int leftmove(int (&board)[4][4]);	//向左移动操作,返回值1表示有效操作，0表示无效操作
int rightmove(int (&board)[4][4]);	//向右移动操作
int upmove(int (&board)[4][4]);		//向上移动操作
int downmove(int (&board)[4][4]);	//向下移动操作
int iswin(int(&board)[4][4]);		//判断是否胜利
int isfail(int(&board)[4][4]);		//判断是否失败
unsigned short int getcolor(int color);//得到数字对应的颜色参数
int main()
{
	clock_t start, finish;	//游戏时间计时
	double time_length;
	start = clock();

	int count = 0;	//存储操作步数

	int board[4][4];	//棋盘
	char move;
	cout << "游戏通过方向键控制:" << endl;
	init(board);
	printboard(board);
	int output = 0;
	for (;;)
	{
		if (!output)	//通过output变量防止多次输出提示
		{
			cout << "方向键控制移动（按Esc结束程序）:";
			output = 1;
		}
		move = _getch();	//方向键第一个字符为-32
		move = _getch();	//vs2013用 _getch() 函数，getch()不能用？
		switch (move)
		{
		case 72:
		{
			if (upmove(board)) //如果是有效操作
			{
				randnum(board);
				system("cls");
				printboard(board);
				output = 0;
				++count;
				break;
			}
			else
				continue;
		}
		case 80:
		{
			if (downmove(board)) 
			{
				randnum(board);
				system("cls");
				printboard(board);
				output = 0;
				++count;
				break;
			}
			else
				continue;
		}
		case 75:
		{
			if (leftmove(board))
			{
				randnum(board);
				system("cls");
				printboard(board);
				output = 0;
				++count;
				break;
			}
			else
				continue;
		}
		case 77:
		{
			if (rightmove(board))
			{
				randnum(board);
				system("cls");
				printboard(board);
				output = 0;
				++count;
				break;
			}
			else
				continue;
		}
		case 27:exit(0);
		}
		if (iswin(board))
		{
			cout << "你赢了！" << endl ;
			finish = clock();
			time_length = (double)(finish - start) / CLOCKS_PER_SEC;
			printf("您所用游戏时间为：%.1fs\n", time_length);
			printf("您的操作步数为:%d\n", count);
			cout << "输入任意键结束" << endl;
			_getch();
			_getch();
			exit(0);
		}	
		if (isfail(board)) 
		{
			cout << "游戏结束" << endl;
			finish = clock();
			time_length = (double)(finish - start) / CLOCKS_PER_SEC;
			printf("您所用游戏时间为：%.1fs\n", time_length);
			printf("您的操作步数为:%d\n", count);
			cout << "输入任意键结束" << endl;
			_getch();
			exit(0);
		}
	} 
}
int iswin(int(&board)[4][4])
{
	for (int i = 0; i <= 3; i++)
		for (int j = 0; j <= 3; j++)
			if (board[i][j] == 2048)
				return 1;
	return 0;
}
int isfail(int(&board)[4][4])
{
	for (int i = 0; i <= 3; i++)
		for (int j = 0; j <= 3; j++)
			if (board[i][j] == 0)
				return 0;		//如果有0，则游戏未结束
	for (int i = 0; i <= 3; i++)
		for (int j = 0; j <= 2; j++)
			if (board[i][j] == board[i][j + 1])
				return 0;		//如果棋盘已经充满，但横向仍可操作，则未结束
	for (int i = 0; i <= 2; i++)
		for (int j = 0; j <= 3; j++)
			if (board[i][j] == board[i + 1][j])
				return 0;		//如果棋盘已经充满，但纵向仍可操作，则未结束
	return 1;		//不可执行任何操作，游戏结束
}
void init(int (&board)[4][4])
{
	for (int i = 0; i <= 3; i++)
		for (int j = 0; j <= 3; j++)
			board[i][j] = 0;
	srand((unsigned)time(NULL));
	int i = rand() % 4;
	int j = rand() % 4;
	board[i][j] = 2;
	do
	{
		i = rand() % 4;
		j = rand() % 4;
	} while (board[i][j] != 0);
	board[i][j] = 2;
}
void randnum(int (&board)[4][4]) 
{
	int num = (rand() % 2 + 1) * 2;
	int i, j;
	srand((unsigned)time(NULL));
	do
	{
		i = rand() % 4;
		j = rand() % 4;
	} while (board[i][j] != 0);
		board[i][j] = num;
}

void printboard(int (&board)[4][4])
{
	HANDLE hOut;//创建句柄
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i <= 3; i++)
		for (int j = 0; j <= 3; j++)
		{
			if (j == 3)
			{
				SetConsoleTextAttribute(hOut, getcolor(board[i][j]));//设置字体颜色
				printf("%d\n", board[i][j]);						//getcolor()函数用于取得对应数字的颜色参数，然后调用SetConsoleTextAttribute()设置颜色
			}
			else
			{
				SetConsoleTextAttribute(hOut, getcolor(board[i][j]));
				printf("%d\t", board[i][j]);
			}			
		}
	SetConsoleTextAttribute(hOut,getcolor(0));//还原为白色字体
}
int rightmove(int (&board)[4][4])
{
	int flag = 0;
	for (int i = 0; i <= 3; i++)		//以行为单位循环操作
	{
		int tmp[4] = { 0, 0, 0, 0 }, count = 3;	//tmp保存该行执行操作后的最终结果
		for (int j = 3; j >= 0; j--)	//从右向左，遇到的非0数字存入tmp[]
		{
			if (board[i][j] != 0)
			{
				if (tmp[count]==0)		//tmp对应的位置为0，说明还未存入数字，则存入该数字
					tmp[count] = board[i][j];
				else
				{
					if (board[i][j] == tmp[count])	//tmp对应的位置已有数字，且两数字相等，则合并
						tmp[count] += board[i][j];
					else
						tmp[--count] = board[i][j];	//tmp对应的位置已有数字，但两数字不等
				}									//则向前一位存入tmp中数字为0的空位
			}
		}
		for (int j = 0; j <= 3; j++)		//只要原棋盘与操作后棋盘有一处不同，则为有效操作
			if (board[i][j] != tmp[j])		//否则为无效操作
				flag = 1;
		for (int j = 3; j >= 0; j--)	//将tmp复制到棋盘
			board[i][j] = tmp[j];
	}
	return flag;
}
int leftmove(int (&board)[4][4])
{
	int flag = 0;
	for (int i = 0; i <= 3; i++)
	{
		int tmp[4] = { 0, 0, 0, 0 }, count = 0;
		for (int j = 0; j <= 3; j++)
		{
			if (board[i][j] != 0)
			{
				if (tmp[count] == 0)
					tmp[count] = board[i][j];
				else
				{
					if (board[i][j] == tmp[count])
						tmp[count] += board[i][j];
					else
						tmp[++count] = board[i][j];
				}
			}
		}
		for (int j = 0; j <= 3; j++)
			if (board[i][j] != tmp[j])
				flag = 1;
		for (int j = 0; j <= 3; j++)
			board[i][j] = tmp[j];
	}
	return flag;
}
int upmove(int (&board)[4][4])
{
	int flag = 0;
	for (int j = 0; j <= 3; j++)
	{
		int tmp[4] = { 0, 0, 0, 0 }, count = 0;
		for (int i = 0; i <= 3; i++)
		{
			if (board[i][j] != 0)
			{
				if (tmp[count] == 0)
					tmp[count] = board[i][j];
				else
				{
					if (board[i][j] == tmp[count])
						tmp[count] += board[i][j];
					else
						tmp[++count] = board[i][j];
				}	
			}
		}	
		for (int i = 0; i <= 3; i++)
			if (board[i][j] != tmp[i])
				flag = 1;
		for (int i = 0; i <= 3; i++)
			board[i][j] = tmp[i];
	}
	return flag;
}
int downmove(int (&board)[4][4])
{
	int flag = 0;
	for (int j = 0; j <= 3; j++)
	{
		int tmp[4] = { 0, 0, 0, 0 }, count = 3;
		for (int i = 3; i >= 0; i--)
		{
			if (board[i][j] != 0)
			{
				if (tmp[count] == 0)
					tmp[count] = board[i][j];
				else
				{
					if (board[i][j] == tmp[count])
						tmp[count] += board[i][j];
					else
						tmp[--count] = board[i][j];
				}	
			}
		}
		for (int i = 0; i <= 3; i++)
			if (board[i][j] != tmp[i])
				flag = 1;
		for (int i = 3; i >= 0; i--)
			board[i][j] = tmp[i];
	}
	return flag;
}
unsigned short int getcolor(int color)
{
	switch (color)
	{
	case 0:return  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;			//浅白色
	case 2:return  FOREGROUND_RED | FOREGROUND_BLUE;							//浅紫色
	case 4:return  FOREGROUND_GREEN;											//浅绿色
	case 8:return  FOREGROUND_RED;												//浅红色
	case 16:return FOREGROUND_GREEN | FOREGROUND_BLUE;							//浅蓝色
	case 32:return  FOREGROUND_RED | FOREGROUND_GREEN;							//浅黄色
	case 64:return FOREGROUND_INTENSITY | FOREGROUND_RED;						//高亮红色
	case 128:return FOREGROUND_INTENSITY | FOREGROUND_GREEN;					//高亮绿色
	case 256:return FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE;	//高亮浅蓝色
	case 512:return FOREGROUND_INTENSITY | FOREGROUND_BLUE;						//高亮蓝色
	case 1024:return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;	//高亮黄色
	case 2048:return FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;	//高亮紫色
	default:return 0;//浅白色
	}
}




