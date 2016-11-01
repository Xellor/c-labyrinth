// c-labyrinth
// Coded by Xellor
#include <stdio.h>
#include <stdlib.h>

void printTDArray(int **array, int size_x, int size_y);
void printCArray(char array[], int size);
void checkLabyrinth(int **array, int size_x, int size_y);
void mark(int **array, int size_x, int size_y, int n, int pos_x, int pos_y);
void wave(int **array, int *pN, int size_x, int size_y);
char shortest(int **array, int size_x, int size_y, int pos_x, int pos_y, int max_n);
void back(int **array, int size_x, int size_y, int max_n, char *way, int sizeWay);

int main()
{
	const unsigned size_x  = 5,			// size labyrinth array 
			 	   size_y  = 5;
	char way[size_x * size_y];			// way array
	int max_n;
	int labyrinth[size_x][size_y] =		// labyrinth array
			{{0, -1, 0, 0, 0},
			 {0,  1, 1, 1, 0},
			 {0,  1, 0, 1, 0},
			 {-2, 1, 1, 1, 0},
			 {0,  0, 0, 0, 0}};

	printf("Labyrinth:\n");
	printTDArray((int**)labyrinth, size_x, size_y);
	wave((int**)labyrinth, &max_n, size_x, size_y);
	printf("Labyrinth after wave:\n");
	printTDArray((int**)labyrinth, size_x, size_y);
	back((int**)labyrinth, size_x, size_y, max_n, way, (size_x * size_y));
	printCArray(way, (size_x * size_y));
	return 0;
}
void printTDArray(int **array, int size_x, int size_y)
{
	int *p_array = (int*)array;
	for(int i = 0; i < size_x; i++) {
		for(int j = 0; j < size_y; j++)
			printf("%3d", p_array[i * size_x + j]);
		printf("\n");
	}
}
void printCArray(char array[], int size)
{
	for(unsigned i = 0; i < size; i++)
		printf("%c ", array[i]);
	printf(";\n");
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
void wave(int **array, int *pN, int size_x, int size_y)
{
	checkLabyrinth((int**)array, size_x, size_y);
	int *p_array = (int*)array;
	int z = 0, i, j;
	int n = 2;
	
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
	*pN = n;
}
char shortest(int **array, int size_x, int size_y, int pos_x, int pos_y, int max_n)
{
	int *p_array = (int*)array;
	int min = max_n - 1, min_x, min_y;

	if(p_array[pos_x * size_x + (pos_y + 1)] < min && p_array[pos_x * size_x + (pos_y + 1)] != -2 && 
		p_array[pos_x * size_x + (pos_y + 1)] != 0 && p_array[pos_x * size_x + (pos_y + 1)] != 1) {
		min = p_array[pos_x * size_x + (pos_y + 1)];
		min_x = pos_x;
		min_y = pos_y + 1;
		// printf("R if\n");
	}
	if(p_array[pos_x * size_x + (pos_y - 1)] < min && p_array[pos_x * size_x + (pos_y - 1)] != -2 && 
		p_array[pos_x * size_x + (pos_y - 1)] != 0 && p_array[pos_x * size_x + (pos_y - 1)] != 1) {
		min = p_array[pos_x * size_x + pos_y - 1];
		min_x = pos_x;
		min_y = pos_y - 1;
		// printf("L if\n");
	}
	if(p_array[(pos_x - 1) * size_x + pos_y] < min && p_array[(pos_x - 1) * size_x + pos_y] != -2 && 
		p_array[(pos_x - 1) * size_x + pos_y] != 0 && p_array[(pos_x - 1) * size_x + pos_y] != 1) {
		min = p_array[(pos_x - 1) * size_x + pos_y];
		min_x = pos_x - 1;
		min_y = pos_y;
		// printf("U if\n");
	}
	if(p_array[(pos_x + 1) * size_x + pos_y] < min && p_array[(pos_x + 1) * size_x + pos_y] != -2 && 
		p_array[(pos_x + 1) * size_x + pos_y] != 0 && p_array[(pos_x + 1) * size_x + pos_y] != 1) {
		min = p_array[(pos_x + 1) * size_x + pos_y];
		min_x = pos_x + 1;
		min_y = pos_y;
		// printf("D if\n");
	}
	if(min_x == pos_x && min_y == pos_y + 1)
		return 'R';
	if(min_x == pos_x && min_y == pos_y - 1)
		return 'L';
	if(min_x == pos_x - 1 && min_y == pos_y)
		return 'U';
	if(min_x == pos_x + 1 && min_y == pos_y)
		return 'D';
}
void back(int **array, int size_x, int size_y, int max_n, char *way, int sizeWay)
{
	int *p_array = (int*)array;
	int i, j, enter_x, enter_y, exit_x, exit_y;

	for(i = 0; i < size_x; i++) {		// TODO optimize
		for(j = 0; j < size_y; j++) {
			if(p_array[i * size_x + j] == -1) {	// find enter
				enter_x = i;
				enter_y = j;
			}
			if(p_array[i * size_x + j] == -2) {	// find exit
				exit_x = i;
				exit_y = j;
			}
		}
	}

	i = 0;
	int back_x = exit_x;
	int back_y = exit_y;
	way[0] = shortest((int**)array, size_x, size_y, exit_x, exit_y, max_n);

	do {
		if(back_x == enter_x && back_y == enter_y) {
			break;
		}
		if(way[i] == 'R') {
			back_y = back_y + 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y, max_n);
		}
		if(way[i] == 'L') {
			back_y = back_y - 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y, max_n);
		}
		if(way[i] == 'U') {
			back_x = back_x - 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y, max_n);
		}
		if(way[i] == 'D') {
			back_x = back_x + 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y, max_n);
		}
		i++;
	} while (i < 4);
}