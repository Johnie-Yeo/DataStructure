#pragma warning(disable:4996)

#include<stdio.h>
#include<stdbool.h>
#include<math.h>

int cols[16];
int N;
int count;

bool queens(int level);
bool promising(int level);

int main()
{
	while(1){
		count = 0;
		printf("N: ");
		scanf("%d", &N);
		if (N == 0)
			break;
		if (N > 15) {
			printf("N should be lesser than 16.\n");
			continue;
		}
		queens(0);
		printf("count: %d\n", count);
	}
	return 0;
}
bool queens(int level) {
	if (!promising(level))    
		return false;
	else if (level == N) {
		/*printf("%d.", count);
		for (int i = 1; i <= N; i++)
			printf("(%d, %d)", i, cols[i]);
		printf("\n");*/
		count++;
		return true;
	}
	for (int i = 1; i <= N; i++) {
		cols[level + 1] = i;
		queens(level + 1);
	}
	return false;
}
bool promising(int level) {
	for (int i = 1; i<level; i++) {
		if (cols[i] == cols[level])
			return false;    
		else if (level - i == abs(cols[level] - cols[i]))      
			return false;
	}
	return true;
}

