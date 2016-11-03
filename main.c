// c-labyrinth
// Coded by Xellor
#include <stdio.h>
#include <stdlib.h>

void printTDArray(int **array, int size_x, int size_y);
void printCArray(char array[], int size);
void checkLabyrinth(int **array, int size_x, int size_y);
void mark(int **array, int size_x, int size_y, int n, int pos_x, int pos_y);
void wave(int **array, int size_x, int size_y);
char shortest(int **array, int size_x, int size_y, int pos_x, int pos_y);
void back(int **array, int size_x, int size_y, char *way, int sizeWay);
void normWayArray(char *wat, int size);

int main()
{
	const unsigned size_x = 17,				// size 'labyrinth' array
				   size_y = 17;
	char way[size_x * size_y];				// 'way' array
	int labyrinth[size_x][size_y] =			// 'labyrinth' array
			{{0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0},
			 {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,-2},
			 {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
			 {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
			 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
			 {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
			 {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0},
			 {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
			 {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
			 {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
			 {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			 {0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
			 {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
			 {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
			 {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
			 {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

	printf("Labyrinth:\n");
	printTDArray((int**)labyrinth, size_x, size_y);
	wave((int**)labyrinth, size_x, size_y);
	printf("Labyrinth after wave:\n");
	printTDArray((int**)labyrinth, size_x, size_y);
	back((int**)labyrinth, size_x, size_y, way, (size_x * size_y));
	printf("\nYou exit here: ");
	printCArray(way, (size_x * size_y));
	return 0;
}
void printTDArray(int **array, int size_x, int size_y)
{
	int *pArray = (int*)array;
	for(int i = 0; i < size_x; i++) {
		for(int j = 0; j < size_y; j++)
			printf("%3d", pArray[i * size_x + j]);
		printf("\n");
	}
}
void printCArray(char array[], int size)
{
	for(unsigned i = 0; i < size; i++)
		printf("%c", array[i]);
	printf(";\n");
}	// check numbers enters and exits
void checkLabyrinth(int **array, int size_x, int size_y)
{
	int *pArray = (int*)array;
	int numEnter = 0,
		numExit  = 0;
	for(int i = 0; i < size_x; i++) {
		for(int j = 0; j < size_y; j++) {
			if(pArray[i * size_x + j] == -1)
				numEnter++;
			if(pArray[i * size_x + j] == -2)
				numExit++;
		}
	}
	if(numEnter == 1 && numExit == 1)
		printf("Check is [OK]\n");
	else {
		printf("Check is [ERROR]\nEnters = %d\nExits = %d\n", 
			numEnter, numExit);
		exit(1);
	}
}	// marks adjacent sections 'pos_x' and 'pos_y' flag 'n'
void mark(int **array, int size_x, int size_y, int n, int pos_x, int pos_y)
{
	int *pArray = (int*)array;
	if(pArray[pos_x * size_x + pos_y + 1] == 1)
		pArray[pos_x * size_x + pos_y + 1] = n;
	if(pArray[pos_x * size_x + pos_y - 1] == 1)
		pArray[pos_x * size_x + pos_y - 1] = n;
	if(pArray[(pos_x + 1) * size_x + pos_y] == 1)
		pArray[(pos_x + 1) * size_x + pos_y] = n;
	if(pArray[(pos_x - 1) * size_x + pos_y] == 1)
		pArray[(pos_x - 1) * size_x + pos_y] = n;
}
void wave(int **array, int size_x, int size_y)	// wave function
{
	checkLabyrinth((int**)array, size_x, size_y);
	int *pArray = (int*) array;
	int n = 2, m1 = 2, m2 = 0, i, j;

	for(i = 0; i < size_x; i++) {
		for(j = 0; j < size_y; j++) {
			if(pArray[i * size_x + j] == -1) {
				mark((int**)array, size_x, size_y, n, i, j);
				n++;
				m1++;
				break;
			}
		}
	}
	do {
		for(i = 0; i < size_x; i++) {
			for(j = 0; j < size_y; j++) {
				if(pArray[i * size_x + j] == n - 1) {
					mark((int**)array, size_x, size_y, n, i, j);
					m1++;
				}
			}
		}
		printf("n = %d, m1 = %d\n", n, m1);
		n++;
		if(m1 == m2)
			break;
		m2 = m1;
	} while (true);
}	// return nearest section (Right, Up etc)
char shortest(int **array, int size_x, int size_y, int pos_x, int pos_y)
{
	int *pArray = (int*)array;
	int min = size_x * size_y, min_x, min_y;

	if(pArray[pos_x * size_x + (pos_y + 1)] < min &&
	pArray[pos_x * size_x + (pos_y + 1)] != -2 &&
	pArray[pos_x * size_x + (pos_y + 1)] != 0 &&
	pArray[pos_x * size_x + (pos_y + 1)] != 1) {
		min = pArray[pos_x * size_x + (pos_y + 1)];
		min_x = pos_x;
		min_y = pos_y + 1;
	}
	if(pArray[pos_x * size_x + (pos_y - 1)] < min &&
	pArray[pos_x * size_x + (pos_y - 1)] != -2 &&
	pArray[pos_x * size_x + (pos_y - 1)] != 0 &&
	pArray[pos_x * size_x + (pos_y - 1)] != 1) {
		min = pArray[pos_x * size_x + pos_y - 1];
		min_x = pos_x;
		min_y = pos_y - 1;
	}
	if(pArray[(pos_x - 1) * size_x + pos_y] < min &&
	pArray[(pos_x - 1) * size_x + pos_y] != -2 &&
	pArray[(pos_x - 1) * size_x + pos_y] != 0 &&
	pArray[(pos_x - 1) * size_x + pos_y] != 1) {
		min = pArray[(pos_x - 1) * size_x + pos_y];
		min_x = pos_x - 1;
		min_y = pos_y;
	}
	if(pArray[(pos_x + 1) * size_x + pos_y] < min &&
	pArray[(pos_x + 1) * size_x + pos_y] != -2 &&
	pArray[(pos_x + 1) * size_x + pos_y] != 0 &&
	pArray[(pos_x + 1) * size_x + pos_y] != 1) {
		min = pArray[(pos_x + 1) * size_x + pos_y];
		min_x = pos_x + 1;
		min_y = pos_y;
	}
	if(min_x == pos_x && min_y == pos_y + 1)
		return 'R';
	else if(min_x == pos_x && min_y == pos_y - 1)
		return 'L';
	else if(min_x == pos_x - 1 && min_y == pos_y)
		return 'U';
	else if(min_x == pos_x + 1 && min_y == pos_y)
		return 'D';
	else return '\0';
}	// function way back
void back(int **array, int size_x, int size_y, char *way, int sizeWay)
{
	int *pArray = (int*)array;
	int i, j, enter_x, enter_y, exit_x, exit_y;

	for(i = 0; i < size_x; i++) {
		for(j = 0; j < size_y; j++) {
			if(pArray[i * size_x + j] == -1) {	// find enter
				enter_x = i;
				enter_y = j;
			}
			if(pArray[i * size_x + j] == -2) {	// find exit
				exit_x = i;
				exit_y = j;
			}
		}
	}

	i = 0;
	int back_x = exit_x;
	int back_y = exit_y;
	way[0] = shortest((int**)array, size_x, size_y, exit_x, exit_y);

	do {
		if(back_x == enter_x && back_y == enter_y) {
			break;
		} else if(way[i] == 'R') {
			back_y = back_y + 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y);
		} else if(way[i] == 'L') {
			back_y = back_y - 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y);
		} else if(way[i] == 'U') {
			back_x = back_x - 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y);
		} else if(way[i] == 'D') {
			back_x = back_x + 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y);
		} else {
			way[i + 1] = '\0';
		}
		i++;
	} while(i < size_x * size_y);
	normWayArray(way, sizeWay);
}
void normWayArray(char *way, int size)	// normalize 'way' array
{
	const int tempSize = size;
	char temp[tempSize];
	int i = 0, j = 0, min_n;

	do {
		if(way[i] == 'R' || way[i] == 'L' || way[i] == 'U' || way[i] == 'D') {
			i++;
		} else
			break;
	} while(i < size);

	min_n = i - 2;
	i = 0;
	j = min_n;

	do {	// reverse 'way' array, write result in 'temp' array
		temp[i] = way[j];
		i++;
		j--;
	} while (j > 0);

	i = 0;

	do {	// 'way' array = 'temp' array
		way[i] = temp[i];
		i++;
	} while (i < min_n);

	i = 0;

	do {	// invert Right, Left, Up, Down
		if(way[i] == 'R') {
			way[i] = 'L';
			i++;
			continue;
		} else if(way[i] == 'L') {
			way[i] = 'R';
			i++;
			continue;
		} else if(way[i] == 'U') {
			way[i] = 'D';
			i++;
			continue;
		} else if(way[i] == 'D') {
			way[i] = 'U';
			i++;
			continue;
		} else
			way[i] = '\0';
		i++;
	} while(i < size);
	i = min_n;
	do {	// clean 'way' array of trash
		way[i] = '\0';
		i++;
	} while (i <= size - (min_n));
}
