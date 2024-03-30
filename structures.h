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
		ERROR
		
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

//queueueueu
typedef struct qNode {
	Token value;
	struct qNode* next;
} qNode;
typedef struct {
	qNode* front, * rear;
} Queue;








