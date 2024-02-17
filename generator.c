#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include "array2i.h"
#define WALL 219
#define HEAD 88

enum  direction { LEFT, RIGHT, UP, DOWN, NONE };
enum states {GEN_BORDER,GEN_PATH,END}state = GEN_BORDER;
int x = 0, y = 0, startPos = 0;
int repeatDirection[4] = {0,0,0,0};
int isTrue = 1,direction = NONE;
array2i moveSave,moveBack;

int checkPlace(int x, int y, int direction, array2i * Array) {
	for (int i = 0; i < Array->counter; i++) {
		if (direction == LEFT) {
			if ((Array->vector[i].x == x && Array->vector[i].y == y) ||
				(Array->vector[i].x == x && Array->vector[i].y == y - 1) || 
			    (Array->vector[i].x == x && Array->vector[i].y == y + 1) || 
			    (Array->vector[i].x == x-1 && Array->vector[i].y == y) ||
			    (Array->vector[i].x == x - 1 && Array->vector[i].y == y-1) || 
			    (Array->vector[i].x == x - 1 && Array->vector[i].y == y+1))
				return 0;
		}
		else if (direction == RIGHT) {
			if ((Array->vector[i].x == x && Array->vector[i].y == y) ||
				(Array->vector[i].x == x && Array->vector[i].y == y - 1) ||
				(Array->vector[i].x == x && Array->vector[i].y == y + 1) ||
				(Array->vector[i].x == x + 1 && Array->vector[i].y == y) ||
				(Array->vector[i].x == x + 1 && Array->vector[i].y == y-1) || 
				(Array->vector[i].x == x + 1 && Array->vector[i].y == y+1))
				return 0;
		}
		else if (direction == DOWN) {
			if ((Array->vector[i].x == x && Array->vector[i].y == y) ||
				(Array->vector[i].x == x && Array->vector[i].y == y + 1) ||
				(Array->vector[i].x == x - 1 && Array->vector[i].y == y + 1) ||
				(Array->vector[i].x == x + 1 && Array->vector[i].y == y + 1) ||
				(Array->vector[i].x == x - 1 && Array->vector[i].y == y) ||
				(Array->vector[i].x == x + 1 && Array->vector[i].y == y))
				return 0;
		}
		else if (direction == UP) {
			if ((Array->vector[i].x == x && Array->vector[i].y == y) ||
				(Array->vector[i].x == x && Array->vector[i].y == y - 1) ||
				(Array->vector[i].x == x - 1 && Array->vector[i].y == y - 1) ||
				(Array->vector[i].x == x + 1 && Array->vector[i].y == y - 1) ||
				(Array->vector[i].x == x - 1 && Array->vector[i].y == y) ||
				(Array->vector[i].x == x + 1 && Array->vector[i].y == y))
				return 0;
		}
	}
	return 1;
}

int generate(unsigned char* Tab, int Width, int Height) {
	if (!startPos) {
		startPos = (rand() % (Width - 2)) + 1;
		moveSave.vector = NULL;
		moveBack.vector = NULL;
	}
	switch (state){
	case GEN_BORDER:
		if (x<Width) {
			*(Tab + x) = WALL;
			*(Tab + (Width-1-x) + (Height-1)*Width) = WALL;
			x++;
		}
		if (y<Height) {
			*(Tab + y*Width) = WALL;
			*(Tab + Width-1 + (Height-y-1)*Width) = WALL;
			y++;
		}
		if (x >= Width && y >= Height) {
			state = GEN_PATH;
			x = startPos;
			y = Height-1;
			*(Tab + x + y*Width) = HEAD;
		}
		break;
	case GEN_PATH:
		while (isTrue) {
			direction = rand() % 4;
			*(Tab + x + y * Width) = ' ';
			if (repeatDirection[0] == 1 && repeatDirection[1] == 1 && repeatDirection[2] == 1 && repeatDirection[3] == 1) {
				arrayRemoveElement(&moveBack);
				if (moveBack.counter == 0) {
					state = END;
					*(Tab + x + y * Width) = ' ';
					x = startPos;
					y = Height - 1;
					break;
				}
				y = moveBack.vector[moveBack.counter - 1].y;
				x = moveBack.vector[moveBack.counter - 1].x;
				*(Tab + x + y * Width) = HEAD;
				repeatDirection[0] = 0; repeatDirection[1] = 0; repeatDirection[2] = 0; repeatDirection[3] = 0;
			}
			switch (direction)
			{
				case LEFT:
					repeatDirection[LEFT] = 1;
					if (x - 1 >= 1 && y!= Height-1 && y!=0 && checkPlace(x-1,y,LEFT,&moveSave)) {
						x--;
						*(Tab + x + (y-1) * Width) = WALL; *(Tab + x + (y+1) * Width) = WALL;
						*(Tab + x-1 + y * Width) = WALL; *(Tab + x-1 + (y+1) * Width) = WALL; *(Tab + x-1 + (y-1) * Width) = WALL;
						isTrue = 0;
					}
					break;
				case RIGHT:
					repeatDirection[RIGHT] = 1;
					if (x + 1 < Width - 1 && y != Height - 1 && y != 0 && checkPlace(x + 1, y, RIGHT, &moveSave)) {
						x++;
						*(Tab + x + (y-1) * Width) = WALL; *(Tab + x + (y+1) * Width) = WALL;
						*(Tab + x + 1 + y * Width) = WALL; *(Tab + x + 1 + (y + 1) * Width) = WALL; *(Tab + x + 1 + (y - 1) * Width) = WALL;
						isTrue = 0;
					}
					break;
				case UP:
					repeatDirection[UP] = 1;
					if (y - 1 >= 1 && x != Width - 1 && x != 0 && checkPlace(x , y-1, UP, &moveSave)) {
						y--;
						*(Tab + x-1 + y * Width) = WALL; *(Tab + x+1 + y * Width) = WALL;
						*(Tab + x + 1 + (y-1) * Width) = WALL; *(Tab + x - 1 + (y - 1) * Width) = WALL; *(Tab + x + (y - 1) * Width) = WALL;
						isTrue = 0;
					}
					break;
				case DOWN:
					repeatDirection[DOWN] = 1;
					if (y + 1 < Height-1 && x != Width - 1 && x != 0 && checkPlace(x, y+1, DOWN, &moveSave)) {
						y++;
						*(Tab + x-1 + y * Width) = WALL; *(Tab + x+1 + y * Width) = WALL;
						*(Tab + x + 1 + (y + 1) * Width) = WALL; *(Tab + x - 1 + (y + 1) * Width) = WALL; *(Tab + x + (y + 1) * Width) = WALL;
						isTrue = 0;
					}
					break;
			}
			
		}
		repeatDirection[0] = 0; repeatDirection[1] = 0; repeatDirection[2] = 0; repeatDirection[3] = 0;
		isTrue = 1;
		*(Tab + x + y * Width) = HEAD;
		arrayAddElement(&moveSave, x, y);
		arrayAddElement(&moveBack, x, y);
		break;
	case END:
		y = 1;
		do {
			x = rand() % Width-1;
		} while (*(Tab + x + y*Width)!=' ');
		y = 0;
		*(Tab + x + y * Width) = ' ';
		arrayDelete(&moveSave);
		arrayDelete(&moveBack);
		return 1;
		break;
	}
	return 0;
}