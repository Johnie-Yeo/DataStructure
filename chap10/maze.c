#pragma warning(disable:4996)

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

int n;
int **maze;

#define pathway_colour 0      // white
#define wall_colour 1        // blue
#define blocked_colour 2      // red
#define path_colour 3        // green

bool findmazepath(int, int);
void read_maze();
void reset_maze();
int main() {
	printf("Size of maze:");
	scanf("%d", &n);
	read_maze();
	int count = 0;
	while (findmazepath(0, 0)) {
		count++;
		reset_maze();
	}
	printf("Answer: %d \n", count);

	return 0;
}
void reset_maze()
{
	maze[0][0] = pathway_colour;
	maze[n - 1][n - 1] = pathway_colour;
	for(int i=0;i<n;i++)
		for (int j = 0;j < n;j++) {
			if (maze[i][j] == path_colour)
				maze[i][j] = blocked_colour;
		}
}
bool findmazepath(int x, int y) {
	if (x < 0 || y < 0 || x >= n || y >= n || maze[x][y] != pathway_colour)
		return false;
	else if (x == n - 1 && y == n - 1) {
		maze[x][y] = path_colour;
		return true;
	}
	else {
		maze[x][y] = path_colour;
		if (findmazepath(x - 1, y) || findmazepath(x, y + 1)
			|| findmazepath(x + 1, y) || findmazepath(x, y - 1)) {
			return true;
		}
		maze[x][y] = blocked_colour;    // dead end
		return false;
	}
}
void read_maze()
{
	maze = (int**)malloc(n * sizeof(int*));
	for (int i = 0;i < n;i++) {
		maze[i] = (int *)malloc(n * sizeof(int));
	}
	for (int i = 0;i < n;i++)
		for (int j = 0;j < n;j++)
			scanf("%d", &maze[i][j]);
}