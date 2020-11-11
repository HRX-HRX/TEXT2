#include"game.h"
int main()
{

	int quit = 0;
	while (!quit)
	{
		menu();
		int x;
		printf("请输入：");
		scanf_s("%d", &x);
		switch (x)
		{
		case 1:game(); break;
		case 2:quit = 1; break;
		default:printf("输入有误！请重新输入！\n"); continue;
		}
	}

	system("pause");
	return 0;
}
