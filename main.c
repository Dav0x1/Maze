#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "generator.h"
#include "find.h"
#include "array2i.h"

#define TRUE 1
#define FALSE 0
#define WIDTH 200
#define HEIGHT 200
#define FILE_NAME "maze.txt" //LIMIT 20 CHAR

void displayMaze(unsigned char *Tab, int Width, int Height);
void saveToFile(unsigned char* Tab,int Width,int Height);
char* intToChar(int num);

unsigned char consoleOutput[WIDTH][HEIGHT];
int main() {
	int width = WIDTH, height = HEIGHT, delay = 0;
	int x, y;
	int isTrue = 1;
	enum {GENERATE,FIND};
	COORD cursorPos; cursorPos.X = 0; cursorPos.Y = 0;
	HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	int i=0,state = GENERATE;
	unsigned char* maze = NULL; // Array with maze

	srand(time(NULL));
	// Setting cursor parameters
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;

	SetConsoleCursorInfo(consoleOutput,&cursorInfo);
	SetConsoleTitleA("Maze");
	SetConsoleTextAttribute(consoleOutput,FOREGROUND_GREEN);

	printf("Type width and height:");
	scanf("%i %i", &width, &height);
	if (width<4) width = WIDTH;

	if (height<4) height = HEIGHT;

	printf("Type display delay in ms:");
	scanf("%i", &delay);
	if (delay < 0) delay = 0;
	// Initialization maze array
	maze = (unsigned char*)malloc(height*width*sizeof(unsigned char));
	for (i = 0; i<height * width; i++) {
		*(maze+i)=' ';
	}

	while (isTrue) {
		SetConsoleCursorPosition(consoleOutput, cursorPos);
		displayMaze(maze,width,height);
		switch (state){
		case GENERATE:
			if (generate(maze, width, height)) state = FIND;
			break;
		case FIND:
			if (find(maze, width, height)) isTrue = 0;
			break;
		}
		Sleep(delay);
	}

	saveToFile(maze,width,height);
	if(!consoleOutput)
		CloseHandle(consoleOutput);
	free(maze);

	printf("\nPress ENTER to close\n");
	getchar(); getchar();
	return 0;
}

void displayMaze(unsigned char *Tab, int Width, int Height) {
	int x,y;
	for (y = 0; y<Height; y++) {
		for (x = 0;x<Width;x++) {
			if (*(Tab + x + y * Width) != consoleOutput[x][y]) {
				printf("\x1b[%d;%df", y + 1, x + 1);
				printf("%c", *(Tab + x + y * Width));
				consoleOutput[x][y] = *(Tab + x + y * Width);
			}
		}
		printf("\n");
	}
}
void saveToFile(unsigned char* Tab, int Width, int Height){
	int i=0,j=0;
	FILE* file = NULL;
	
	char name[20] = FILE_NAME;

	file = fopen(name, "r");
	i = 2;
	if (file != NULL) {
		for (j = 0;j<strlen(name);j++) {
			if (name[j] == '.') break;
		}
	};

	while (file != NULL) {
		fclose(file);
		char *temp_num = intToChar(i);
		name[j] = '\0';
		strcat(name," (");
		strcat(name,temp_num);
		strcat(name, ").txt");
		free(temp_num);
		file = fopen(name, "r");
		i++;
	}

	file = fopen(name,"w");
	for (int i = 0;i<Height;i++) {
		for (int j = 0; j < Width; j++) {
			fputc(*(Tab+j+i*Width),file);
		}
		fputc('\n', file);
	}
	fclose(file);
};
char* intToChar(int num) {
	char* string = NULL;
	int length = 0,i=0,j=0;
	for (i = 1;num/i!=0;i*=10) {
		length++;
	}

	string = (char*)malloc((length+1)*sizeof(char));
	for (j = 0;j<length;j++) {
		i /= 10;
		string[j] = ((num/i)%10)+48;
	}
	string[length] = '\0';
	return string;
};