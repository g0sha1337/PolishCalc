#pragma once
Queue* ConvertToPolishs(Token* tokens, int size);
double calculate(Queue* que);
int PriorityDefiner(Token token);
Token FunctionCalculate(Token func, Token val);
int factorial(int n);
Token OperatorCalculation(Token val1, Token val2, Token oper);
int VariableFinder(Token* array);
int GetIndexLetter(char letter);

void DefineNewVariable(Token* array);
int IsPreviouslyKnownVariable(Token token);