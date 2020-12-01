#include"contact.h"
//通讯录可以用来存储1000个人的信息，每个人的信息包括：姓名、性别、年龄、电话、住址
void Menu()//菜单
{
	printf("**********************\n");
	printf("** 1 Add      2 Del **\n");
	printf("** 3 Search   4 Mod **\n");
	printf("** 5 Show     6 Cle **\n");
	printf("** 7 Sort     0 Exit**\n");
	printf("**********************\n");
	printf("请选择：\n");
}
//生成通讯录
Con InitContact()
{
	contact_t *ct = NULL;
	FILE*fp = fopen(SAVE_FILE, "rb");
	if (NULL == fp)
	{
		int size = sizeof(contact_t)+sizeof(person_t)*NUM;
		ct = (contact_t *)malloc(size);
		if (NULL == ct){
			printf("malloc error");
			exit(1);
		}

		ct->cap = NUM;
		ct->size = 0;
	}
	else
	{
		contact_t tmp;
		fread(&tmp, sizeof(contact_t), 1, fp);
		int size = sizeof(contact_t)+sizeof(person_t)* tmp.cap;
		ct = (contact_t *)malloc(size);
		if (NULL == ct){
			printf("malloc error");
			exit(1);
		}
		ct->cap = tmp.cap;
		ct->size = tmp.size;

		fread(ct->persons, sizeof(person_t), tmp.size, fp);
		fclose(fp);
	}
	return ct;
}
//判断为空
static int IsEmpty(contact_t  *ct)
{
	return ct->size == 0;
}

