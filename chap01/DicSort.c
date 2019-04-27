#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>

#define MAX 10000
#define BUFFER_SIZE 100

char *words[MAX];
int freq[MAX];
int n = 0;

void add_word(char buffer[100]);
void sort_words();

int main()
{
	char buffer[BUFFER_SIZE];

	FILE *fin = fopen("harry.txt", "r");
	FILE *fout = fopen("words.txt", "w");
	while(!feof(fin)) {
		fscanf(fin, "%s", buffer);
		add_word(buffer);
	}
	sort_words();

	for (int i = 0;i < n;i++)
		fprintf(fout, "%s: %d\n", words[i], freq[i]);
	fclose(fin);
	fclose(fout);

	return 0;
}
void sort_words()
{
	for (int i = n - 1;i > 0;i--) {
		for (int j = 0;j < i;j++) {
			if (strcmp(words[j], words[j + 1]) > 0) {
				char *tmp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = tmp;
				int t = freq[j];
				freq[j] = freq[j + 1];
				freq[j + 1] = t;
			}
		}
	}
}
void add_word(char buffer[])
{
	for (int i = 0;i < n;i++) {
		if (strcmp(buffer, words[i]) == 0) {
			freq[i]++;
			return;
		}
	}
	words[n] = strdup(buffer);
	freq[n++] = 1;
}