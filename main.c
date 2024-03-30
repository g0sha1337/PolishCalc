#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <math.h>

#include "structures.h"


char WhitelistChar[] = " 1234567890+-^!qwertyuiopasdfghjklzxcvbnm.,";



int contain(char x, char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == x) return 1;
    }
    return 0;
}


void ClearLine(char* equasion) {
    char trimmed[1000] = { '\0' };
    int trimIndex = 0;
    for (int i = 0; equasion[i] != '\0'; i++) { //clear from spaces and tabs
        if (equasion[i] != ' ' && equasion[i] != '\t')
            trimmed[trimIndex++] = equasion[i];
    }
    strcpy(equasion, trimmed);
    for (int i = 0; i < strlen(equasion); i++) {
        if (equasion[i] == ',') equasion[i] = '.';
    }
}
double convertStringToDouble(const char* str) {
    return strtod(str, NULL);
}
void ClearCharArray(char* arr) {
    int len = strlen(arr);
    for (int i = 0; i < len; i++) {
        arr[i] = '\0';
    }
}
void ClearToken(Token* token) {
    token->data = '\0';
    token->type = NONE;
    token->value = 0.00;
    token->func = NONE;
}
void tokenizer(char* str,Token* array) {
    Token temp;
    ClearToken(&temp);

    char MathFunctins[32][16] = {
        "sin", "cos", "tg", "ctg", "arcsin", "arccos","arctg","arcctg","sqrt"
    };
    //Token array[1024] = { "\0" }; //array with our tokens (cringe)
    int ArrayPositionRN = 0;
    int counter = 0;
    int ParsingNumberRN = 0;
    int ParsingFunctionRN = 0;
    char TempCharLine[256] = { '\0' }; // bringing number in char array, for ex 3.14159265
    for (int i = 0; i <= strlen(str); i++) { //<= because we need to parse \0 to add determine token

        if (ParsingFunctionRN) {
            if (isalpha(str[i])) {
                TempCharLine[counter] = str[i];
                counter++;
                continue;
            }
            else {
                for (int i = 0; i < 10; i++) {
                    if (strcmp(TempCharLine, MathFunctins[i]) == 0) {
                        temp.type = FUNCTION;
                        temp.func = i;
                        array[ArrayPositionRN] = temp;
                        ArrayPositionRN++;
                        ClearToken(&temp);
                        ClearCharArray(TempCharLine);
                        break;
                    }

                }
                if (TempCharLine[0] != '\0') { // if user entired some huynya
                    temp.type = ERROR;
                    temp.func = 8;
                    array[ArrayPositionRN] = temp;
                    ArrayPositionRN++;
                    ClearToken(&temp);
                    ClearCharArray(TempCharLine);
                }
                ParsingFunctionRN = 0;
                counter = 0;
            }
        }

        if (isdigit(str[i]) || str[i] == '.') {
            ParsingNumberRN = 1;
            TempCharLine[counter] = str[i];
            counter++;

        }
        else if (((!(isdigit(str[i]) || str[i] == '.')) && ParsingNumberRN == 1) && str[i] != '\0') {
            temp.type = VALUE;
            temp.value = convertStringToDouble(TempCharLine);
            array[ArrayPositionRN] = temp;
            ArrayPositionRN++;
            counter = 0;
            ClearCharArray(TempCharLine);
            ClearToken(&temp);
            ParsingNumberRN = 0; //turn flag that we are parsing rn some number off

        }
        if (str[i] == '\0') { // if we reaised end of the line
            if (ParsingNumberRN) {
                temp.type = VALUE;
                temp.value = convertStringToDouble(TempCharLine);
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                counter = 0;
                ClearCharArray(TempCharLine);
                ClearToken(&temp);
            }
            temp.type = END;
            array[ArrayPositionRN] = temp;
            break;
        }


        if (!ParsingNumberRN) { //If we not parsing some number right now we can parse other data
            if (isalpha(str[i])) {

                if (!(isalpha(str[i + 1]))) {
                    temp.type = VARIABLE;
                    temp.data = str[i];
                    array[ArrayPositionRN] = temp;
                    ArrayPositionRN++;
                    ClearToken(&temp);
                    continue;
                }
                ParsingFunctionRN = 1;
                TempCharLine[counter] = str[i];
                counter++;
                continue;

            }
            if (str[i] == '(') {
                temp.type = BRACKET_OPEN;
                temp.data = '(';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                temp.type = NONE;
                ClearToken(&temp);
            }
            else if (str[i] == ')') {
                temp.type = BRACKET_CLOSE;
                temp.data = ')';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '+') {
                temp.type = OPERAND;
                temp.data = '+';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '-') {
                temp.type = OPERAND;
                temp.data = '-';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '*') {
                temp.type = OPERAND;
                temp.data = '*';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '^') {
                temp.type = OPERAND;
                temp.data = '^';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '!') {
                temp.type = OPERAND;
                temp.data = '!';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '/') {
                temp.type = OPERAND;
                temp.data = '/';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
        }
    }
}
int CheckBrackets(Token* tokens, int length){ 
    Stack* stack = NewStack();

    for (int i = 0; i < length; i++) {
        if (tokens[i].type == BRACKET_OPEN) {
            push(stack, tokens[i]);
        }
        else if (tokens[i].type == BRACKET_CLOSE) {
            Token PopedToken = pop(stack);
            if (PopedToken.type != BRACKET_OPEN) {
                return 0;
            }
        }
    }
    if (stack->start == NULL) {
        return 1;
    }
    else {
        return 0;
    }
};


//int PriorityDefiner(Token token) {
//    return 0;
//
//}


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
            printf("Type: END, Data: %c", tokens[i].data);
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
void main() {
    
    char InputLine[100] = { '\0' };
    printf("........................................................................................................................\n\nEnter equasion to count: ");
    scanf("%99[^\n]", InputLine);
    
    ClearLine(InputLine);
    int length = strlen(InputLine);
    length++;
    Token* tokens = (Token*)malloc(length * sizeof(Token)); //the number of tokens cannot exceed the length of the string
    //check correct expression
    tokenizer(InputLine, tokens);
    if (CheckBrackets(tokens, length)) {
        printf("Everything OK");
               
        
            
        
        
        
    }
    else {
        printf("Incorrect equasion");

    }
    printTokens(tokens, length);
    
    free(tokens);
}
