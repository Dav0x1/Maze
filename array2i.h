#ifndef ARRAY2I
#define ARRAY2I
typedef struct vector2i {
	int x;
	int y;
}vector2i;

typedef struct array2i{
	vector2i* vector;
	int size;
	int counter;
}array2i;

void arrayInit(array2i* Array);
void arrayAddElement(array2i * Array,int x,int y);
void arrayRemoveElement(array2i* Array);
void arrayDelete(array2i* Array);
#endif
