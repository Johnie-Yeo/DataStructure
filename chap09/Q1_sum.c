#pragma warning(disable:4996)
#include<stdio.h>

int get_sum(int);
int main()
{
	int num;
	int result;

	printf("Number: ");
	scanf("%d", &num);

	result = get_sum(num);

	printf("Sum: %d", result);

	return 0;
}
int get_sum(int num)
{
	static int result = 0;
	if (num == 0)
		return result;
	if (num % 3 == 0 || num % 5 == 0)
		result += num;
	return get_sum(num - 1);
}
