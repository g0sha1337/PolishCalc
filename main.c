#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <math.h>

#include "structures.h"
#include "tokenizer.h"
#include "calculator.h"

char WhitelistChar[] = " 1234567890+-^*!/()abcdefghijklmnopqrstuvwxyz.,";

int contain(char x, char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == x) return 1;
    }
    return 0;
}

int CheckBrackets(Token* tokens, int length) {
    Stack* stack = NewStack();
    for (int i = 0; i < length; i++) {
        if (tokens[i].type == BRACKET_OPEN) {
            push(stack, tokens[i]);
        }
        else if (tokens[i].type == BRACKET_CLOSE) {
            if (isEmptyStack(stack)) {
                // Closing bracket without a corresponding opening bracket
                return 0;
            }
            Token PopedToken = pop(stack);
            if (PopedToken.type != BRACKET_OPEN) {
                // Mismatch of bracket types
                return 0;
            }
        }
    }
    if (isEmptyStack(stack)) {
        return 1; //  brackets are balanced
    }
    else {
        return 0; // Unpaired opening brackets remain
    }
}

int CheckInput(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!(contain(str[i], WhitelistChar))) return 0;
    }
    return 1;
}
void printTokens(Token* tokens, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("\nToken %zu: ", i);
        switch (tokens[i].type) {
        case NONE:
            printf("Type: NONE");
            break;
        case VALUE:
            printf("Type: VALUE, Value: %f", tokens[i].value);
            break;
        case VARIABLE:
            printf("Type: VARIABLE, Data: %c", tokens[i].data);
            break;
        case OPERAND:
            printf("Type: OPERAND, Data: %c", tokens[i].data);
            break;
        case END:
            printf("Type: END");
            break;
        case FUNCTION:
            printf("Type: FUNCTION, Data: %c, Function type: ", tokens[i].data);
            switch (tokens[i].func) {
            case __sin:
                printf("sin");
                break;
            case __cos:
                printf("cos");
                break;
            case __tg:
                printf("tg");
                break;
            case __ctg:
                printf("ctg");
                break;
            case __arcsin:
                printf("arcsin");
                break;
            case __arccos:
                printf("arccos");
                break;
            case __arctg:
                printf("arctg");
                break;
            case __arcctg:
                printf("arcctg");
                break;
            case __sqrt:
                printf("sqrt");
                break;
            case __NONE:
                printf("none");
                break;
            }
            break;
        case BRACKET_OPEN:
            printf("Type: BRACKET_OPEN, Data: %c", tokens[i].data);
            break;
        case BRACKET_CLOSE:
            printf("Type: BRACKET_CLOSE, Data: %c", tokens[i].data);
            break;
        case ERROR:
            printf("Type: ERROR");
            break;
        }
    }
}
void PrintToken(Token token) {

    switch (token.type) {
    case NONE:
        printf(" :NONE:");
        break;
    case VALUE:
        printf("%.0f ", token.value);
        break;
    case VARIABLE:
        printf("%c ", token.data);
        break;
    case OPERAND:
        printf("%c ", token.data);
        break;
    case END:
        printf(":END:");
        break;
    case FUNCTION:
        //printf("Type: FUNCTION, Data: %c, Function type: ", token.data);
        switch (token.func) {
        case __sin:
            printf("sin ");
            break;
        case __cos:
            printf("cos ");
            break;
        case __tg:
            printf("tg ");
            break;
        case __ctg:
            printf("ctg ");
            break;
        case __arcsin:
            printf("arcsin ");
            break;
        case __arccos:
            printf("arccos ");
            break;
        case __arctg:
            printf("arctg ");
            break;
        case __arcctg:
            printf("arcctg ");
            break;
        case __sqrt:
            printf("sqrt ");
            break;
        case __NONE:
            printf("none ");
            break;
        }
        break;
    case BRACKET_OPEN:
        printf("Type: BRACKET_OPEN, Data: %c", token.data);
        break;
    case BRACKET_CLOSE:
        printf("Type: BRACKET_CLOSE, Data: %c", token.data);
        break;
    case ERROR:
        printf("Type: ERROR");
        break;
    }
}
int main() {
    
    char InputLine[100] = { '\0' };
    printf("........................................................................................................................\n\nEnter equasion to count: ");
    scanf("%99[^\n]", InputLine);
    
    ClearLine(InputLine);
    int length = strlen(InputLine);
    length++;
    Token* tokens = tokenizer(InputLine, length);
    // printTokens(tokens, length);
    //Token* tokens = (Token*)malloc(length * sizeof(Token)); //the number of tokens cannot exceed the length of the string
    //check correct expression
    
    /*if (!(CheckBrackets(tokens, length))) printf("\nCheckBrackets FAIL\n");
    if (!(CheckInput(InputLine))) printf("\nCheckInput FAIL\n");
    if (!(CheckTokenPositions(tokens))) printf("\nCheckTokenPositions FAIL\n");*/

    if (CheckBrackets(tokens, length) && CheckInput(InputLine) && CheckTokenPositions(tokens)) { //works only if input was corrects
        printf("\nEverything OK\n");

        Queue* PolishTokens = ConvertToPolishs(tokens,length);
        
        
        printf("\nPOLISH TOKENS: ");
        for (int i = 0; i < length-1; i++) {    
            /*printf("\ntoken-%d: ", i);*/
            PrintToken(dequeue(PolishTokens));

        }
            
        
        printf("\n\n");
        free(PolishTokens);
    }
    else {
        printf("Incorrect equasion");

    }
    //printTokens(tokens, length);
    
    free(tokens);
    
    return 0;
}



