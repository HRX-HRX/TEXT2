#include"contact.h"
//ͨѶ¼���������洢1000���˵���Ϣ��ÿ���˵���Ϣ�������������Ա����䡢�绰��סַ
void Menu()//�˵�
{
	printf("**********************\n");
	printf("** 1 Add      2 Del **\n");
	printf("** 3 Search   4 Mod **\n");
	printf("** 5 Show     6 Cle **\n");
	printf("** 7 Sort     0 Exit**\n");
	printf("**********************\n");
	printf("��ѡ��\n");
}
//����ͨѶ¼
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
//�ж�Ϊ��
static int IsEmpty(contact_t  *ct)
{
	return ct->size == 0;
}

//����
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
//����ָ����Ϣ��ϵ��
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
//�ж��Ƿ�Ϊ��
static int IsFull(contact_t **ct)
{
	return (*ct)->cap == (*ct)->size;
}
//����
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
//�����ϵ��
void Add(contact_t **ct)
{
	if (!IsFull(ct) || Inc(ct))//ǰ��Ϊ�������������Ϣ����������
	{
		person_t *p = &((*ct)->persons[(*ct)->size]);//����һ��ָ�룬ָ����������ĳ�Ա�����Ա����Ϊ�ṹ�壬����ָ������Ҳ�ǽṹ������
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
			printf("����������Ѵ��ڣ�\n");
		}
	}
	else
	{
		printf("inc error!\n");
	}
}
//��ʾ
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
//ɾ��ָ����ϵ����Ϣ
void Del(contact_t *ct)
{
	assert(ct);
	if (!IsEmpty(ct)){
		printf("������Ҫɾ�����˵����� ");
		char name[SIZE / 4] = { 0 };
		scanf(" %s", name);
		int pos = Find(ct, name);
		if (pos >= 0)
		{
			ct->persons[pos] = ct->persons[ct->size - 1];
			ct->size -= 1;
			printf("ɾ���ɹ���\n");
		}
		else
		{
			printf("��Ҫɾ�����ˣ�������!\n");
		}
	}
}
//����ָ����ϵ����Ϣ
void Search(contact_t *ct)
{
	assert(ct);
	printf("��������Ҫ���ҵ��˵�������");
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
			printf("�����ҵ��˲����ڣ�\n");
		}
	}
}
//�޸�ָ����ϵ����Ϣ
void Mod(contact_t *ct)
{
	printf("��������Ҫ�޸ĵ��˵�������\n");
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
			printf("��ѡ��Ҫ�޸ĵ���Ϣ��\n");
			printf("1 name 2 sex 3 age 4 tel 5 add\n");
			int select = 0;
			scanf("%d", &select);
			
			switch (select)
			{
			case 1:
				printf("�����룺");
				char name[SIZE/4] = { 0 };
				scanf("%s", name);
				strcpy(ct->persons[p].name, name);
				break;
			case 2:
				printf("�����룺");
				char sex=0;
				scanf("%c", &sex);
				ct->persons[p].sex= sex;
				break;
			case 3:
				printf("�����룺");
				int age = 0;
				scanf("%d", &age);
				ct->persons[p].age=age;
				break;
			case 4:
				printf("�����룺");
				char tel[SIZE/4] = { 0 };
				scanf("%s", tel);
				strcpy(ct->persons[p].tel, tel);
				break;
			case 5:
				printf("�����룺");
				char add[SIZE] = { 0 };
				scanf("%s", add);
				strcpy(ct->persons[p].add, add);
				break;

			}
			printf("�޸ĳɹ���\n");
			printf("%5s  %5s %8s  %10s %10s\n", "name", "sex", "age", "tel", "add");
			printf("%5s %5c", ct->persons[p].name, ct->persons[p].sex);
			printf("%9d %15s", ct->persons[p].age, ct->persons[p].tel);
			printf("%10s\n", ct->persons[p].add);
		}
		else
		{
			printf("�����ҵ��˲����ڣ�\n");
		}
	}

}
//���������ϵ��
void Clear(contact_t *ct)
{
	ct->size = 0;
	person_t *p = NULL;
	printf("�����\n");
}
//�ȽϺ���
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
//����������������ϵ��
void Sort_name(contact_t *ct)
{
	qsort(ct->persons, ct->size, sizeof(person_t),Minecmp);
	printf("����ɹ���\n");
	Show(ct);
}