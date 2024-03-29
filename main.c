#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    for (int i =0;i<16;i++) token->data[i] = '\0';
    token->type = NONE;
    token->value = 0.00;
}
void tokenizer(char* str,Token* array) {
    Token temp;
    ClearToken(&temp);

    char MathFunctins[32][32] = {
        "sin", "cos", "tg", "ctg", "arcsin", "arccos"
    };
    //Token array[1024] = { "\0" }; //array with our tokens
    int ArrayPositionRN = 0;
    int counter = 0;
    int ParsingNumberRN = 0;
    int ParsingFunctionRN = 0;
    char TempCharLine[256] = { '\0' }; // number in char array, for ex 3.14159265
    for (int i = 0; i < strlen(str) + 1; i++) {

        if (ParsingFunctionRN) {
            if (isalpha(str[i])) {
                TempCharLine[counter] = str[i];
                counter++;
                continue;
            }
            else {
                for (int i = 0; i < 7; i++) {
                    if (strcmp(TempCharLine, MathFunctins[i])) {
                        temp.type = FUNCTION;
                        strcpy(temp.data, TempCharLine);
                        array[ArrayPositionRN] = temp;
                        ArrayPositionRN++;
                        ClearToken(&temp);
                        ClearCharArray(TempCharLine);
                        break;
                    }

                }
                if (TempCharLine[0] != '\0') { // if user entired some huynya
                    temp.type = ERROR;
                    strcpy(temp.data, TempCharLine);
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
        else if (((!(isdigit(str[i]) || str[i] == '.')) && ParsingNumberRN == 1) || str[i] == '\0') {
            temp.type = VALUE;
            temp.value = convertStringToDouble(TempCharLine);
            array[ArrayPositionRN] = temp;
            ArrayPositionRN++;
            counter = 0;
            ClearCharArray(TempCharLine);
            ClearToken(&temp);
            ParsingNumberRN = 0; //turn flag that we are parsing rn some number off
            
        } 
        
        
        if (!ParsingNumberRN) { //���� �� �� ������ ����� ����� ������ �� 
            if (isalpha(str[i])) {

                if (!(isalpha(str[i + 1]))) {
                    temp.type = VARIABLE;
                    temp.data[0] = str[i];
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
                temp.data[0] = '(';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                temp.type = NONE;
                ClearToken(&temp);
            }
            else if (str[i] == ')') {
                temp.type = BRACKET_CLOSE;
                temp.data[0] = ')';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '+') {
                temp.type = OPERAND;
                temp.data[0] = '+';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '-') {
                temp.type = OPERAND;
                temp.data[0] = '-';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '*') {
                temp.type = OPERAND;
                temp.data[0] = '*';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '^') {
                temp.type = OPERAND;
                temp.data[0] = '^';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            }
            else if (str[i] == '!') {
                temp.type = OPERAND;
                temp.data[0] = '!';
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                ClearToken(&temp);
            } 
            



        }

        // �������� ������������� � ������ �����!!!

    }

}
//int CheckValid(char* InputLine) {
//
//};

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
            printf("Type: VARIABLE, Data: %s", tokens[i].data);
            break;
        case OPERAND:
            printf("Type: OPERAND, Data: %s", tokens[i].data);
            break;
        case FUNCTION:
            printf("Type: FUNCTION, Data: %s", tokens[i].data);
            break;
        case BRACKET_OPEN:
            printf("Type: BRACKET_OPEN, Data: %s", tokens[i].data);
            break;
        case BRACKET_CLOSE:
            printf("Type: BRACKET_CLOSE, Data: %s", tokens[i].data);
            break;
        case ERROR:
            printf("Type: ERROR");
            break;
        }
    }
}
void main() {
    
    char InputLine[100] = { '\0' };
    scanf("%99[^\n]", InputLine);
    Token tokens[2048];
    ClearLine(InputLine);
    //check correct expression
    if (/*CheckValid(InputLine)*/1) { //�������� ����� ��� �� ������ � ����� ������!!!!!!!!
              
               
        tokenizer(InputLine, tokens);
            
        
        
        
    }
    else {
        printf("Incorrect ");

    }
    printTokens(tokens, 10);
    
    
}
