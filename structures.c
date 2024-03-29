#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

//stack
void initStack(Stack* stack) {
    stack->top = NULL;
}
int isEmptyStack(const Stack* s) {
    return s->top == NULL;
}
void push(Stack* stack, Token value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->token = value;
    newNode->next = stack->top;
    stack->top = newNode;
}
Token pop(Stack* s) {
    if (isEmptyStack(s)) {
        fprintf(stderr, "Stack is empty, cannot pop!n");
        exit(EXIT_FAILURE);
    }
    Node* temp = s->top;
    Token poppedValue = temp->token;
    s->top = temp->next;
    free(temp);
    return poppedValue;
}
Token peek(const Stack* s) {
    if (isEmptyStack(s)) {
        fprintf(stderr, "Stack is empty, cannot peek!n");
        exit(EXIT_FAILURE);
    }
    return s->top->token;
}
//queue
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
        fprintf(stderr, "Queue is empty, cannot dequeue!n");
        exit(EXIT_FAILURE);
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





