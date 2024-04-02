#include <stdio.h>
#include <stdlib.h>
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

void ClearSomeToken(Token* token) {
	token->data = '\0';
	token->type = NONE;
	token->value = 0.00;
	token->func = NONE;
}

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

		i++;
	}

	while (stack->start != NULL) { // while empty stack
		enqueue(que, pop(stack));
	}
	return que;

}