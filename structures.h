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
	
	char data[16];
	double value;
	
} Token;


typedef struct {
	Token token;
	void* next;
	void* prev;
} Node;

typedef struct {
    Node* top;
} Stack;

//queueueueu
typedef struct qNode {
	Token value;
	struct qNode* next;
} qNode;
typedef struct {
	qNode* front, * rear;
} Queue;








