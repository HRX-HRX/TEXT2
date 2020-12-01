#ifndef _CONTACT_H_
#define _CONTACT_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>

#pragma warning(disable:4996)
#define SIZE 128
#define NUM 5
#define Inc_Size 5

typedef struct person{
	char name[SIZE/4];
	char sex;
	int age;
	char tel[SIZE/4];
	char add[SIZE];
}person_t,*Per;

typedef struct contact{
	int cap;
	int size;
	person_t persons[0];
}contact_t,*Con;

#define SAVE_FILE "save.txt"

contact_t * InitContact();
void Menu();
void Add(contact_t **ct);
void Del(contact_t *ct);
void Search(contact_t *ct);
void Mod(contact_t *ct);
void Clear(contact_t *ct);
void Sort_name(contact_t *ct);
void Show(contact_t *ct);
void SaveContact(contact_t *ct);

#endif