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
    if (isEmptyStack(s)) {
        perror("Stack is empty, cannot pop!n");
        exit(EXIT_FAILURE);
    }
    Node* temp = s->start;
    Token poppedValue = temp->token;
    s->start = temp->next;
    free(temp);
    return poppedValue;
}
Token peek(const Stack* s) {
    if (isEmptyStack(s)) {
        perror("Stack is empty, cannot peek!n");
        exit(EXIT_FAILURE);
    }
    return s->start->token;
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
        perror("Queue is empty, cannot dequeue!n");
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





