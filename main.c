#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
char WhitelistChar[] = " 1234567890+-^!qwertyuiopasdfghjklzxcvbnm.,";



// Structs

typedef struct {
    Node* top;
} Stack;

void initStack(Stack* stack) {
    stack->top = NULL;
}
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}



typedef struct {
    enum Type {
        VALUE,
        VARIABLE,
        OPERAND,
        FUNCTION,
        BRACKET_OPEN,
        BRACKET_CLOSE,
        NONE,
        ERROR
    } type;
    union {
        char data[5];
        double value;
        enum Type {
            NONE, sin, cos, tg,ctg,arctg,arcctg,ln,sqrt
        } func;
    };
} Token;

typedef struct {
    Token token;
    void* next;
    void* prev;
} Node;

typedef struct {
    Node* start;
} Queue;

Queue* NewQueue() { //кьюью
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->start = NULL;
    return queue;
}
Stack* NewStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;

}

int contain(char x, char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == x) return 1;
    }
    return 0;
}

int CheckValid(char* str) {
    int flag = 1;
    for (int i = 0; i < strlen(str); i++) {
        if (contain(str[i], WhitelistChar) == 0) return 0;
    }
    Stack stack;
    initStack(&stack);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            push(&stack, str[i]);
        }
        else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (isEmpty(&stack)) {
                return 0; // Незакрытая скобка
            }
            char topChar = pop(&stack);
            if ((str[i] == ')' && topChar != '(') ||
                (str[i] == '}' && topChar != '{') ||
                (str[i] == ']' && topChar != '[')) {
                return 0;
            }
        }
    }
    if (!isEmpty(&stack)) {
        return 0;
    }

    return 1; // Все скобки закрыты правильно
}
void ClearLine(char* equasion) {
    char trimmed[1000] = { '\0' };
    int trimIndex = 0;
    for (int i = 0; equasion[i] != '\0'; i++) { //clear from spaces and tabs
        if (equasion[i] != ' ' && equasion[i] != '\t')
            trimmed[trimIndex++] = equasion[i];
        if (equasion[i] == ',') { // peplace all , to . 
            trimmed[trimIndex++] = '.';
        }
    }
    
    strcpy(equasion, trimmed);
}
double convertStringToDouble(const char* str) {
    return strtod(str, NULL);
}
void ClearCharArray(char* arr) {
    int len = strlen(arr);
    for (int i = 0; i < len; i) {
        arr[i] = '\0';
    }
}
void tokenizer(char* str,Token* array) {
    Queue* que = NewQueue();
    Stack* stack = NewStack();
    Token temp;
    //Token array[1024] = { "\0" }; //array with our tokens
    int ArrayPositionRN = 0;
    int counter = 0;
    int ParsingNumberRN = 0;
    char TempCharLine[256] = {'\0'}; // number in char array, for ex 3.14159265
    for (int i = 0; i < strlen(str); i++) {

        if (ifdigit(str[i]) || str[i] == '.') {
            ParsingNumberRN = 1;
            TempCharLine[counter] = str[i];
            counter++;

        }
        else if ((!(ifdigit(str[i]) || str[i] == '.')) && ParsingNumberRN == 1) {
            temp.type = VALUE;
            temp.value = convertStringToDouble(TempCharLine);
            array[ArrayPositionRN] = temp;
            ArrayPositionRN++;
            temp.type = NONE;
            ClearCharArray(TempCharLine);
            ParsingNumberRN = 0;


        } else if (str[i] == '(') {


            temp.type = BRACKET_OPEN;
            array[ArrayPositionRN] = temp;
            ArrayPositionRN++;
            temp.type = NONE;
        }
        else if (str[i] == ')') {
            temp.type = BRACKET_CLOSE;
            array[ArrayPositionRN] = temp;
            ArrayPositionRN++;
            temp.type = NONE;
        }
         
    }



}


int PriorityDefiner(Token token) {
    return 0;

}
void main() {
    char InputLine[100] = { '\0' };
    scanf("%99[^\n]", InputLine);
    //check correct expression
    if (CheckValid(InputLine)) {
        ClearLine(InputLine);
        printf("%s\nEVERYTHING OK\n",InputLine);
        Token tokens[512];
        tokenizer(InputLine, tokens);
        
        
        
        
    }
    else {
        printf("Incorrect ");

    }

    
    
}
