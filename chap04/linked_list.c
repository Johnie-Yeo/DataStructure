#pragma warning(disable:4996)

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node {
	int data;
	struct node *next;
}Node;

Node *head = NULL;
Node *end = NULL;
Node *current;
int n = 0;

#define BUFFER_SIZE 20
/*functions here*/
void create();
void add();
void add_first();
void add_idx();
void remove();
void remove_idx(int idx);
void remove_value(int value);
void remove_multiple(int mul);
void print();
void reverse();
void swap();
Node *get_node(int idx);
Node *remove_first();
Node *remove_after(Node *prev);
int add_after(Node *prev, int data);

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
		else if (strcmp(command, "print") == 0)
			print();
		else if (strcmp(command, "remove") == 0)
			remove();
		else if (strcmp(command, "size") == 0)
			printf("%d\n", n);
		else if (strcmp(command, "reverse") == 0)
			reverse();
		else if (strcmp(command, "swap") == 0)
			swap();
		else if (strcmp(command, "exit") == 0) {
			printf("SYSTEM DOWN.\n");
			break;
		}
		else
			printf("INVALId ARGUMENTS!\n");
	}
	free(head);
	free(end);
	free(current);
	return 0;
}
void create()
{
	int numbers = 0;
	int ch;
	while (scanf("%d", &numbers)) {
		current = (Node *)malloc(sizeof(Node));
		current->data = numbers;
		current->next = NULL;
		n++;

		if (head == NULL)
			head = end = current;
		else {
			end->next = current;
			end = current;
		}
		if ((ch = getchar()) != '\n')
			continue;
		else break;
	}
}
void add()
{
	char buffer[BUFFER_SIZE];

	scanf("%s", buffer);
	if (strcmp(buffer, "-f") == 0)
		add_first();
	else if (strcmp(buffer, "-i") == 0)
		add_idx();
	n++;
}
void print()
{
	current = head;
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}
void add_first()
{
	int value = 0;

	scanf("%d", &value);

	current = (Node *)malloc(sizeof(Node));
	current->data = value;
	current->next = head;
	head = current;
}
void add_idx()
{
	int idx;
	int value;

	scanf("%d", &idx);
	scanf("%d", &value);

	if (idx < 0)
		printf("ERROR!.\n");

	current = (Node *)malloc(sizeof(Node));
	current->data = value;

	if (idx == 0) {
		current->next = head;
		head = current;
	}
	Node *prev = get_node(idx - 1);
	if (prev != NULL) {
		add_after(prev, value);
	}
}
int add_after(Node *prev, int data)
{
	if (prev == NULL)
		return 0;
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp->data = data;
	tmp->next = prev->next;
	prev->next = tmp;

	return 1;
}
Node *get_node(int idx)
{
	if (idx < 0)
		return NULL;
	Node *p = head;
	for (int i = 0;i < idx&&p != NULL;i++)
		p = p->next;
	return p;
}
void remove()
{
	char buffer[BUFFER_SIZE];
	int x;

	scanf("%s", buffer);
	scanf("%d", &x);

	if (strcmp(buffer, "-i") == 0)
		remove_idx(x);
	else if (strcmp(buffer, "-v") == 0)
		remove_value(x);
	else if (strcmp(buffer, "-r") == 0)
		remove_multiple(x);
}
void remove_idx(int idx)
{
	if (idx == 0) {
		remove_first();
	}
	Node *prev = get_node(idx - 1);
	if (prev == NULL)
		return;
	else {
		remove_after(prev);
	}
	n--;
}
void remove_value(int val)
{
	Node *p = head;
	Node *q = NULL;

	while (p != NULL && (p->data != val)) {
		q = p;
		p = p->next;
	}
	if (p == NULL)
		return;
	if (q == NULL)
		remove_first();
	else
		remove_after(q);
	n--;
}
void remove_multiple(int mul)
{
	Node *p = head;
	while (p != NULL) {
		if (p->data%mul == 0)
			remove_value(p->data);
		p = p->next;
	}
}
Node *remove_first()
{
	if (head == NULL) {
		return NULL;
	}
	else {
		Node *tmp = head;
		head = head->next;
		return tmp;
	}
}
Node *remove_after(Node *prev)
{
	Node *tmp = prev->next;
	if (tmp == NULL)
		return NULL;
	else {
		prev->next = tmp->next;
		return tmp;
	}
}
void reverse()
{
	Node *q = get_node(n - 1);
	Node *p = q;
	for (int i = 1;i < n;i++) {
		p->next = get_node(n - i - 1);
		p = p->next;;
	}
	p->next = NULL;
	head = q;
}
void swap()
{
	int idx1, idx2;

	scanf("%d", &idx1);
	scanf("%d", &idx2);

	Node *p = get_node(idx1);
	Node *q = get_node(idx2);
	Node *tmp = NULL;
	if (idx1 == 0) {
		Node *prev = get_node(idx2 - 1);
		prev->next = p;
		tmp = p;
		p = q;
		q = tmp;
	}
	else if (idx2 == 0) {
		Node *prev = get_node(idx1 - 1);
		prev->next = q;
		tmp = q;
		q = p;
		p = tmp;
	}
	else {
		Node *prev_p = get_node(idx1 - 1);
		Node *prev_q = get_node(idx2 - 1);
		tmp = prev_p->next;
		prev_p->next = prev_q->next;
		prev_q->next = tmp;
		tmp = p->next;
		p->next = q->next;
		q->next = tmp;
	}
}