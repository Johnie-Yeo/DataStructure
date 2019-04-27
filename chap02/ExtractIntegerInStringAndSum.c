#include<stdio.h>

#define SIZE 100
int main()
{
	char str[SIZE];
	int num[50] = { 0 };
	int sum = 0;
	int i = 0,a=0;

	gets_s(str,SIZE);

	while (str[a]!='\0') {
		if (str[a] >= '0'&&str[a] <= '9') {
			num[i] = num[i] * 10 + (str[a]) - '0';
			if (str[a+1]<'0' || str[a+1]>'9') {
				sum += num[i];
				i++;
			}
		}
		a++;
		
	}
	for (int s = 0;s < i-1;s++)
		printf("%d+", num[s]);
	printf("%d=%d", num[i-1], sum + num[i]);
	

	return 0;
}