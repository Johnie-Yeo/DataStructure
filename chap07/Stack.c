main.cpp



#include "stack.h"

#define MAX_LENGTH 100

int read_line(FILE *, char[], int);

int main()
{
	char infix[MAX_LENGTH];
	while (1) {
		printf("$ ");
		if (read_line(stdin, infix, MAX_LENGTH) < 0)
			return -1;
		if (strcmp(infix, "exit") == 0)
			break;
		printf("Result = %d\n", convert(infix));

	}
	return 0;
}
int read_line(FILE *fp, char str[], int n)
{
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n'&&ch != EOF)
		if (i < n - 1)
			str[i++] = ch;

	str[i] = '\0';
	return i;
}

==============================================

stack.cpp


#include "stack.h"

struct node {
	Item data;
	struct node *next;
};
struct stack_type {
	struct node *top;
};

static void terminate(const char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}
Stack create()
{
	Stack s = (Stack)malloc(sizeof(struct stack_type));
	if (s == NULL)
		terminate("Error in create:stack could not be created.");
	s->top = NULL;
	return s;
}
void destroy(Stack s)
{
	make_empty(s);
	free(s);
}
void make_empty(Stack s)
{
	while (!is_empty(s))
		pop(s);
}
bool is_empty(Stack s)
{
	return s->top == NULL;
}
void push(Stack s, Item i)
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	if (new_node == NULL)
		terminate("Error in push: stack is full.");

	new_node->data = i;
	new_node->next = s->top;
	s->top = new_node;
}
Item pop(Stack s)
{
	struct node *old_top;
	Item i;

	if (is_empty(s))
		terminate("Error in pop:stack is empty.");

	old_top = s->top;
	i = old_top->data;
	s->top = old_top->next;
	free(old_top);
	return i;
}
Item peek(Stack s)
{
	if (is_empty(s))
		terminate("Error in peek: stack is empty.");
	return s->top->data;
}

=============================================

calculate.cpp


#include "stack.h"

static char OPERATORS[] = "+-*/()";
static int PRECEDENCE[] = { 1,1,2,2,-1,-1 };
//여는 괄호의 우선순위를 -1로 정의. 이렇게 하면 2번 규칙을 예외로 처리할 필요가 없다.
Stack operator_stack;//연산자
Stack operand_stack;//피연산자

int precedence(char op);
int is_operator(char ch);
void handle_exception(const char *err_msg);
char *process_op(char op, char *pos);
int eval_op(char op);

int precedence(char op)
{
	return PRECEDENCE[is_operator(op)];
}
int is_operator(char ch)
{
	for (int i = 0;i < strlen(OPERATORS);i++)
		if (OPERATORS[i] == ch)
			return i;
	return -1;
}
void handle_exception(const char *err_msg)
{
	printf("%s\n", err_msg);
	exit(1);
}
/*int convert(char *infix)
{
int result = 0;
long convert_value = 0;

operator_stack = create();
operand_stack = create();

char *postfix = (char*)malloc(strlen(infix) + 1);
char *pos = postfix;

char *token = strtok(infix, " ");
while (token != NULL){
if (token[0] >= '0'&&token[0] <= '9') {
sprintf(pos, "%s ", token);
pos += (strlen(token) + 1);
push(operand_stack, atoi(token));
}
else if (is_operator(token[0]) > -1) {
pos = process_op(token[0], pos);
}
else {
handle_exception("Syntax Error: invalid character encountered.");
}
token = strtok(NULL, " ");
}

while (!is_empty(operator_stack)) {
char op = (char)pop(operator_stack);
push(operand_stack, eval_op(op));
if (op == '0')//스택에 괄호가 남이 있어서는 안된다.
handle_exception("Unmatched parenthesis.");
sprintf(pos, "%c", op);
pos += 2;
}
*pos = '\0';

result = peek(operand_stack);

return result;
}*/
int convert(char *data)
{
	int result = 0;
	char  buffer[20];

	operator_stack = create();
	operand_stack = create();

	char *infix = strdup(data);
	char *pos = (char *)malloc(strlen(infix) + 1);
	char *token;
	int count = 0;
	while (strlen(infix)!=0) {
		long convert_value = strtol(infix, &token, 10);
		if (is_operator(infix[0]) == -1||count==0||(count>1&&data[count]=='(')) {
			push(operand_stack, convert_value);
			itoa(convert_value, buffer, 10);
			sprintf(pos, "%s", buffer);
			pos += strlen(buffer);
			infix += strlen(buffer);
		}
		else {
			pos = process_op(infix[0], pos);
			infix += 1;
		}
		count++;
	}
	while (!is_empty(operator_stack)) {
		int tmp_result = 0;
		char op = (char)pop(operator_stack);
		tmp_result = eval_op(op);
		push(operand_stack, tmp_result);
		if (op == '0')//스택에 괄호가 남이 있어서는 안된다.
			handle_exception("Unmatched parenthesis.");
		sprintf(pos, "%c", op);
		pos += 1;
	}
	*pos = '\0';

	result = peek(operand_stack);

	return result;
}
char *process_op(char op, char *pos)
{
	int result = 0;

	if (is_empty(operator_stack) || op == '(')//여는 괄호는 그냥 스택에 push 한다.
	{
		push(operator_stack, op);
	}
	else {
		char top_op = peek(operator_stack);
		if (precedence(op) > precedence(top_op))
		{
			push(operator_stack, op);
		}
		else {
			while (!is_empty(operator_stack) && precedence(op) <= precedence(top_op)) {
				pop(operator_stack);
				if (top_op == '(')
					break;//op의 우선순의가 top_op보다 낮거나 같은데 top_op가 닫는 괄호이면 op는 닫는 괄호라는 의미이다.
				result = eval_op(top_op);
				push(operand_stack, result);
				sprintf(pos, "%c ", top_op);
				pos += 1;
				if (!is_empty(operator_stack))
					top_op = (char)peek(operator_stack);
			}
			if (op != ')')//닫는 괄호는 스택에 push하지 않는다.
			{
				push(operator_stack, op);
			}
		}
	}
	return pos;
}
int eval_op(char op)
{
	if (is_empty(operand_stack))
		handle_exception("Syntax Error: Stack empty in eval_op.(rh)");
	int rhs = pop(operand_stack);
	if (is_empty(operand_stack))
		handle_exception("Syntax Error: Stack empty in eval_op.(lh)");
	int lhs = pop(operand_stack);
	int result = 0;
	switch (op)
	{
	case '+':
		result = lhs + rhs;
		break;
	case '-':
		result = lhs - rhs;
		break;
	case '*':
		result = lhs * rhs;
		break;
	case '/':
		result = lhs / rhs;
		break;

	}
	return result;
}


===============================================


stack.h


#ifndef STACK_H
#define STACK_H

#pragma warning(disable:4996)
#include<stdbool.h> /*C99 only*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int Item;

typedef struct stack_type *Stack;

Stack create();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);
int convert(char *infix);

#endif