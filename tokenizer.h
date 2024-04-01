#pragma once
void ClearLine(char* equasion);
double convertStringToDouble(const char* str);
void ClearCharArray(char* arr);
Token* tokenizer(char* str, int size);
int CheckTokenPositions(Token* tokens);
void ClearToken(Token* token);