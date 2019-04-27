#pragma warning(disable:4996)

#include<stdio.h>

int get_combination(int, int);
int main()
{
	int n;
	int k;
	int result;
	while (1) {
		printf("$ ");
		scanf("%d %d", &n, &k);

		if (n > 20) {
			printf("n should be lesser than 20.\n");
			break;
		}
		if (k < 0) {
			printf("Wrong Access.\n");
			break;
		}
		if (k > n) {
			printf("n should be greater than k.\n");
			break;
		}
		result = get_combination(n, k);
		printf("%dC%d= %d\n", n, k, result);
	}

	return 0;
}
int get_combination(int n, int k)
{
	if (n == k || k == 0)
		return 1;
	return (get_combination(n - 1, k) + get_combination(n - 1, k - 1));
}