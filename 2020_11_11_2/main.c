#include"game.h"
int main()
{

	int quit = 0;
	while (!quit)
	{
		menu();
		int x;
		printf("�����룺");
		scanf_s("%d", &x);
		switch (x)
		{
		case 1:game(); break;
		case 2:quit = 1; break;
		default:printf("�����������������룡\n"); continue;
		}
	}

	system("pause");
	return 0;
}
