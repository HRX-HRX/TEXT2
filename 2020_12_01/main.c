#include"contact.h"
int main()
{
	contact_t * ct=InitContact();
	int quit = 0;
	int select = 0;
	while (!quit)
	{
		Menu();
		scanf("%d", &select);
		switch (select)
		{
		case 0:
			quit = 1;
			SaveContact(ct);
			break;
		case 1:
			Add(&ct);
			break;
		case 2:
			Del(ct);
			break;
		case 3:
			Search(ct);
			break;
		case 4:
			Mod(ct);
			break;
		case 5:
			Show(ct);
			break;
		case 6:
			Clear(ct);
			break;
		case 7:
			Sort_name(ct);
			break;
		}
	}
	printf("ByeBye!\n");
	system("pause");
	return 0;
}


