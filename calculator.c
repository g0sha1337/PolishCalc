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
			
	}


	return 0; // case indefined
}


//void ClearToken(Token* token) {
//	token->data = '\0';
//	token->type = NONE;
//	token->value = 0.00;
//	token->func = NONE;
//}

Queue* ConvertToPolishs(Token* tokens, int size) { //MANY BAGS!!! FIXXX THEM TOMORROW

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
			Token operand2 = pop(stack);
			Token operand1 = pop(stack);

			Token resultToken = OperatorCalculation(operand1, operand2, token);

			// We throw the result on the stack   Кидаем результат в стек
			if (resultToken.type != ERROR) {
				push(stack, resultToken);
			}
			else {

				printf("Error: Division by zero\n");
				exit(EXIT_FAILURE);
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

