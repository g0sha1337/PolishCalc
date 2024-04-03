#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "calculator.h"

int PriorityDefiner(Token token) { //def
	
	switch (token.type)
	{
		case OPERAND:
			if (token.data == '-' || token.data == '+') {
				return 1;
			}
			else if (token.data == '*' || token.data == '/') {
				return 2;
			}
			else if (token.data == '!' || token.data == '^') {
				return 3;
			}
		case FUNCTION: // �� �������� ����� ���� ��� �������
			return 4;	
			
	}


	return 0; // case indefined
}

Queue* ConvertToPolishs(Token* tokens, int size) { 

	int i = 0;
	Stack* stack = NewStack();
	initStack(stack);
	Queue* que = NewQueue();
	initQueue(que);

	int BracketFlag = 0;
	Token temp;
	while (tokens[i].type != END) { // semestr.online/informatics/polish.php

		if (tokens[i].type == VALUE || tokens[i].type == VARIABLE) {
			enqueue(que, tokens[i]);
		}
		else if (tokens[i].type == BRACKET_OPEN) {
			push(stack, tokens[i]);
			
		}
		else if (tokens[i].type == BRACKET_CLOSE) {
			while (!(isEmptyStack(stack)) && peek(stack).type != BRACKET_OPEN) {
				enqueue(que, pop(stack));
			}
			pop(stack); // remove (
		}
		if (!isEmptyStack(stack) && peek(stack).type == FUNCTION) {
			enqueue(que, pop(stack)); // Add the function to the queue after the last argument inside the brackets.
		}
		else if (tokens[i].type == OPERAND) {
			while (!isEmptyStack(stack) && peek(stack).type != END) { // ��������, ��� ���� �� ������ � �� ��� ������� �� END
				if (PriorityDefiner(tokens[i]) <= PriorityDefiner(peek(stack))) {
					enqueue(que, pop(stack));
				}
				else {
					break;
				}
			}
			push(stack, tokens[i]);
		}
		else if (tokens[i].type == FUNCTION) {
			push(stack, tokens[i]);
		}

		i++;
	}

	while (stack->start != NULL) { // while empty stack
		enqueue(que, pop(stack));
	}
	free(stack); // we are good boys 
	return que;

}

Token FunctionCalculate(Token func, Token val) {
	Token token;
	ClearToken(&token);
	if (func.type == FUNCTION) {
		token.type == VALUE;
		switch (func.func) {
		case __sin:
			token.value = sin(val.value);
			return token;
		case __cos:
			token.value = cos(val.value);
			return token;
		case __tg:
			token.value = tan(val.value);
			return token;
		case __arctg:
			token.value = atan(val.value);
			return token;
		case __arcctg:
			token.value = (3.14159265/2) - atan(val.value); // there isnt arcctg in math.h :(
			return token;
		case __arcsin:
			token.value = asin(val.value);
			return token;
		case __arccos:
			token.value = acos(val.value);
			return token;
		case __sqrt:
			token.value = sqrt(val.value);
			return token;
		case __factorial: //add
			if (val.value < 0 || val.value != (int)val.value) { // ���� ��������� ������������� - error
				token.type = ERROR;
				return token;
			}
			else {
				double result = 1.0;
				for (int i = 2; i <= val.value; ++i) {
					result *= i;
				}
				token.value = result;
				return token;
			}
		case __pow: //add
			token.value = pow(val.value, val.data);
			return token;
		}
	}
	return token;
}

//Token FucktorialCalculation(Token val) {
//	Token result;
//	ClearToken(&result);
//	if (val.value == 0) {
//		result.type = VALUE;
//		result.value = 1;
//		return result;
//	}
//	else {
//
//	}
//}

int factorial(int n) {
	if (n == 0) return 1;
	else return n * factorial(n - 1);
}
Token OperatorCalculation(Token val1, Token val2, Token oper) {
	Token token;
	ClearToken(&token);
	token.type = VALUE;
	switch (oper.data) {
	case '+':
		token.value = val1.value + val2.value;
		return token;
	case '-':
		token.value = val1.value - val2.value;
		return token;
	case '*':
		token.value = val1.value * val2.value;
		return token;
	case '/':
		if (val2.value != 0) {  // It is impossible to divide by zero, otherwise an error     ������ �� ���� ������, ����� ������
			token.value = val1.value / val2.value;
			return token;
		}
		else {
			token.type = ERROR;
			return token;
		}
	case '^': //add
		token.value = pow(val1.value, val2.value);
		return token;
	}
	token.type = ERROR;
	return token;
}


double calculate(Queue* que) {
	Stack* stack = NewStack();

	while (peek(que).type != END) {
		Token token;
		ClearToken(&token);
		token = dequeue(que);

		if (token.type == VALUE) {
			push(stack, token); // If the token is a number, put it on the stack      ���� ����� - �����, ��������� ��� � ����
		}
		else if (token.type == OPERAND) {
			// If the token is an operator, extract the top two numbers from the stack     ���� ����� - ��������, ��������� ��� ������� ����� �� �����
			Token resultToken;
			resultToken.type = VALUE;
			if (token.data == '!') {
				Token value = pop(stack);
				if (floor(value.value) == value.value && value.value >=0) { // fucktorial works only with integer
					resultToken.value = (double)factorial((int)value.value);
				}
				else {
					printf("Trying take factorial from bad number!");
				}
			}
			else {
				Token operand2 = pop(stack);
				Token operand1 = pop(stack);

				resultToken = OperatorCalculation(operand1, operand2, token);

			}
			
			// We throw the result on the stack   ������ ��������� � ����
			if (resultToken.type != ERROR) {
				push(stack, resultToken);
			}
			else {

				printf("Error: Division by zero\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (token.type == FUNCTION) {
			Token ValToken = pop(stack);
			Token res;
			ClearToken(&res);
			res = FunctionCalculate(token, ValToken);
			
			if (res.type != ERROR) {
				push(stack, res);
			}
			else {
				printf("Error: Division by zero or something else illigal\n");
				exit(-1);
			}
		}
	}

	// After the end of the loop, only one number should remain in the stack - the result of calculations   ����� ���������� ����� � ����� ������ �������� ������ ���� ����� - ��������� ����������
	Token finalResultToken = pop(stack);
	double finalResult = finalResultToken.value;

	// Freeing up the memory spent on the stack     ����������� ������, ����������� �� ����
	free(stack);

	return finalResult;
}

