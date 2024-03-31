#include <stdio.h>
#include <stdlib.h>


#include "structures.h"
#include "calculator.h"

int PriorityDefiner(Token token) { //def
	
	// write prioritizer hehehe

	return 0;
}
void ClearSomeToken(Token* token) {
	token->data = '\0';
	token->type = NONE;
	token->value = 0.00;
	token->func = NONE;
}

Queue* ConverterToPolishs(Token* tokens) { //MANY BAGS!!! FIXXX THEM TOMORROW
	Queue* PolishTokens = NewQueue();
	initQueue(PolishTokens);


	int i = 0;
	Stack* stack = NewStack();
	initStack(stack);
	Queue* que = NewQueue();
	initQueue(que);

	int BracketFlag = 0;
	Token temp;
	while (tokens[i].type != END) { // semestr.online/informatics/polish.php
		if (tokens[i].type == OPERAND && tokens[i].data == '!') {
			enqueue(que, tokens[i]);
		} else if (tokens[i].type == FUNCTION) {
			push(stack, tokens[i]);
		} else if (tokens[i].type == BRACKET_OPEN) {
			BracketFlag = 1;
			push(stack, tokens[i]);
		}
		else if (tokens[i].type == OPERAND) {
			push(stack, tokens[i]);
		}
		else if (tokens[i].type == BRACKET_CLOSE) {
			while (peek(stack).type != BRACKET_OPEN) {
				
				temp = pop(stack);
				enqueue(que, temp);

			}
			if (tokens[i].type == BRACKET_CLOSE) pop(stack);

		}
		else {
			enqueue(que, tokens[i]);
		}
		
		ClearSomeToken(&temp);

		i++;
	}
	while (stack->start!=NULL) { // while empty stack
		Token temp;
		temp = pop(stack);
		enqueue(que, temp);
		ClearSomeToken(&temp);
	}
	return que;

}