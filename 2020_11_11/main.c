#include"game.h"
int main()
{
	
	int n;
	int quit = 0;
	while (!quit)
	{
		Menu();
		scanf("%d",&n);
		switch (n)
		{
		case 1:
			Game(); 
			break;
		case 2:
			quit = 1; break;
		default:printf("输入有误！请重新输入！\n"); break;
		}
	}
	printf("ByeBye!\n");
	system("pause");
	return 0;
}