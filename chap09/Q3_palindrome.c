
#pragma warning(disable:4996)

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define BUFFER_SIZE 100
bool judge_palindrome(char *);

int main()

{
	char word[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf("%s", word);

		if (judge_palindrome(word) == true)
			printf("%s is a palindrome.\n", word);

		else {
			printf("%s is not a palindrome.\n", word);
			break;
		}
	}

	return 0;
}
bool judge_palindrome(char *word)
{
	int len = strlen(word);
	char buffer[BUFFER_SIZE];
	if (len == 0 || len == 1)
		return true;
	if (word[0] == word[len - 1]) {
		for (int i = 0; i < len; i++)
			buffer[i] = word[i + 1];
		buffer[len - 2] = '\0';
		judge_palindrome(buffer);
	}
	else
		return false;
}