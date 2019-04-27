#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TERMS 100
#define MAX 100
#define BUFFER_SIZE 20

typedef struct term {
	int coef;
	int expo;
}Term;

typedef struct {
	char name;
	int nbr_terms;
	Term *terms[MAX_TERMS];
}Polynomial;

Polynomial *polys[MAX];
int n = 0;

//functions
void create();
void add();
void calculate();
void print();
int find(char func);
int pow(int x, int y);

int main()
{
	char command[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf("%s", command);
		if (strcmp(command, "create") == 0)
			create();
		else if (strcmp(command, "add") == 0)
			add();
		else if (strcmp(command, "calc") == 0)
			calculate();
		else if (strcmp(command, "print") == 0)
			print();
		else if (strcmp(command, "exit") == 0)
			break;
		else
			printf("Invalid Arguments.\n");
	}

	for (int i = 0;i < n;i++) {
		int nt = polys[i]->nbr_terms;
		for (int j = 0;j < nt;j++)
			free(polys[i]->terms[j]);
		free(polys[i]);
	}
	
	return 0;
}
void create()
{
	char func;
	scanf(" %c", &func);
	polys[n] = (Polynomial*)malloc(sizeof(Polynomial));
	polys[n]->name = func;
	polys[n]->nbr_terms = 0;
	n++;
}
void add()
{
	char func;
	int coef, expo;
	scanf(" %c", &func);
	scanf(" %d", &coef);
	scanf(" %d", &expo);
	int idx = find(func);
	int nt = polys[idx]->nbr_terms;
	if (nt == 0) {
		polys[idx]->terms[nt] = (Term *)malloc(sizeof(Term));
		polys[idx]->terms[nt]->coef = coef;
		polys[idx]->terms[nt]->expo = expo;
		polys[idx]->nbr_terms++;
		return;
	}
	for (int i = 0;i < nt;i++) {
		if (expo == polys[idx]->terms[i]->expo) {
			polys[idx]->terms[i]->coef += coef;
			return;
		}
	}
	polys[idx]->terms[nt] = (Term *)malloc(sizeof(Term));
	polys[idx]->terms[nt]->coef = coef;
	polys[idx]->terms[nt]->expo = expo;
	polys[idx]->nbr_terms++;
}
void calculate()
{
	int result = 0;
	char func;
	int digit;
	scanf(" %c", &func);
	scanf(" %d", &digit);
	int idx = find(func);
	int nt = polys[idx]->nbr_terms;
	for (int i = 0;i < nt;i++) {
		result += polys[idx]->terms[i]->coef*pow(digit, polys[idx]->terms[i]->expo);
	}
	printf("%d\n", result);
}
void print()
{
	char func;
	scanf(" %c", &func);
	int idx = find(func);
	int nt = polys[idx]->nbr_terms;
	for (int i = 0;i<nt;i++)
		for (int j = nt - 1;j > i;j--) {
			if (polys[idx]->terms[j]->expo > polys[idx]->terms[i]->expo) {
				int tmp = polys[idx]->terms[j]->expo;
				polys[idx]->terms[j]->expo = polys[idx]->terms[i]->expo;
				polys[idx]->terms[i]->expo = tmp;
				tmp = polys[idx]->terms[j]->coef;
				polys[idx]->terms[j]->coef = polys[idx]->terms[i]->coef;
				polys[idx]->terms[i]->coef = tmp;
			}
		}

	for (int i = 0;i < nt - 1;i++)
		printf("(%dx^%d)+", polys[idx]->terms[i]->coef, polys[idx]->terms[i]->expo);
	printf("(%d)\n", polys[idx]->terms[nt - 1]->coef);
}
int find(char func)
{
	int i;
	for (i = 0;i < n;i++)
		if (polys[i]->name == func)
			return i;
	if (i > n) {
		printf("You haven't defined function %c", func);
		return -1;
	}
}
int pow(int x, int y)
{
	if (y == 0)
		return 1;
	else
		return x*pow(x, (y - 1));
}