//保存
static void SaveContact(contact_t *ct)
{
	assert(ct);
	FILE *fp = fopen(SAVE_FILE, "wb");
	if (NULL == fp){
		printf("fopen error, save failed \n");
		return;
	}
	fwrite(ct, sizeof(contact_t), 1, fp);
	fwrite(ct->persons, sizeof(person_t), ct->size, fp);
	printf("save done...\n");
	fclose(fp);
}
//查找指定信息联系人
static int Find(contact_t *ct,char *name)
{
	assert(ct);
	assert(name);

	for (int i = 0; i < ct->size; i++){
		if (strcmp(ct->persons[i].name, name) == 0){
			return i;
		}
	}
	return -1;

}
//判断是否为满
static int IsFull(contact_t **ct)
{
	return (*ct)->cap == (*ct)->size;
}
//扩容
static int Inc(contact_t **ct)
{
	//printf("...\n");
	contact_t *p = (contact_t *)realloc(*ct, (*ct)->cap + Inc_Size*sizeof(person_t));
	if (NULL == p)
	{
		return 0;
	}
	*ct = p;
	(*ct)->cap += Inc_Size;
	return 1;
}
//添加联系人
void Add(contact_t **ct)
{
	if (!IsFull(ct) || Inc(ct))//前者为真则正常添加信息，否则扩容
	{
		person_t *p = &((*ct)->persons[(*ct)->size]);//定义一个指针，指向柔性数组的成员，其成员类型为结构体，所以指针类型也是结构体类型
		printf("input name:");
		char name[SIZE / 4] = { 0 };
		scanf(" %s", name);
		if (Find(*ct, name) == -1)
		{
			strcpy(p->name, name);
			printf("input sex:");
			scanf(" %c", &(p->sex));
			printf("input age:");
			scanf(" %d", &(p->age));
			printf("input tel:");
			scanf(" %s", p->tel);
			printf("input add:");
			scanf(" %s", p->add);
			(*ct)->size += 1;
		}
		else
		{
			printf("您输入的人已存在！\n");
		}
	}
	else
	{
		printf("inc error!\n");
	}
}
//显示
void Show(contact_t *ct)
{
	assert(ct);
	printf("%5s  %5s %8s  %10s %10s\n", "name", "sex", "age", "tel", "add");
	for (int p = 0; p < ct->size; p++)
	{
		printf("%5s %5c", ct->persons[p].name, ct->persons[p].sex);
		printf("%9d %15s", ct->persons[p].age, ct->persons[p].tel);
		printf("%10s\n", ct->persons[p].add);
	}
}
//删除指定联系人信息
void Del(contact_t *ct)
{
	assert(ct);
	if (!IsEmpty(ct)){
		printf("输入你要删除的人的姓名 ");
		char name[SIZE / 4] = { 0 };
		scanf(" %s", name);
		int pos = Find(ct, name);
		if (pos >= 0)
		{
			ct->persons[pos] = ct->persons[ct->size - 1];
			ct->size -= 1;
			printf("删除成功！\n");
		}
		else
		{
			printf("你要删除的人，不存在!\n");
		}
	}
}
//查找指定联系人信息
void Search(contact_t *ct)
{
	assert(ct);
	printf("请输入你要查找的人的姓名：");
	char name[SIZE / 4] = { 0 };
	scanf("%s", name);
	if (!IsEmpty(ct))
	{
		int p = Find(ct, name);
		if (p >= 0)
		{
			printf("%5s  %5s %8s  %10s %10s\n", "name", "sex", "age", "tel", "add");
			printf("%5s %5c", ct->persons[p].name, ct->persons[p].sex);
			printf("%9d %15s", ct->persons[p].age, ct->persons[p].tel);
			printf("%10s\n", ct->persons[p].add);
		}
		else
		{
			printf("您查找的人不存在！\n");
		}
	}
}
//修改指定联系人信息
void Mod(contact_t *ct)
{
	printf("请输入你要修改的人的姓名：\n");
	char name[SIZE / 4] = { 0 };
	scanf("%s", name);
	if (!IsEmpty(ct))
	{
		int p = Find(ct, name);
		if (p >= 0)
		{
			printf("%5s  %5s %8s  %10s %10s\n", "name", "sex", "age", "tel", "add");
			printf("%5s %5c", ct->persons[p].name, ct->persons[p].sex);
			printf("%9d %15s", ct->persons[p].age, ct->persons[p].tel);
			printf("%10s\n", ct->persons[p].add);
			printf("请选择要修改的信息：\n");
			printf("1 name 2 sex 3 age 4 tel 5 add\n");
			int select = 0;
			scanf("%d", &select);
			
			switch (select)
			{
			case 1:
				printf("请输入：");
				char name[SIZE/4] = { 0 };
				scanf("%s", name);
				strcpy(ct->persons[p].name, name);
				break;
			case 2:
				printf("请输入：");
				char sex=0;
				scanf("%c", &sex);
				ct->persons[p].sex= sex;
				break;
			case 3:
				printf("请输入：");
				int age = 0;
				scanf("%d", &age);
				ct->persons[p].age=age;
				break;
			case 4:
				printf("请输入：");
				char tel[SIZE/4] = { 0 };
				scanf("%s", tel);
				strcpy(ct->persons[p].tel, tel);
				break;
			case 5:
				printf("请输入：");
				char add[SIZE] = { 0 };
				scanf("%s", add);
				strcpy(ct->persons[p].add, add);
				break;

			}
			printf("修改成功！\n");
			printf("%5s  %5s %8s  %10s %10s\n", "name", "sex", "age", "tel", "add");
			printf("%5s %5c", ct->persons[p].name, ct->persons[p].sex);
			printf("%9d %15s", ct->persons[p].age, ct->persons[p].tel);
			printf("%10s\n", ct->persons[p].add);
		}
		else
		{
			printf("您查找的人不存在！\n");
		}
	}

}
//清空所有联系人
void Clear(contact_t *ct)
{
	ct->size = 0;
	person_t *p = NULL;
	printf("已清空\n");
}
//比较函数
int Minecmp(const void *_p1, const void *_p2)
{
	int *p1 = (int*)_p1;
	int *p2 = (int*)_p2;

	if (*p1 > *p2)
	{
		return 1;
	}
	else if (*p1 < *p2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
//以名字排序所有联系人
void Sort_name(contact_t *ct)
{
	qsort(ct->persons, ct->size, sizeof(person_t),Minecmp);
	printf("排序成功！\n");
	Show(ct);
}