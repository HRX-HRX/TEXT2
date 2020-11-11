#include"game.h"
void menu()
{

	printf("***********************\n");
	printf("* 1.Play       2.Exit *\n");
	printf("***********************\n");
}
void SetMines(char mine[][COL], int row, int col)
{
	int count = NUM;
	while (count)
	{
		int x = rand() % 10 + 1;
		int y = rand() % 10 + 1;
		if (mine[x][y] == '0')//b保证不重复的20个雷
		{
			mine[x][y] = '1';
			count--;
		}

	}
}
void ShowLine(int nums)
{
	printf("---");
	for (int i = 0; i < nums; i++)
	{
		printf("-");
	}
	printf("\n");
}
void ShowBoard(char show[][COL], int row, int col)
{
	printf("   ");
	for (int i = 1; i < row - 1; i++)//row=12
	{
		printf(" %2d ", i);
	}
	printf("\n");
	ShowLine(2 * col + col + 4);
	for (int i = 1; i < row - 1; i++)
	{
		printf("%2d|", i);
		for (int j = 1; j < col - 1; j++)
		{
			printf(" %c |", show[i][j]);
		}
		printf("\n");
		ShowLine(2 * col + col + 4);
	}
}

int GetMines(char mine[][COL], int row, int col, int x, int  y)//显示雷的个数
{
	return mine[x - 1][y - 1] + mine[x - 1][y] + mine[x - 1][y + 1] + \
		mine[x][y - 1] + mine[x][y + 1] + \
		mine[x + 1][y - 1] + mine[x + 1][y] + mine[x + 1][y + 1] - 8 * '0';
}
void game()
{
	srand((unsigned long)time(NULL));
	char show_board[ROW][COL];
	char mine_board[ROW][COL];
	memset(show_board, '*', sizeof(show_board));
	memset(mine_board, '0', sizeof(mine_board));
	SetMines(mine_board, ROW, COL);
	int count = (ROW - 2)*(COL - 2) - NUM;
	int x, y;
	do
	{
		ShowBoard(show_board, ROW, COL);
		printf("请输入子的坐标1~10：");
		scanf_s("%d %d", &x, &y);
		if (x<1 || x>10 || y<1 || y>10)
		{
			printf("输入位置不合法！请重新输入！\n");
			continue;
		}
		if (show_board[x][y] != '*')
		{
			printf("该位置已排除！请重新输入！\n");
			continue;
		}
		if (mine_board[x][y] == '1')
		{
			printf("你被炸死了！");
			break;
		}
		int num = GetMines(mine_board, ROW, COL, x, y);
		show_board[x][y] = num + '0';
		count--;
		system("cls");
	} while (count > 0);
	if (count == 0)
	{
		printf("你赢了！\n");
	}
	printf("下面是雷区分布！\n");
	ShowBoard(mine_board, ROW, COL);
}
