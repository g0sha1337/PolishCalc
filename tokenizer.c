#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "tokenizer.h"

void ClearLine(char* equasion) {
    char trimmed[1000] = { '\0' };
    int trimIndex = 0;
    for (int i = 0; equasion[i] != '\0'; i++) { //clear from spaces and tabs
        if (equasion[i] != ' ' && equasion[i] != '\t')
            trimmed[trimIndex++] = equasion[i];
    }
    strcpy(equasion, trimmed);
    for (int i = 0; i < strlen(equasion); i++) { //swap , to . and Upper to Lowers 
        if (equasion[i] == ',') equasion[i] = '.';
        if (equasion[i] >= 'A' && equasion[i] <= 'Z') equasion[i] = equasion[i] + 32;
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


Token* tokenizer(char* str, int size) {
    Token* array = (Token*)malloc(size*2 * sizeof(Token));
    if (array == NULL) {
        printf("\nKURWA HEAP KURWA!!1!\n");
        exit(EXIT_FAILURE);
    }
    Token temp;
    ClearToken(&temp);
    char MathFunctins[32][16] = {
        "sin", "cos", "tg", "ctg", "arcsin", "arccos","arctg","arcctg","sqrt"
    };
    char _pi[] = "pi";
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
                if (strcmp(_pi, TempCharLine)==0) {
                    temp.type = VALUE;
                    temp.value = 3.14159265;
                    array[ArrayPositionRN] = temp;
                    ArrayPositionRN++;
                    ClearToken(&temp);
                    ClearCharArray(TempCharLine);

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

                }
                

                
                if (TempCharLine[0] != '\0') { // if user entired some huynya
                    temp.type = __ERROR;
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
                if (i == 0) {
                    temp.type = VALUE;
                    temp.value = 0;
                    array[ArrayPositionRN] = temp;
                    ArrayPositionRN++;
                    ClearToken(&temp);
                    temp.type = OPERAND;
                    temp.data = '-';
                    array[ArrayPositionRN] = temp;
                    ArrayPositionRN++;
                    ClearToken(&temp);

                }
                else if (isdigit(str[i - 1]) == 0 && str[i - 1] != ')') {
                    temp.type = VALUE;
                    temp.value = 0;
                    array[ArrayPositionRN] = temp;
                    ArrayPositionRN++;
                    ClearToken(&temp);
                    temp.type = OPERAND;
                    temp.data = '-';
                    array[ArrayPositionRN] = temp;
                    ArrayPositionRN++;
                    ClearToken(&temp);
                } else {
                    temp.type = OPERAND;
                    temp.data = '-';
                    array[ArrayPositionRN] = temp;
                    ArrayPositionRN++;
                    ClearToken(&temp);
                }
                
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
    return array;
}

int CheckTokenPositions(Token* tokens) { // avoid 2++ and some other incorrect input
    // sin ( 2 * ( 2 - 1 ) )
    int i = 0;
    while (tokens[i].type != END) {
        if ( //trying to find wrong token positions
            (tokens[i].type == FUNCTION && tokens[i + 1].type != BRACKET_OPEN) || //  if sqrt2 or sinx instead of sqrt(2) and sin(x)
            (tokens[i].type == tokens[i+1].type && (!((tokens[i].type == BRACKET_CLOSE && tokens[i+1].type == BRACKET_CLOSE) ||(tokens[i].type == BRACKET_OPEN && tokens[i+1].type == BRACKET_OPEN)))) ||// if *+ or +- (exception with )( )
            (tokens[i].type == __ERROR)
            ) return 0;
        i++;
    }
    return 1; // everything good
}

void flush_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
