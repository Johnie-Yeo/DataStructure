#pragma warning(disable:4996)

#include<stdio.h>
#include<string.h>

#define BUFFER_SIZE 100

int compare(char *str1, char *str2);

int main()
{
	char str1[BUFFER_SIZE];
	char str2[BUFFER_SIZE];
	int result;
	while (1) {
		printf("$ ");
		scanf("%s", str1);

		if (strcmp(str1, "exit") == 0)
			break;
		scanf("%s", str2);

		result = compare(str1, str2);
		if (result == -1)
			printf("%s is earlier than %s by dictionary order.\n", str1, str2);
		else if (result == 0)
			printf("Both words are same.\n");
		else if (result == 1)
			printf("%s is greater than %s by dictionary order.\n", str1, str2);
	}

	return 0;
}
int compare(char *str1, char *str2)
{
	if (*str1 == '\0')
		*str1 = 0;
	if (*str2 == '\0')
		*str2 = 0;
	if (*str1 > *str2)
		return 1;
	else if (*str1 < *str2)
		return -1;
	else if (*str1 == *str2)
		compare(str1 + 1, str2 + 1);
}
