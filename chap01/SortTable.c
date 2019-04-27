#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>

#define MAX 100
#define MAX_LEN 100

char *table[MAX][MAX];
int widths[MAX] = { 0 };

void print_blank(int k);
void add_entry(int i, int j, char entry[100]);

int main()
{
	char buffer[MAX_LEN], table_entry[MAX_LEN];
	int row, col;

	FILE *fin = fopen("input.txt", "r");
	fscanf(fin, "%d %d", &row, &col);

	int i = 0, j = 0;

	while (!feof(fin)) {
		fscanf(fin, "%s", buffer);

		if (strcmp(buffer, "&") == 0 || strcmp(buffer, "\\\\") == 0){
			add_entry(i, j, table_entry);
			table_entry[0] = '\0';
			if (strcmp(buffer, "&") == 0)
				j++;
			else
				i++, j = 0;
		}
		else {
			if (strlen(table_entry) > 0)
				strcat(table_entry, " ");
			strcat(table_entry, buffer);
		}
	}
	add_entry(i, j, table_entry);
	fclose(fin);

	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			printf("%s", table[i][j]);
			print_blank(widths[j] - strlen(table[i][j]) + 1);
			/*Above wo lines can be replaced with this single line.*/
			/*printf("%-*s",widths[j]+1,table[i][j]);*/
		}
		printf("\n");
	}
}
void print_blank(int k)
{
	for (int i = 0;i < k;i++)
		printf(" ");
}
void add_entry(int i, int j, char entry[100])
{
	table[i][j] = strdup(entry);
	if (strlen(entry) > widths[j])
		widths[j] = strlen(entry);
}