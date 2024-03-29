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
    token->data = '\0';
    token->type = NONE;
    token->value = 0.00;
}
void tokenizer(char* str,Token* array) {
    Token temp;
    ClearToken(&temp);
    //Token array[1024] = { "\0" }; //array with our tokens
    int ArrayPositionRN = 0;
    int counter = 0;
    int ParsingNumberRN = 0;
    char TempCharLine[256] = { '\0' }; // number in char array, for ex 3.14159265
    for (int i = 0; i < strlen(str) + 1; i++) {
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
        if (!ParsingNumberRN) { //åñëè ìû íå ïàðñèì ÷èñëî ïðÿìî ñåé÷àñ íà 
            if (str[i] == '(') {
                temp.type = BRACKET_OPEN;
                array[ArrayPositionRN] = temp;
                ArrayPositionRN++;
                temp.type = NONE;
                ClearToken(&temp);
            }
            else if (str[i] == ')') {
                temp.type = BRACKET_CLOSE;
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
        }
        // ÄÎÏÈÑÀÒÜ ÒÐÈÃÎÍÎÌÅÒÐÈÞ È ÏÐÎ×ÞÓ ÕÓÉÍÞ!!!

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
            printf("Type: VARIABLE, Data: %c", tokens[i].data);
            break;
        case OPERAND:
            printf("Type: OPERAND, Data: %c", tokens[i].data);
            break;
        case FUNCTION:
            printf("Type: FUNCTION, Data: %c", tokens[i].data);
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
    scanf("%99[^\n]", InputLine);
    Token tokens[2048];
    ClearLine(InputLine);
    //check correct expression
    if (/*CheckValid(InputLine)*/1) { //ÄÎÏÈÑÀÒÜ ×ÅÊÅÐ ÂÑÅ ËÈ ÕÎÐÎØÎ Â ÏËÀÍÅ ÑÊÎÁÎÊ!!!!!!!!
              
               
        tokenizer(InputLine, tokens);
            
        
        
        
    }
    else {
        printf("Incorrect ");

    }
    printTokens(tokens, 10);
    
    
}
