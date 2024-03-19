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
	const char* BIG_TEXT = ""
		" ____                                         ____                 ___               __  __       ___     \n"
		"/\\  _`\\                                      /\\  _`\\              /\\_ \\             /\\ \\/\\ \\    /'___`\\   \n"
		"\\ \\,\\L\\_\\    __  __   _____      __    _ __  \\ \\ \\/\\_\\     __     \\//\\ \\      ___   \\ \\ \\ \\ \\  /\\_\\ /\\ \\  \n"
		" \\/_\\__ \\   /\\ \\/\\ \\ /\\ '__`\\  /'__`\\ /\\`'__\\ \\ \\ \\/_/_  /'__`\\     \\ \\ \\    /'___\\  \\ \\ \\ \\ \\ \\/_/// /__ \n"
		"   /\\ \\L\\ \\ \\ \\ \\_\\ \\\\ \\ \\L\\ \\/\\  __/ \\ \\ \\/   \\ \\ \\L\\ \\/\\ \\L\\.\\_    \\_\\ \\_ /\\ \\__/   \\ \\ \\_/ \\   // /_\\ \\\n"
		"   \\ `\\____\\ \\ \\____/ \\ \\ ,__/\\ \\____\\ \\ \\_\\    \\ \\____/\\ \\__/.\\_\\   /\\____\\\\ \\____\\   \\ `\\___/  /\\______/\n"
		"    \\/_____/  \\/___/   \\ \\ \\/  \\/____/  \\/_/     \\/___/  \\/__/\\/_/   \\/____/ \\/____/    `\\/__/   \\/_____/ \n"
		"                        \\ \\_\\                                                                             \n"
		"                         \\/_/                                                                             \n";
	printf(BIG_TEXT);
	printf("Enter some line to count \n");
	


		
	char InputLine[1024] = { '\0' };
	fscanf("%s", InputLine);
	char ClearLine[1024] = { '\0' };


	for (int i = 0; InputLine[i] != '\0'; i++) {
		if (InputLine[i] != ' ' || InputLine[i] != '\t') add(ClearLine, InputLine[i]); //clear line from tabs and spaces 
	}






}