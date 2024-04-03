#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

//stack
void initStack(Stack* stack) {
    stack->start = NULL;
}

int isEmptyStack(const Stack* s) {
    return s->start == NULL;
}

Stack* NewStack() { //c
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->start = NULL;
    return s;
}

void push(Stack* stack, Token value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->token = value;
    newNode->next = stack->start;
    stack->start = newNode;
}

Token pop(Stack* s) {
    Token End;
    End.type = END;
    if (isEmptyStack(s)) {
        return End;
    }
    Node* temp = s->start;
    Token poppedValue = temp->token;
    s->start = temp->next;
    free(temp);
    return poppedValue;
}

Token peek(const Stack* s) {
    Token End;
    End.type = END;
    if (isEmptyStack(s)) {
        return End;
    }
    return s->start->token;
}


//queue
Queue* NewQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    return queue;
}

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

int isEmptyQueue(const Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, Token value) {
    qNode* newNode = (qNode*)malloc(sizeof(qNode));
    newNode->value = value;
    newNode->next = NULL;
    if (isEmptyQueue(q)) {
        q->front = q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Token dequeue(Queue* q) {
    if (isEmptyQueue(q)) {
        //printf("\n\nQueue is empty, cannot dequeue!n");
        Token token;
        ClearToken(&token);
        token.type == END;
        return token;
    }
    qNode* temp = q->front;
    Token dequeuedValue = temp->value;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return dequeuedValue;
}




void ClearToken(Token* token) {
    token->data = '\0';
    token->type = NONE;
    token->value = 0.00;
    token->func = NONE;
}