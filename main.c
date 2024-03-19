#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define MAX_LENGTH 1024

typedef struct {
	int top;
	char array[MAX_LENGTH];
} Stack;

void add(char* arr, char x) {
	int len = strlen(arr);
	arr[len] = x;
	arr[len + 1] = '\0';
}


void main() {
	printf("Enter some line to count \n");

	char InputLine[1024] = { '\0' };
	char ClearLine[1024] = { '\0' };

	fscanf_s("%[^\n]%*c", InputLine);

	for (int i = 0; InputLine[i] != '\0'; i++) {
		if (InputLine[i] != ' ' || InputLine[i] != '\t') add(ClearLine, InputLine[i]); //clear line from tabs and spaces 
	}






}