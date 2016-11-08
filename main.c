// c-labyrinth
// Coded by Xellor
#include <stdio.h>
#include <stdlib.h>

void printTDArray(const int **array, int size_x, int size_y);
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
	printTDArray((const int**)labyrinth, size_x, size_y);
	wave((int**)labyrinth, size_x, size_y);
	printf("Labyrinth after wave:\n");
	printTDArray((const int**)labyrinth, size_x, size_y);
	back((int**)labyrinth, size_x, size_y, way, (size_x * size_y));
	printf("\nYou exit here: ");
	printCArray(way, size_x * size_y);
	return 0;
}
void printTDArray(const int **array, int size_x, int size_y)
{
	int *pArray = (int*)array;
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			printf("%3d", pArray[i * size_x + j]);
		}
		printf("\n");
	}
}
void printCArray(char array[], int size)
{
	// TODO раз уж ты вывводишь посимвольно, и знаешь, что твоя строка оканчивается на '\0',
	// то гораздо логичнее выводить в цикле while до тех пор пока не стретишь '\0'
	// P.s. а вообще можно было вместо цикла написать: printf("%s", array);
	for (unsigned i = 0; i < size; i++) {
		printf("%c", array[i]);
	}
	printf(";\n");
}
// check numbers enters and exits
void checkLabyrinth(int **array, int size_x, int size_y)
{
	int *pArray = (int*)array;
	int numEnter = 0,
		numExit  = 0;
	// TODO как только ты нашел вход и выход можно заканчивать обход массива,
	// иначе ты выполняешь кучу ненужных операций сравнения
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			if (pArray[i * size_x + j] == -1) {
				numEnter++;
			}
			if (pArray[i * size_x + j] == -2) {
				numExit++;
			}
		}
	}
	if (numEnter == 1 && numExit == 1) {
		printf("Check is [OK]\n");
	}
	else {
		printf("Check is [ERROR]\nEnters = %d\nExits = %d\n",
			numEnter, numExit);
		exit(1);
	}
}
// marks adjacent sections 'pos_x' and 'pos_y' flag 'n'
void mark(int **array, int size_x, int size_y, int n, int pos_x, int pos_y)
{
	int *pArray = (int*)array;
	if (pArray[pos_x * size_x + pos_y + 1] == 1) {
		pArray[pos_x * size_x + pos_y + 1] = n;
	}
	if (pArray[pos_x * size_x + pos_y - 1] == 1) {
		pArray[pos_x * size_x + pos_y - 1] = n;
	}
	if (pArray[(pos_x + 1) * size_x + pos_y] == 1) {
		pArray[(pos_x + 1) * size_x + pos_y] = n;
	}
	if (pArray[(pos_x - 1) * size_x + pos_y] == 1) {
		pArray[(pos_x - 1) * size_x + pos_y] = n;
	}
}
void wave(int **array, int size_x, int size_y)	// wave function
{
	// TODO логичнее выполнять проверку до вызова функции wave,
	// т.к. она не является частью логику распространения волны
	checkLabyrinth((int**)array, size_x, size_y);
	int *pArray = (int*) array;
	int n = 2, i, j;

	for (i = 0; i < size_x; i++) {
		for (j = 0; j < size_y; j++) {
			if (pArray[i * size_x + j] == -1) {
				mark((int**)array, size_x, size_y, n, i, j);
				n++;
				break;
			}
		}
	}
	// TODO не понятно, что за переменные m1 и m2. (лучше поменять название или пояснить комментом)
	// m2 == m1, зачем это? И я не вижу способа, чтобы это условие выполнилось хоть когда-нибудь.
	// Если проверка на продвижение фронта, то у тебя опечатка из-за которая это не работает.
	// А слабо без обхода всего массива для каждой "волны".
	// Условие остановки - не конец обхода лабиринта, а нахождение выхода или обнаружение, что все пути являются тупиковыми.
	// Иначе у тебя цикл вхолостую работает
	//
	// Также нет необходимости при каждой итерации внешнего цикла перебирать весь массив.
	// Достаточно перебрать точки фронта (точки которые ты пометил на предыдущей итерации)
	for (int m1 = 2, m2 = 0; n <= size_x * size_y; m2 == m1, n++) {
		for (i = 0; i < size_x; i++) {
			for (j = 0; j < size_y; j++) {
				if (pArray[i * size_x + j] == n - 1) {
					mark((int**)array, size_x, size_y, n, i, j);
					m1++;
				}
			}
		}
		if (m1 == m2) {
			break;
		}
	}
}	// return nearest section (Right, Up etc)
char shortest(int **array, int size_x, int size_y, int pos_x, int pos_y)
{
	int *pArray = (int*)array;
	int min = size_x * size_y, min_x, min_y;

	// TODO условие внутри if'ов одно и то же и по факту в этом месте сильной дублирование кода,
	// это следует вынести в отдельную функцию.
	// Довольно часто такой код содержит copy-paste ошибки
	if (pArray[pos_x * size_x + (pos_y + 1)] < min &&
	pArray[pos_x * size_x + (pos_y + 1)] != -2 &&
	pArray[pos_x * size_x + (pos_y + 1)] != 0 &&
	pArray[pos_x * size_x + (pos_y + 1)] != 1) {
		min = pArray[pos_x * size_x + (pos_y + 1)];
		min_x = pos_x;
		min_y = pos_y + 1;
	}
	if (pArray[pos_x * size_x + (pos_y - 1)] < min &&
	pArray[pos_x * size_x + (pos_y - 1)] != -2 &&
	pArray[pos_x * size_x + (pos_y - 1)] != 0 &&
	pArray[pos_x * size_x + (pos_y - 1)] != 1) {
		min = pArray[pos_x * size_x + pos_y - 1];
		min_x = pos_x;
		min_y = pos_y - 1;
	}
	if (pArray[(pos_x - 1) * size_x + pos_y] < min &&
	pArray[(pos_x - 1) * size_x + pos_y] != -2 &&
	pArray[(pos_x - 1) * size_x + pos_y] != 0 &&
	pArray[(pos_x - 1) * size_x + pos_y] != 1) {
		min = pArray[(pos_x - 1) * size_x + pos_y];
		min_x = pos_x - 1;
		min_y = pos_y;
	}
	if (pArray[(pos_x + 1) * size_x + pos_y] < min &&
	pArray[(pos_x + 1) * size_x + pos_y] != -2 &&
	pArray[(pos_x + 1) * size_x + pos_y] != 0 &&
	pArray[(pos_x + 1) * size_x + pos_y] != 1) {
		min = pArray[(pos_x + 1) * size_x + pos_y];
		min_x = pos_x + 1;
		min_y = pos_y;
	}
	if (min_x == pos_x && min_y == pos_y + 1) {
		return 'R';
	} else if (min_x == pos_x && min_y == pos_y - 1) {
		return 'L';
	} else if (min_x == pos_x - 1 && min_y == pos_y) {
		return 'U';
	} else if (min_x == pos_x + 1 && min_y == pos_y) {
		return 'D';
	} else {
		return '\0';
	}
}
// function way back
void back(int **array, int size_x, int size_y, char *way, int sizeWay)
{
	int *pArray = (int*)array;
	int i, j, enter_x, enter_y, exit_x, exit_y;

	// TODO тут не замечание, а просто комментарий: если бы не этот способ поиска конца,
	// то, вероятно, твоя реализация смогла бы обрабатывать ситуацию нескольких выходов.
	for (i = 0; i < size_x; i++) {
		for (j = 0; j < size_y; j++) {
			if (pArray[i * size_x + j] == -1) {	// find enter
				enter_x = i;
				enter_y = j;
			}
			if (pArray[i * size_x + j] == -2) {	// find exit
				exit_x = i;
				exit_y = j;
			}
		}
	}
	int back_x = exit_x;
	int back_y = exit_y;
	way[0] = shortest((int**)array, size_x, size_y, exit_x, exit_y);

	for (i = 0; i < size_x * size_y; i++) {
		if (back_x == enter_x && back_y == enter_y) {
			break;
		} else if (way[i] == 'R') {
			back_y = back_y + 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y);
		} else if (way[i] == 'L') {
			back_y = back_y - 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y);
		} else if (way[i] == 'U') {
			back_x = back_x - 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y);
		} else if (way[i] == 'D') {
			back_x = back_x + 1;
			way[i + 1] = shortest((int**)array, size_x, size_y, back_x, back_y);
		} else {
			way[i + 1] = '\0';
		}
	}
	normWayArray(way, sizeWay);
}
void normWayArray(char *way, int size)	// normalize 'way' array
{
	const int tempSize = size;
	char temp[tempSize];
	int i, j, min_n;

	// TODO тут чтобы найти конец пути достаточно найти индекс '\0' т.к. ты явно записываешь '\0' при формированнии строки
	for (i = 0, j = 0; i < size; i++) {	// search minimal n
		if (way[i] == 'R' || way[i] == 'L' || way[i] == 'U' || way[i] == 'D') {
			continue;
		} else {
			break;
		}
	}
	min_n = i - 2;

	// TODO эту задачу обычно выполняют при помощи одной индексной переменой. temp[i] = way[min_n - i]
	// reverse 'way' array, write result in 'temp' array
	for (i = 0, j = min_n; j >= 0; i++, j--) {
		temp[i] = way[j];
	}
	for (i = 0; i <= min_n; i++) {	// 'way' array = 'temp' array
		way[i] = temp[i];
	}
	for( i = 0; i <= size; i++) {	// invert Right, Left, Up, Down
		if (way[i] == 'R') {
			way[i] = 'L';
			continue;
		} else if (way[i] == 'L') {
			way[i] = 'R';
			continue;
		} else if (way[i] == 'U') {
			way[i] = 'D';
			continue;
		} else if (way[i] == 'D') {
			way[i] = 'U';
			continue;
		} else {
			way[i] = '\0';
		}
	}
	for (i = min_n; i <= size - min_n; i++) {	// clean 'way' array of trash
		way[i] = '\0';
	}
}