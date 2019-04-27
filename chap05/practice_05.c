#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX 100000
#define BUFFER_SIZE 100

struct follower { 
	char *word; 
	int count; 
	struct follower *next; 
}; 
typedef struct follower Follower;

typedef struct item {
	char *word;     
	int size;    // head가 거느리고 있는 연결리스트의 길이     
	Follower *head; 
} Item; 

Item *table[MAX];   
int n=0;    // table에 저정된 단어의 개수 

int search_table(char *buf);
Item *create_item_instance();
Follower *create_follower_instance();
Follower *search_follower(Item *ptr_item, char *buffer);
void set_follower(Item *ptr_item, char *buffer);
void print_table();

int main()
{
	int index=0;
	char buffer[BUFFER_SIZE];
	FILE *fp = fopen("Text.txt", "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		exit(1);
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", buffer);
		if (search_table(buffer) == -1) {
			Item *ptr_item = create_item_instance();

			ptr_item->word = strdup(buffer);
			table[n] = ptr_item;

			set_follower(table[index], buffer);
			n++;
		}
		else {
			set_follower(table[index], buffer);
		}
		index = search_table(buffer);
	}
	fclose(fp);
	print_table();

	return 0;
}
Follower *create_follower_instance()
{
	Follower *fw = (Follower *)malloc(sizeof(Follower));
	fw->count = 0;
	fw->next = NULL;
	fw->word = NULL;

	return fw;
}
Item *create_item_instance()
{
	Item *ptr_it = (Item *)malloc(sizeof(Item));
	ptr_it->head = NULL;
	ptr_it->size = 0;
	ptr_it->word = NULL;

	return ptr_it;
}
int search_table(char *buf)//있으면 idx 없으면 -1
{
	int i = 0;
	if (n == 0)
		return -1;
	for (i;i < n;i++) {
		if (strcmp(table[i]->word, buf) == 0)
			return i;
	}
	return -1;
}
void set_follower(Item *ptr_item,char *buffer)
{
	Follower *ptr_follower = create_follower_instance();

	if (n == 0)
		return;
	
	if (ptr_item->head == NULL) {
		ptr_follower->count++;
		ptr_follower->word = strdup(buffer);

		ptr_item->head = ptr_follower;
		ptr_item->size++;
	}
	
	else {
		ptr_follower = search_follower(ptr_item,buffer);
		Follower *tmp = ptr_item->head;
		if (ptr_follower == NULL) {
			while (tmp->next!=NULL) {
				tmp = tmp->next;
			}
			Follower *q = create_follower_instance();
			q->count++;
			q->word = strdup(buffer);
			q->next = NULL;
			tmp->next = q;

			ptr_item->size++;
		}
		else {
			ptr_follower->count++;
		}
	}
}
Follower *search_follower(Item *ptr_item, char *buffer)
{
	Follower *tmp = ptr_item->head;
	while (tmp != NULL) {
		if (strcmp(tmp->word, buffer) == 0) {
			break;
		}
		tmp = tmp->next;
	}
	return tmp;
}
void print_table()
{
	Follower *ptr_follower;
	for (int i = 0;i < n;i++) {
		printf("%s: ", table[i]->word);
		ptr_follower = table[i]->head;
		while (ptr_follower!=NULL) {
			printf("%s(%d) ", ptr_follower->word, ptr_follower->count);
			ptr_follower = ptr_follower->next;
		}
		printf("\n");
	}
}