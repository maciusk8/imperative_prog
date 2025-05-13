#include <stdio.h>
#include <stdlib.h>
#define N 20

typedef struct Ant {
	int pi, pj;
	int direction;
} Ant;

enum Direction { UP=0, RIGHT=1, DOWN=2, LEFT=3 };

int rnd(const int min, const int max) {
	return (rand() % (max - min)) + min;
}

void print_board(int** board, const int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d ", board[i][j]);
		} 
		printf("\n");
	}

}

void print_ant(const Ant ant)
{
	switch (ant.direction)
	{
		case UP:
			printf("%d %d N\n", ant.pi, ant.pj);
			break;
		case RIGHT:
			printf("%d %d E\n", ant.pi, ant.pj);
			break;
		case DOWN:
			printf("%d %d S\n", ant.pi, ant.pj);
			break;
		case LEFT:
			printf("%d %d W\n", ant.pi, ant.pj);
			break;
	}
}

void init_board(int*** board, const int n) 
{
	*board = (int**)malloc(n * sizeof(int*));
	for(int i = 0; i < n; i++)
	{
		(*board)[i] = (int*)malloc(n*sizeof(int));
		for(int j = 0; j <n; j++)
		{
			(*board)[i][j] = rnd(1,9);
		} 
	}
}

void free_board(int** board, const int n) 
{
	if (board == NULL)
	{
		return;
	}
	else
	{
		for(int i = 0; i < n; i++)
		{
			free(board[i]);
		}
		free(board);
	}
}

void move(Ant* ant, const int n)
 {
	int i = ant->pi;
	int j = ant->pj;
	switch (ant->direction) 
	{
    case UP:    i--; if (i < 0) i = n - 1; break;  
    case RIGHT: j++; if (j >= n) j = 0; break;     
    case DOWN:  i++; if (i >= n) i = 0; break; 
    case LEFT:  j--; if (j < 0) j = n - 1; break;  
	}
	ant->pi = i;
	ant->pj = j;
}


void ant_move(int** board, const int n, Ant* ant) 
{
	int i = ant->pi;
	int j = ant->pj;
	switch (board[i][j])
	{
		case 1:
			board[i][j] = 7;
			move(ant, n);
			break;
		case 2:
			board[i][j] = 4;
			ant->direction++;
			ant->direction %=4;
			break;
		case 3:
			board[i][j] = 2;
			ant->direction+=3;
			ant->direction %=4;
			break;
		case 4:
			board[i][j] = 6;
			ant->direction++;
			ant->direction %=4;
			move(ant, n);
			ant->direction+=3;
			ant->direction%=4;
			break;
		case 5:
			board[i][j] = 3;
			ant->direction+=3;
			ant->direction %=4;
			move(ant, n);
			ant->direction++;
			ant->direction %=4;
			break;
		case 6:
			board[i][j] = 5;
			ant->direction+=2;
			ant->direction %=4;
			move(ant, n);
			ant->direction+=2;
			ant->direction%=4;
			break;
		case 7:
			board[i][j] = 8;
			ant->direction+=2;
			ant->direction %=4;
			break;
		case 8:	
			board[i][j] = 1;
			break;
	}
}

void ant_simulation(int** board, const int n, Ant* ant, const int steps)
{
	ant->pi = 0;
	ant->pj = 0;
	ant->direction = RIGHT;
	for (int i = 0; i < steps; i++)
	{
		ant_move(board, n, ant);
	}
}

int main(void) {
	int** board;
	int n, steps;
	unsigned seed;
	Ant ant;

	scanf("%d %d %d", &n, &seed, &steps);
	srand(seed);
	init_board(&board, n);
	ant_simulation(board, n, &ant, steps);
	print_board(board, n);
	print_ant(ant);

	free_board(board, n);

	return 0;
}

