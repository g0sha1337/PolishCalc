#pragma once
//stack
typedef struct {
	enum Type {
		NONE,
		VALUE,
		VARIABLE,
		OPERAND,
		FUNCTION,
		BRACKET_OPEN,
		BRACKET_CLOSE,
		__ERROR, 
		END
	} type;

	enum Func {
		__sin,
		__cos,
		__tg,
		__ctg,
		__arcsin,
		__arccos,
		__arctg,
		__arcctg,
		__sqrt,
		__factorial,
		__pow,
		__NONE,
	} func;

	char data;

	double value;
	
} Token;

typedef struct {
	Token token;
	void* next;
	void* prev;
} Node;

typedef struct {
    Node* start;
} Stack;

//queue

typedef struct qNode {
	Token value;
	struct qNode* next; //link to next element queue
} qNode;

typedef struct {
	qNode* front; // pered
	qNode* rear; // zad
} Queue;

Token peek(const Stack* s);
Token pop(Stack* s);
void initStack(Stack* stack);
Stack* NewStack();
void push(Stack* stack, Token value);
void initQueue(Queue* q);
Queue* NewQueue();
int isEmptyQueue(const Queue* q);
void enqueue(Queue* q, Token value);
Token dequeue(Queue* q);
void ClearToken(Token* token);
