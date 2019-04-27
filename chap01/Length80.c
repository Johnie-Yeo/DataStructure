#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX_LEN 100
#define LINE_WIDTH 80

int count_word(char buffer[], int *total_len);
void output_line(FILE *, char buffer[], int wcount, int len);
void output_blank(FILE *, int gap);

int main()
{
	char buffer[MAX_LEN];
	FILE *fin = fopen("harry.txt", "r");
	FILE *fout = fopen("aligned.txt", "w");
	int line = 1;
	do {
		fgets(buffer, MAX_LEN, fin);
		line++;
		if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n')
			buffer[strlen(buffer) - 1] == '\0';
		int count_chars = 0;
		int count_words =count_word(buffer, &count_chars);
		output_line(fout, buffer, count_words, count_chars);
		buffer[0] = '\0';
	} while (!feof(fin));
	fclose(fin);
	fclose(fout);
}
int count_word(char buffer[], int *total_len)
{
	int count = 0;
	for (int i = 0;i < strlen(buffer);i++) {
		if ((i == 0 || isspace(buffer[i - 1])) && !isspace(buffer[i]))
			count++;
		if (!isspace(buffer[i]))
			(*total_len)++;
	}
	return count;
}
void output_line(FILE *fout, char buffer[], int wcount, int total_len)
{
	if (wcount == 0) {
		fprintf(fout, "\n");
		return;
	}
	else if (wcount == 1) {
		while (isspace(*buffer))
			buffer++;
		fprintf(fout, "%s", buffer);
		return;
	}
	int gap = (LINE_WIDTH - total_len) / (wcount - 1);
	int remainder = (LINE_WIDTH - total_len) % (wcount - 1);
	int width = 0;
	for (int i = 0, k = 0; i < strlen(buffer) && width < 80;i++) {
		if (i != 0 && !isspace(buffer[i - 1]) && isspace(buffer[i])) {
			if (k < remainder)
				output_blank(fout, gap + 1), width += (gap + 1);
			else
				output_blank(fout, gap), width += gap;
			k++;
		}
		else if (!isspace(buffer[i])) {
			fprintf(fout, "%c", buffer[i]);
			width++;
		}
	}
	fprintf(fout, "\n");
}
	void output_blank(FILE *fout, int gap)
{
		for (int i = 0;i < gap;i++)
			fprintf(fout, " ");
}