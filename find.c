#include "find.h"
#include "array2i.h"

static enum {INIT,START,END,DONE};
vector2i currentPos,lastPos;
static int isInArray = 0, i = 0;
array2i path;
static int state = INIT;

int find(char* Tab, int Width, int Height){
	switch (state) {
	case INIT:
		arrayInit(&path);
		for (i = 0; i < Width; i++) {
			if (*(Tab + i + (Height - 1) * Width) == 'X') {
				lastPos.x = i;
				lastPos.y = Height - 1;
				currentPos.x = i;
				currentPos.y = Height - 2;
				state = START;
				arrayAddElement(&path, currentPos.x, currentPos.y);
				break;
			}
		}
		break;
	case START:
		if (lastPos.y < currentPos.y) {
			if (*(Tab + (currentPos.x - 1) + currentPos.y * Width) == ' ') {
				lastPos = currentPos;
				currentPos.x--;
			}
			else if (*(Tab + currentPos.x + (currentPos.y + 1) * Width) == ' ') {
				lastPos = currentPos;
				currentPos.y++;
			}
			else if (*(Tab + (currentPos.x + 1) + currentPos.y * Width) == ' ') {
				lastPos = currentPos;
				currentPos.x++;
			}
			else {
				vector2i temp;
				temp = currentPos;
				currentPos = lastPos;
				lastPos = temp;
			}
		}
		else if (lastPos.y > currentPos.y) {
			if (*(Tab + (currentPos.x + 1) + currentPos.y * Width) == ' ') {
				lastPos = currentPos;
				currentPos.x++;
			}
			else if (*(Tab + currentPos.x + (currentPos.y - 1) * Width) == ' ') {
				lastPos = currentPos;
				currentPos.y--;
			}
			else if (*(Tab + (currentPos.x - 1) + currentPos.y * Width) == ' ') {
				lastPos = currentPos;
				currentPos.x--;
			}
			else {
				vector2i temp;
				temp = currentPos;
				currentPos = lastPos;
				lastPos = temp;
			}
		}
		else if (lastPos.x > currentPos.x) {
			if (*(Tab + currentPos.x + (currentPos.y - 1) * Width) == ' ') {
				lastPos = currentPos;
				currentPos.y--;
			}
			else if (*(Tab + (currentPos.x - 1) + currentPos.y * Width) == ' ') {
				lastPos = currentPos;
				currentPos.x--;
			}
			else if (*(Tab + currentPos.x + (currentPos.y + 1) * Width) == ' ') {
				lastPos = currentPos;
				currentPos.y++;
			}
			else {
				vector2i temp;
				temp = currentPos;
				currentPos = lastPos;
				lastPos = temp;
			}
		}
		else if (lastPos.x < currentPos.x) {
			if (*(Tab + currentPos.x + (currentPos.y + 1) * Width) == ' ') {
				lastPos = currentPos;
				currentPos.y++;
			}
			else if (*(Tab + (currentPos.x + 1) + currentPos.y * Width) == ' ') {
				lastPos = currentPos;
				currentPos.x++;
			}
			else if (*(Tab + currentPos.x + (currentPos.y - 1) * Width) == ' ') {
				lastPos = currentPos;
				currentPos.y--;
			}
			else {
				vector2i temp;
				temp = currentPos;
				currentPos = lastPos;
				lastPos = temp;
			}
		}

		*(Tab + currentPos.x + currentPos.y * Width) = 'X';
		*(Tab + lastPos.x + lastPos.y * Width) = ' ';
		isInArray = 0;
		for (int i = 0; i < path.counter; i++) {
			if (path.vector[i].x == currentPos.x && path.vector[i].y == currentPos.y) {
				isInArray = 1;
				break;
			}

		}
		if (isInArray) {
			arrayRemoveElement(&path);
		}
		else {
			arrayAddElement(&path, currentPos.x, currentPos.y);
		}
		if (currentPos.y == 0) {
			state = END;
		}
		break;
	case END:
		for (i = 0; i < path.counter; i++) {
			*(Tab + path.vector[i].x + path.vector[i].y * Width) = 'X';
		}
		state = DONE;
		break;
	case DONE:
		return 1;
		break;
	}
	return 0;
}