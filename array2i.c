#include "Array2i.h"
#include <stdlib.h>

#define INCREASE_VALUE 5

void arrayInit(array2i* Array) {

	if (Array) {
		Array->size = INCREASE_VALUE;
		Array->counter = 0;
		Array->vector = (vector2i*)malloc(INCREASE_VALUE*sizeof(vector2i));
	}
}

void arrayAddElement(array2i* Array, int x, int y) {
	if (Array) {
		// Initialization
		if(!Array->vector) arrayInit(Array);
		// Increase size
		if (Array->counter == Array->size) {
			int i;
			vector2i* temp;
			temp = Array->vector;
			
			Array->size += INCREASE_VALUE;
			Array->vector = (vector2i*)malloc(Array->size * sizeof(vector2i));
			for (i = 0; i < Array->size - INCREASE_VALUE; i++) {
				Array->vector[i] = temp[i];
			}
			Array->vector[Array->counter].x = x;
			Array->vector[Array->counter].y = y;
			Array->counter++;
			free(temp);
		}
		// Append element
		else {
			Array->vector[Array->counter].x = x;
			Array->vector[Array->counter].y = y;
			Array->counter++;
		}

	}
};

void arrayRemoveElement(array2i* Array) {
	if (Array != NULL && Array->vector != NULL) {
		Array->counter--;
		// Decrease size
		if (Array->size-Array->counter>= INCREASE_VALUE) {
			int i;
			vector2i* temp;
			temp = Array->vector;

			Array->size -= INCREASE_VALUE;
			Array->vector = (vector2i*)malloc(Array->size * sizeof(vector2i));
			for (i = 0; i < Array->counter; i++) {
				Array->vector[i] = temp[i];
			}
			free(temp);
		}
	}
}
void arrayDelete(array2i* Array) {
	if (Array != NULL && Array->vector != NULL) {
		free(Array->vector);
		Array->vector == NULL;
	}
}