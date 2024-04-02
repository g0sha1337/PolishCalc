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
			while (!isEmptyStack(stack) && peek(stack).type != END) { // ѕровер€ем, что стек не пустой и на его вершине не END
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
		case '+': {
			token.value = val1.value + val1.value;
			return token;
		}case '-': {
			token.value = val1.value - val1.value;
			return token;
		}case '*': {
			token.value = val1.value * val1.value;
			return token;
		}
		case '/': {
			token.value = val1.value / val1.value;
			return token;
		}
	}
	token.type = ERROR;
	return token;

}

double calculate(Queue* que) {

	Stack* stack = NewStack();

	while (peek(stack).type != END) {

		Token token;
		ClearToken(&token);
		token = dequeue(que);

		// do later

	}


}