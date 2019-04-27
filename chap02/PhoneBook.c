#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INIT_CAPACITY 3 //배열 재할당을 위해 작은값
#define BUFFER_SIZE 50

char **names; //names
char **numbers;//numbers
int n = 0; // number of people in the directory
int capacity = INIT_CAPACITY;//size of arrays

							 /*function prototypes here*/
void init_directory();
int read_line(char str[], int limit);
void process_command();
void load(char *fileName);
void add(char *name, char *number);
void find(char *name);
void status();
int search(char *name);
void remove(char *name);
void save(char *fileName);
void reallocate();
void find_p(char *name_p);
int remove_p(char *name_p);
/*Until here*/

char delim[] = " ";

int main()
{
	init_directory();//이 함수에서 배열 names와 numbers 생산
	process_command();// 사용자 명령을 받아 처리하는 부분을 별개의 함수로 만듬

	return 0;
}
void init_directory()
{
	names = (char **)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char **)malloc(INIT_CAPACITY * sizeof(char*));
}
int read_line(char str[], int limit)
{
	int ch, i = 0;

	while ((ch = getchar()) != '\n')
		if (i<limit - 1)
			str[i++] = ch;

	str[i] = '\0';
	return i;

}
void process_command()
{
	char command_line[BUFFER_SIZE];
	char *command, *argument1, *argument2;

	while (1) {
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE) <= 0)
			continue;
		command = strtok(command_line, delim);
		if (command == NULL)continue;
		if (strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("file name required.\n");
				continue;
			}
			load(argument1);
		}
		else if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);

			if (argument1 == NULL || argument2 == NULL) {
				printf("INVALID ARGUMENTS.\n");
				continue;
			}
			add(argument1, argument2);

			printf("%s was added successfully.\n", argument1);
		}
		else if (strcmp(command, "find") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("INVALID ARGUMENTS.\n");
				continue;
			}
			else if (strcmp(argument1,"-p")==0) {
				int count = 0;
				argument2 = strtok(NULL, delim);
				while (argument2 != NULL) {
					find_p(argument2);
					count++;
					argument2 = strtok(NULL, delim);
				}
				printf("%d people found.\n",count);
			}
			else {
				find(argument1);
			}
		}
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("INVALID ARGUMENTS.\n");
				continue;
			}
			else if (strcmp(argument1,"-p")==0) {
				int count_r = 0;
				argument2 = strtok(NULL, delim);
				while (argument2 != NULL) {
					count_r=remove_p(argument2);
					argument2 = strtok(NULL, delim);
				}
				printf("%d people deleted.\n", count_r);
			}
			else {
				remove(argument1);
			}
		}
		else if (strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);

			if (argument1 == NULL || strcmp("as", argument1) != 0 || argument2 == NULL)
			{
				printf("INVALID ARGUMENTS.\n");
				continue;
			}
			save(argument2);
		}
		else if (strcmp(command, "exit") == 0) {
			printf("SYSTEM DOWN.\n");
			break;
		}
	}
}
void load(char *fileName)
{
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
	}
	fclose(fp);
}
void add(char *name, char *number)
{
	if (n >= capacity)
		reallocate();
	int i = n - 1;
	while (i >= 0 && strcmp(names[i], name) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i + 1];
		i--;
	}
	names[i + 1] = strdup(name);
	numbers[i + 1] = strdup(number);

	n++;
}
void find(char *name)
{
	int idx = search(name);
	if (idx == -1)
		printf("No person named '%s' exists.\n", name);
	else
		printf("%s\n", numbers[idx]);
}
void status()
{
	int i;
	for (i = 0;i < n;i++)
		printf("%s\t%s\n", names[i], numbers[i]);
	printf("Total %d people.\n", n);
}
int search(char *name)
{
	int i;
	for (i = 0;i < n;i++)
		if (strcmp(names[i], name) == 0)
			return i;
	return -1;
}
void remove(char *name)
{
	int i = search(name);
	if (i = -1) {
		printf("No person named '%s' exists.\n", name);
		return;
	}
	int j = i;
	for (;j < n - 1;j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'$s' was deleted successfully.\n", name);
}
void save(char *fileName)
{
	int i;

	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	for (i = 0;i < n;i++)
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	fclose(fp);
}
void reallocate()
{
	int i;

	capacity *= 2;
	char **tmp1 = (char**)malloc(capacity * sizeof(char*));
	char **tmp2 = (char**)malloc(capacity * sizeof(char*));

	for (i = 0;i < n;i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}
	free(names);
	free(numbers);

	names = tmp1;
	numbers = tmp2;
}
void find_p(char *name_p)
{
	char buffer[BUFFER_SIZE];
	int i;
	for (i = 0;i < n;i++) {
		strcpy(buffer,names[i]);
		buffer[strlen(name_p)] = '\0';
		if (strcmp(buffer, name_p) == 0) {
			printf("%s %s\n", names[i], numbers[i]);
		}
	}
}
int remove_p(char *name_p)
{
	char buffer[BUFFER_SIZE];
	char answer[10];
	int i;
	static int count=0;
	for (i = 0;i < n;i++) {
		strcpy(buffer, names[i]);
		buffer[strlen(name_p)] = '\0';
		if (strcmp(buffer, name_p) == 0) {
			printf("Do you want to delete '%s'? ", names[i]);
			read_line(answer, 10);
			if (strcmp(answer, "yes") == 0) {
				printf("%s was deleted.\n", names[i]);
				remove(names[i]);
				count++;
			}
			else continue;
		}
	}
}
//
#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INITCAPACITY 3
#define BUFFER_SIZE 50

char **names;
char **numbers;
int capacity = INITCAPACITY;
int n = 0;

void init_directory();
int read_line(char str[], int limit);
void process_command();
void load(char *fileName);
void save(char *fileName);
void remv(char *name);
void status();
int search(char *name);
void reallocate();
int add(char *name, char *number);
void find(char *name);
int find_p(char *name);
int remv_p(char *name);
char delim[] = " ";

int main()
{
   init_directory();
   process_command();

   return 0;
}

void init_directory() {
   names = (char **)malloc(INITCAPACITY * sizeof(char *));
   numbers = (char **)malloc(INITCAPACITY * sizeof(char *));
}

int read_line(char str[], int limit) {
   int ch, i = 0;

   while ((ch = getchar()) != '\n')
      if (i < limit - 1)
         str[i++] = ch;

   str[i] = '\0';

   return i;
}

void process_command() {
   char command_line[BUFFER_SIZE];
   char *command, *argument1, *argument2;

   while (1) {
      printf("$ ");

      if (read_line(command_line, BUFFER_SIZE) <= 0)
         continue;

      command = strtok(command_line, delim);
      if (command == NULL)continue;

      if (strcmp(command, "read") == 0) {
         argument1 = strtok(NULL, delim);

         if (argument1 == NULL) {
            printf("File name required.\n");
            continue;
         }
         load(argument1);
      }
      else if (strcmp(command, "add") == 0) {
         int re;
         argument1 = strtok(NULL, delim);
         argument2 = strtok(NULL, delim);

         if (argument1 == NULL || argument2 == NULL) {
            printf("Invalid arguments\n");
            continue;
         }

         re = add(argument1, argument2);

         if (re == 0)
            continue;
         printf("%s was added successfully.\n", argument1);
      }
      else if (strcmp(command, "find") == 0) {
         int num = 0;
         int index = 0;
         argument1 = strtok(NULL, delim);

         if (strcmp(argument1, "-p") == 0) {
            argument2 = strtok(NULL, delim);
            if (argument2 == NULL) {
               printf("Invalid arguments.\n");
               continue;
            }
            while (argument2 != NULL) {
               index = find_p(argument2);
               num += index;
               argument2 = strtok(NULL, delim);
            }
            if (num == 0)
               printf("no person named exist.\n");
            else if (num == 1)
               printf("%d person found.\n", num);
            else
               printf("%d persons found.\n", num);
         }

         else if (argument1 == NULL) {
            printf("Invalid arguments.\n");
            continue;
         }
         else find(argument1);
      }
      else if (strcmp(command, "status") == 0)
         status();
      else if (strcmp(command, "delete") == 0) {
         int num = 0;
         int index = 0;
         argument1 = strtok(NULL, delim);
         if (strcmp(argument1, "-p") == 0) {
            argument2 = strtok(NULL, delim);
            if (argument2 == NULL) {
               printf("Invalid arguments.\n");
               continue;
            }
            while (argument2 != NULL) {
               index = remv_p(argument2);
               num += index;
               argument2 = strtok(NULL, delim);
            }
            if (num == 0)
               printf("no person named exist.\n");
            else if (num == 1)
               printf("%d person deleted.\n", num);
            else
               printf("%d persons deleted.\n", num);
         }
         else if (argument1 == NULL) {
            printf("Invalid arguments\n");
            continue;
         }
         remv(argument1);
      }
      else if (strcmp(command, "save") == 0) {
         argument1 = strtok(NULL, delim);
         argument2 = strtok(NULL, delim);
         if (argument1 == NULL || strcmp("as", argument1) != 0 || argument2 == NULL) {
            printf("Invalid command format.\n");
            continue;
         }
         save(argument2);
      }
      else if (strcmp(command, "exit") == 0)
         break;
   }
}

void load(char *fileName) {
   char buf1[BUFFER_SIZE];
   char buf2[BUFFER_SIZE];

   FILE*fp = fopen(fileName, "r");
   if (fp == NULL) {
      printf("open failed\n");
      return;
   }
   while ((fscanf(fp, "%s", buf1) != EOF)) {
      fscanf(fp, "%s", buf2);
      add(buf1, buf2);
   }
   fclose(fp);
}

void save(char *fileName) {
   int i;

   FILE*fp = fopen(fileName, "w");
   if (fp == NULL) {
      printf("Open failed.\n");
      return;
   }
   for (i = 0; i < n; i++)
      fprintf(fp, "%s %s\n", names[i], numbers[i]);

   fclose(fp);
}

void remv(char *name) {
   int i = search(name);

   if (i == -1) {
      printf("no person named '%s'exist/\n", name);
      return;
   }

   int j = i;

   for (; j < n - 1; j++) {
      names[j] = names[j + 1];
      numbers[j] = numbers[j + 1];
   }
   n--;

   printf("'%s' was deleted successfully.\n", name);
}

void status() {
   int i;

   for (i = 0; i < n; i++)
      printf("%s %s\n", names[i], numbers[i]);
   printf("Total %d persons.\n", n);
}

void find(char *name) {
   int index = search(name);

   if (index == -1)
      printf("no person named '%s' exists.\n", name);
   else
      printf("%s\n", numbers[index]);
}

int search(char *name) {
   int i;

   for (i = 0; i < n; i++) {
      if (strcmp(name, names[i]) == 0)
         return i;
   }
   return -1;
}

int add(char *name, char *number) {
   if (n >= capacity)
      reallocate();

   if (number[0] == '-' || number[strlen(number) - 1] == '-') {
      printf("Invalid phone number.\n");
      return 0;
   }
   for (int a = 1; a < strlen(number); a++) {

      if (number[a] == '+') {
         printf("Invalid phone number.\n");
         return 0;
      }
      else if (number[a] == '-' && (number[a - 1] == '-' || number[a - 1] == '+')) {
         printf("Invalid phone number.\n");
         return 0;
      }
   }

   int i = n - 1;

   while (i >= 0 && strcmp(names[i], name) > 0) {
      names[i + 1] = names[i];
      numbers[i + 1] = numbers[i];
      i--;
   }
   names[i + 1] = strdup(name);
   numbers[i + 1] = strdup(number);
   n++;
}

void reallocate() {
   int i;
   capacity *= 2;
   char **tmp1 = (char **)malloc(capacity * sizeof(char*));
   char **tmp2 = (char **)malloc(capacity * sizeof(char *));

   for (i = 0; i < n; i++) {
      tmp1[i] = names[i];
      tmp2[i] = numbers[i];
   }
   free(names);
   free(numbers);

   names = tmp1;
   numbers = tmp2;
}

int find_p(char *name) {
   int i = 0, j;
   int count = 0;

   while (i < n) {
      for (j = 0; j < strlen(name); j++) {
         if (name[j] != names[i][j])
            break;
      }
      if (j == strlen(name)) {
         printf("%s %s\n", names[i], numbers[i]);
         count++;
      }
      i++;
   }

   return count;
}

int remv_p(char *name) {
   int i = 0, j;
   int count = 0;

   while (i < n) {
      for (j = 0; j < strlen(name); j++) {
         if (name[j] != names[i][j])
            break;
      }
      if (j == strlen(name)) {
         char ans[BUFFER_SIZE];
         printf("Do you want to delete '%s' ? ", names[i]);
         fgets(ans, BUFFER_SIZE, stdin);
         ans[strlen(ans) - 1] = '\0';
         if (strcmp(ans, "yes") == 0) {
            printf("%s was deleted.\n", names[i]);
            for (j = i; j < n - 1; j++) {
               names[j] = names[j + 1];
               numbers[j] = numbers[j + 1];
            }
            n--;
            i--;
            count++;
         }
         else {
            printf("%s was not deleted.\n", names[i]);
         }
      }
      i++;
   }
   return count;
}