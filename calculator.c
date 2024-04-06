#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "structures.h"
#include "calculator.h"
#include "tokenizer.h"

int KnownVarsPositions[28] = { 0 };
double KnownVars[28] = { '\0' };
int TabsCounter = 0;

void ClearVariables() { // Очистка значений в переменных
	for (int i = 0; i < sizeof(KnownVarsPositions) / sizeof(KnownVarsPositions[0]); i++) {
		KnownVarsPositions[i] = 0;
	}
}

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
		case FUNCTION: // Мы добавили новый кейс для функций
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
			while (!isEmptyStack(stack) && peek(stack).type != END) { // ѕровер¤ем, что стек не пустой и на его вершине не END
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
			if (val.value < 0 || val.value != (int)val.value) { // Если факториал отрицательный - error
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
		if (val2.value != 0) {  // It is impossible to divide by zero, otherwise an error     Делить на ноль нельзя, иначе ошибка
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
			push(stack, token); // If the token is a number, put it on the stack      Если токен - число, поместите его в стек
		}
		else if (token.type == OPERAND) {
			// If the token is an operator, extract the top two numbers from the stack     Если токен - оператор, извлеките два верхних числа из стека
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
			
			// We throw the result on the stack   Кидаем результат в стек
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

	// After the end of the loop, only one number should remain in the stack - the result of calculations   После завершения цикла в стеке должно остаться только одно число - результат вычислений
	Token finalResultToken = pop(stack);
	double finalResult = finalResultToken.value;

	// Freeing up the memory spent on the stack     Освобождаем память, затраченную на стек
	free(stack);
	
	return finalResult;
}

int VariableFinder(Token* array) {
	while (array->type != END) {
		if (array->type == VARIABLE) return 1;

		array++;
	}
	return 0;
}

int GetIndexLetter(char letter) {
	letter = tolower(letter);
	if (letter >= 'a' && letter <= 'z') {
		// Возвращаем индекс от 0 до 25
		return letter - 'a';
	}
	else {
		return -1;
	}
}

int IsPreviouslyKnownVariable(Token token) {
	int index = GetIndexLetter(token.data);

	if (KnownVarsPositions[index]) { //if variable was defined earlier
		return 1;
	}
	return 0;

}

void DefineNewVariable(Token* array) {
	for (int i = 0; array[i].type != END; i++) {
		if (array[i].type == VARIABLE) {

			// if info exist 'bout var earlier
			if (IsPreviouslyKnownVariable(array[i])) {
				array[i].type = VALUE;
				array[i].value = KnownVars[GetIndexLetter(array[i].data)]; // grab known value to our variable and make it type = VALUE
			}
			else {
				TabsCounter += 5;
				printf("\n");
				for (int i = 0; i < TabsCounter; i++) { //UI :3
					printf("-");
				}
				char str[256] = { '\0' };
				printf("[%c]: ", array[i].data);

				
				scanf("%255[^\n]%*c", str);


				int length = strlen(str) + 10;
				Token* newtokens = tokenizer(str, length);
				//printf("new tokens from tokenizer ");
				//printTokens(newtokens, length);
				if (VariableFinder(newtokens)) {
					//DefineNewVariable(newtokens);
					printf("Adding vars to vars soon..");
					exit(-1);
					//bag here~!~
				}
				else {
					TabsCounter -= 5;
					Queue* PolishTokens = ConvertToPolishs(newtokens, length);

					double CalculatedValue = calculate(PolishTokens);
					//rintf("( = %.2f)", CalculatedValue);
					KnownVars[GetIndexLetter(array[i].data)] = CalculatedValue;

					array[i].type = VALUE;
					array[i].value = KnownVars[GetIndexLetter(array[i].data)];
					KnownVarsPositions[GetIndexLetter(array[i].data)] = 1;

				}
				//printf("\n\n\n");
				//printTokens(newtokens, length);

				free(newtokens);

			}


		}
	}
	return;
}