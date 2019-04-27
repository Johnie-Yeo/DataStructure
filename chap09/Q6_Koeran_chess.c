#pragma warning(disable:4996)

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct {
	int x;
	int y;
}Point;

int N;
int **maze;
#define PATHWAY_COLOUR 0

bool movable(Point Depart, Point Destin);
Point first_movement(Point Depart, int dir);
Point second_movement(Point Depart, int dir);
void printmaze();
void scan_maze(int n);

int main()
{
	Point depart;
	Point destin;

	printf("N:");
	scanf("%d", &N);
	printf("Departure: ");
	scanf("%d %d", &depart.x, &depart.y);
	printf("Destination: ");
	scanf("%d %d", &destin.x, &destin.y);
	
	scan_maze(N);

	if (movable(depart, destin) == true)
		printf("\nAvailable.\n\n");
	else
		printf("\nUnavailable.\n");

	printmaze();

	return 0;
}
void scan_maze(int n)
{
	maze = (int**)malloc(n * sizeof(int*));
	for (int i = 0;i < n;i++) {
		maze[i] = (int *)malloc(n * sizeof(int));
	}
	for (int i = 0;i < n;i++)
		for (int j = 0;j < n;j++)
			scanf("%d", &maze[i][j]);
}
bool movable(Point Depart, Point Destin)
{
	if (Depart.x < 0 || Depart.x >= N || Depart.y < 0 || Depart.y >= N ||
		Destin.x < 0 || Destin.y >= N || Destin.y < 0 || Destin.y >= N)
		return false;
	else if (maze[Depart.x][Depart.y] != PATHWAY_COLOUR ||
		maze[Destin.x][Destin.y] != PATHWAY_COLOUR)
		return false;
	else if (Depart.x == Destin.x&&Depart.y == Destin.y)
		return true;
	else {
		Point tmp;
		Point tmp_r;
		for (int i = 0;i < 4;i++) {
			tmp = first_movement(Depart, i);
			if (!movable(tmp, tmp))
				continue;
			else {
				tmp = first_movement(tmp, i);
				tmp_r = first_movement(tmp, (i + 1) % 4);
				if (tmp_r.x == Destin.x&&tmp_r.y == Destin.y)
					return true;
				else {
					tmp_r = first_movement(tmp, (i + 3) % 4);
					if (tmp_r.x == Destin.x&&tmp_r.y == Destin.y)
						return true;
				}
			}
		}
		return false;
	}
}
Point first_movement(Point Depart, int dir)
{
	Point tmp;
	int offset[4][2] = { { -1,0 },{ 0,-1 },{ 1,0 },{ 0,1 } };

	tmp.x = Depart.x + offset[dir][0];
	tmp.y = Depart.y + offset[dir][1];

	return tmp;
}
Point second_movement(Point Depart, int dir)
{
	Point tmp;
	int offset[4][2] = { {-1,-1},{-1,1},{1,-1},{1,1} };

	tmp.x = Depart.x + offset[dir][0];
	tmp.y = Depart.x + offset[dir][0];

	return tmp;
}
void printmaze()
{
	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}