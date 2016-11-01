// c-labyrinth
// coded by Xellor
#include <stdio.h>
#include <stdlib.h>

void printArray(int **array, int size_x, int size_y);
void checkLabyrinth(int **array, int size_x, int size_y);
void mark(int **array, int size_x, int size_y, int n, int pos_x, int pos_y);
void wave(int **array, int size_x, int size_y);

int main()
{
	unsigned size_x  = 5,			// size labyrinth array 
			 size_y  = 5,
			 enter_x = 0,			// enter position
			 enter_y = 1,
			 exit_x  = 3,			// exit position
			 exit_y  = 0;

	int labyrinth[5][5] =			// labyrinth array
			{{0, -1, 0, 0, 0},
			 {0,  1, 1, 1, 0},
			 {0,  1, 0, 1, 0},
			 {-2, 1, 1, 1, 0},
			 {0,  0, 0, 0, 0}};

	printArray((int**)labyrinth, size_x, size_y);
	wave((int**)labyrinth, size_x, size_y);
	printArray((int**)labyrinth, size_x, size_y);
	return 0;
}
void printArray(int **array, int size_x, int size_y)
{
	int *p_array = (int*)array;
	for(int i = 0; i < size_x; i++) {
		for(int j = 0; j < size_y; j++)
			printf("%3d", p_array[i * size_x + j]);
		printf("\n");
	}
}
void checkLabyrinth(int **array, int size_x, int size_y)
{
	int *p_array = (int*)array;
	int numEnter = 0,
		numExit  = 0;
	for(int i = 0; i < size_x; i++) {
		for(int j = 0; j < size_y; j++) {
			if(p_array[i * size_x + j] == -1)
				numEnter++;
			if(p_array[i * size_x + j] == -2)
				numExit++;
		}
	}
	if(numEnter == 1 and numExit == 1)
		printf("Check is [OK]\n");
	else {
		printf("Check is [ERROR]\nEnters = %d\nExits = %d\n", numEnter, numExit);
		exit(1);
	}
}
void mark(int **array, int size_x, int size_y, int n, int pos_x, int pos_y)	// marks adjacent sections
{																			// 'pos_x' and 'pos_y' flag 'n'
	int *p_array = (int*)array;
	if(p_array[pos_x * size_x + pos_y + 1] == 1)
		p_array[pos_x * size_x + pos_y + 1] = n;
	if(p_array[pos_x * size_x + pos_y - 1] == 1)
		p_array[pos_x * size_x + pos_y - 1] = n;
	if(p_array[(pos_x + 1) * size_x + pos_y] == 1)
		p_array[(pos_x + 1) * size_x + pos_y] = n;
	if(p_array[(pos_x - 1) * size_x + pos_y] == 1)
		p_array[(pos_x - 1) * size_x + pos_y] = n;
}
void wave(int **array, int size_x, int size_y)
{
	checkLabyrinth((int**)array, size_x, size_y);
	int *p_array = (int*)array;
	int n = 2, z = 0, i, j;
	
	for(i = 0; i < size_x; i++) {
		for(j = 0; j < size_y; j++) {
			if(p_array[i * size_x + j] == -1) {
				mark((int**)array, size_x, size_y, n, i, j);
				n++;
				break;
			}
		}
	}
	do {
		for(i = 0; i < size_x; i++) {
			for(j = 0; j < size_y; j++) {
				if(p_array[i * size_x + j] == n - 1)
					mark((int**)array, size_x, size_y, n, i, j);
			}
		}
		n++;
		z++;
	} while (z < size_y - 1);
}