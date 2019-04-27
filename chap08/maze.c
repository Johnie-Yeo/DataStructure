input.txt

16
0000100000001000
0110101111101010
0010000000101011
1011111110100010
0000000100111010
1111111111000000
0000000000111011
0111011110000001
0000000011110100
0101011001000110
0001011100010100
0111000110110101
0100010000110101
0001111010010100
0111011011101110
0000000000000000


===============================


main.cpp


#pragma warning(disable:4996)

#include<stdio.h>
#include "queue.h"
#include "pos.h"

#define MAX 100
#define PATH 0
#define WALL 1

int maze[MAX][MAX];
int n; //미로의 크기

void read_maze();
bool movable(Position pos, int dir);
void print_maze();

int main()
{
	read_maze();

	Queue queue = create();
	Position cur;

	cur.x = 0;
	cur.y = 0;
	cur.dir = 5;//편의성(시작할때)
	enqueue(queue, cur);

	maze[0][0] = -1;
	bool found = false;

	while (!is_empty(queue)) {
		Position cur = dequeue(queue);
		for (int dir = 0;dir < 4;dir++) {
			if (movable(cur, dir)) {
				if (cur.dir == (dir + 2) % 4)//왔던길로 돌아감 방지
					continue;
				else {
					Position p = move_to(cur, dir);

					int tmp = maze[p.x][p.y];//기존에 (p.x , p,y) 에 있던 값
					if (p.dir == cur.dir) {
						if (tmp < maze[cur.x][cur.y] || tmp == 0)
							maze[p.x][p.y] = maze[cur.x][cur.y];
						else
							continue;
					}
					else {
						if (tmp < maze[cur.x][cur.y] - 1) {
							maze[p.x][p.y] = maze[cur.x][cur.y] - 1;
							p.dir = cur.dir;
						}
						else if (tmp == 0) {
							maze[p.x][p.y] = maze[cur.x][cur.y] - 1;
						}
						else
							continue;
					}

					if (p.x == n - 1 && p.y == n - 1) {
						printf("Found the path.\n");
						found = true;
						break;
					}
					enqueue(queue, p);
				}
			}
		}
	}
	if (found == true) {
		
		print_maze();
	}
	else
		printf("There isn't any exit.\n");

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
	if (tmp.x < 0 || tmp.x>(n - 1) || tmp.y < 0 || tmp.y>(n - 1))
		return false;

	if (maze[tmp.x][tmp.y] == 1)
		return false;
	else
		return true;//벽을 제외하고는 모두 true 최솟값을 찾기 위해

}
void print_maze()
{
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			/*if (maze[i][j] <0)
				printf("* ");
			else if (maze[i][j] == 1)
				printf("1 ");
			else
				printf("  ");*/
			printf("%5d", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
=========================================



=================================

pos.cpp


#include "pos.h"

int offset[4][2] = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 }};
//북:1 동:2 남:3 서:4 북동:5 동남:6 남서:7 서북:8
Position move_to(Position pos, int dir) {
	Position next;
	next.x = pos.x + offset[dir][0];
	next.y = pos.y + offset[dir][1];
	next.dir = dir;

	return next;
}
==================================

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

====================================

pos.h




#ifndef POS_H
#define POS_H

typedef struct pos {
	int x, y;
	int dir;
}Position;

Position move_to(Position pos, int dir);

#endif POS_H

============================

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

