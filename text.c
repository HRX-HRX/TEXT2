#include<stdio.h>
#include<Windows.h>
void Mineprint(int num)
{
	printf("偶数位：");
	for (int i = 31; i > 0; i-=2)
	{
		printf("%d ", (num >> i) & 1);
	}
	printf("\n");
	printf("奇数位：");
	for (int i = 30; i >= 0; i-=2)
	{
		printf("%d ", (num >> i) & 1);
	}
}
int main()
{
	int x =0;
	scanf_s("%d", &x);
	Mineprint(x);
	system("pause");
	return 0;
}