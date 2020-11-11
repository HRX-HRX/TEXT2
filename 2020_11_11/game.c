#include"game.h"
void menu()
{
	printf("*********************\n");
	printf("****1 Play 2 Exit****\n");
	printf("*********************\n");
	printf("请选择:");
}
void Show(char board[][Col],int row, int col)
{
	printf("-------------\n");
	for (int i = 0; i < row; i++)
	{
		printf("|");
		for(int j = 0; j < col; j++)
		{
			printf(" %c |", board[i][j]);
		}
		printf("\n-------------\n");
	}
}

//void show(char board[][Col],int row,int col)
//{
//	for (int i = 0; i < row; i++)
//	{
//		printf("%d |", i + 1);
//	}
//	printf("\n------------\n");
//	for (int i = 0; i < row; i++)
//	{
//		printf("%d|", i + 1);
//		for (int j = 0; j < col; j++)
//		{
//			printf("%c|", board[i][j]);
//		}
//		printf("\n------------\n");
//	}
//}
void P_Play(char board[][Col], int row, int col)
{
	int x,y;
	while (1)
	{
		printf("请输入你的位置：");
		scanf("%d %d", &x, &y);
		if (x < 1 || x >3 || y < 1 || y > 3)
		{
			printf("输入有误，无此位置！\n");
			continue;
		}
		else if (board[x - 1][y - 1] != ' ')
		{
			printf("输入有误！该位置已被占用\n");
			continue;
		}
		else
		{
			board[x - 1][y - 1] = P_Color;
			break;
		}

	}
}

char Judge(char board[][Col], int row, int col)
{
	for (int i = 0; i <= row; i++)
	{
		if (board[i][0] == board[i][1] && \
			board[i][1] == board[i][2] && \
			board[i][0] != ' ')
			return board[i][0];
	}
	for (int j = 0; j < col; j++)
	{
		if (board[0][j] == board[1][j] && \
			board[1][j] == board[2][j] && \
			board[0][j] != ' ')
			return board[0][j];
	}
	if (board[0][0] == board[1][1] && \
		board[1][1] == board[2][2] && \
		board[0][0] != ' ')
		return board[0][0];
	if (board[0][2] == board[1][1] && \
		board[1][1] == board[2][0] && \
		board[0][2] != ' ')
		return board[0][2];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				return Next;//棋局未满，继续游戏
		}
	}
	return Draw;//平局
}
void C_Play(char board[][Col], int row, int col)
{
	while (1){
		int x = rand() % row;
		int y = rand() % col;
		if (board[x][y] == ' ')
		{
			board[x][y] = C_Color;
			break;
		}
	}
}


void game()
{
	srand((unsigned long)time(NULL));
	char board[Row][Col];
	memset(board,' ',sizeof(board));
	int ret;
	do
	{
		Show(board[Row][Col], Row, Col);
		P_Play(board[Row][Col], Row, Col);
		ret = Judge(board[Row][Col], Row, Col);
		if (ret != Next)
		{
			break;
		}
		C_Play(board[Row][Col], Row, Col);
		Judge(board[Row][Col], Row, Col);
		if (ret != Next)
		{
			break;
		}
	} while (1);

	if (ret == P_Color)
	{
		printf("你赢了！\n");
	}
	else
	{
		if (ret == C_Color)
		{
			printf("你输了！\n");
		}
		else printf("平局！\n");
	}
}