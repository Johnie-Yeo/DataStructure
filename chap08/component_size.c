main.cpp

#pragma warning(disable:4996)

#include<stdio.h>
#include "queue.h"
#include "pos.h"

#define MAX 100
#define IMAGE 1
#define BACKGROUND 0

int maze[MAX][MAX];
int n; //미로의 크기

void read_maze();
bool movable(Position pos, int dir);
int size_component(int i, int j);
int main()
{
	int i, j;
	int nbr_component = 0;
	int count[10];
	
	read_maze();
	for (i = 0;i < n;i++) {
		for (j = 0;j < n;j++) {
			if (maze[i][j] == IMAGE) {
				count[nbr_component++] = size_component(i, j);
			}
		}
	}
	for (i = 0;i < nbr_component - 1;i++)
		printf("%d, ", count[i]);
	printf("%d\n", count[i]);

	return 0;
}
void read_maze()
{
	int ch;
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL)
		printf("Open failed.\n");
	fscanf(fp, "%d", &n);

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			while (ch = fgetc(fp)) {
				if (ch != '\n') {
					maze[i][j] = ch - '0';
					break;
				}
			}
		}
	}
	fclose(fp);
}
bool movable(Position pos, int dir)
{
	Position tmp_pos = pos;
	Position tmp = move_to(tmp_pos, dir);
	if (tmp.x < 0 || tmp.x>(n-1) || tmp.y < 0 || tmp.y>(n-1))
		return false;
	if (maze[tmp.x][tmp.y] == 1)
		return true;
	else
		return false;

}
int size_component(int i, int j)
{
	Queue component = create();
	Position cur;
	int result = 1;

	cur.x = i;
	cur.y = j;
	enqueue(component, cur);

	maze[i][j] = -1;

	while (!is_empty(component)) {
		cur = dequeue(component);
		for (int dir = 0;dir < 8;dir++) {
			if (movable(cur, dir)) {
				Position p = move_to(cur, dir);

				maze[p.x][p.y] = maze[cur.x][cur.y] - 1;

				enqueue(component, p);
				result++;
			}
		}
	}
	return result;
}


==========================

pos.cpp



#include "pos.h"

int offset[8][2] = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 },{-1,1},{1,1},{1,-1},{-1,-1} };
//북:1 동:2 남:3 서:4 북동:5 동남:6 남서:7 서북:8
Position move_to(Position pos, int dir) {
	Position next;
	next.x = pos.x + offset[dir][0];
	next.y = pos.y + offset[dir][1];

	return next;
}


===========================

queue.cpp

//implementation with array

#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

#define INIT_CAPACITY 100

void reallocate(Queue q);

struct queue_type {
	Item  *contents;
	int front;
	int rear;
	int size;// the number of saved data
	int capacity;//size of array contents
};
void terminate(const char *message)
{
	printf("%s\n", message);
	exit(1);
}
int get_size(Queue q)
{
	return q->size;
}
Queue create()
{
	Queue q = (Queue)malloc(sizeof(struct queue_type));
	if (q == NULL)
		terminate("Error in create: queue could not be created.");
	q->contents = (Item *)malloc(INIT_CAPACITY * sizeof(Item));
	if (q->contents == NULL) {
		free(q);
		terminate("Error in create:queue could not be created.");
	}
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	q->capacity = INIT_CAPACITY;

	return q;
}
void destroy(Queue q)
{
	free(q->contents);
	free(q);
}
void make_empty(Queue q)
{
	q->front = 0;
	q->rear = -1;
	q->size = 0;
}
bool is_empty(Queue q)
{
	return q->size == 0;
}
bool is_full(Queue q)
{
	return q->size == q->capacity;
}
void enqueue(Queue q, Item i)
{
	if (is_full(q))
		reallocate(q);
	q->rear = (q->rear + 1) % q->capacity;
	q->contents[q->rear] = i;
	q->size++;
}
Item dequeue(Queue q)
{
	if (is_empty(q))
		terminate("Error in dequeue:queue is empty.");
	Item result = q->contents[q->front];
	q->front = (q->front + 1) % q->capacity;
	q->size--;
	return result;
}
Item peek(Queue q)
{
	if (is_empty(q))
		terminate("Error in peek: queue is empty.");
	return q->contents[q->front];
}
void reallocate(Queue q)
{
	Item *tmp = (Item *)malloc(2 * q->capacity * sizeof(Item));
	if (tmp == NULL)
		terminate("Error in create: queue could not be expanded.");
	int j = q->front;
	for (int i = 0;i < q->size;i++) {
		tmp[i] = q->contents[j];
		j = (j + 1) % q->capacity;
	}
	free(q->contents);

	q->front = 0;
	q->rear = q->size - 1;
	q->contents = tmp;
	q->capacity *= 2;
}


==========================================

queue.h



#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <stdbool.h> //C99 only
#include<stdio.h>
#include "pos.h"
typedef Position Item;

typedef struct queue_type *Queue;

Queue create();
void destroy(Queue q);
void make_empty(Queue q);
bool is_empty(Queue q);
void enqueue(Queue q, Item i);
Item dequeue(Queue q);
Item peek(Queue q);
int get_size(Queue q);

#endif


============================================



pos.h





#ifndef POS_H
#define POS_H

typedef struct pos {
	int x, y;
}Position;

Position move_to(Position pos, int dir);

#endif POS_H







==============================================


input.txt



16
0000100000001000
0110111111101010
0010001100101111
1110111110100010
1010000100111010
1011110111100000
0000000000011111
0000011110010001
0000000011110100
1101100001010110
0011011000000101
0111000100000101
0100010010000101
0101111010000101
1011001011001110
0000011000000010