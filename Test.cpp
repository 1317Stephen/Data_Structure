#include "stdafx.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "windows.h"
#include "conio.h"
#include "signal.h"
#define MAX_QUEUE_SIZE 50
typedef int element;
typedef struct circularQueue
{
	element *queue;
	int front;
	int rear;
}CircularQueue;

void initCQueue(CircularQueue **q_p)
{
	*q_p = (CircularQueue*)malloc(sizeof(CircularQueue));

	(*q_p)->queue = (element *)malloc(sizeof(element)*MAX_QUEUE_SIZE);
	(*q_p)->front = 0;
	(*q_p)->rear = 0;
}
int isEmptyCQueue(CircularQueue *q)
{
	return (q->front == q->rear);
}

int isFullCQueue(CircularQueue *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
void enqueue(CircularQueue *q, element item)
{
	if (isFullCQueue(q))
	{
		printf("<EnQueue Error> Full \n");
	}

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
element dequeue(CircularQueue *q)
{
	if (isEmptyCQueue(q))
	{
		printf("<DeQueue Error> Empty \n");
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}
void printCQueue(CircularQueue *q)
{
	int i = 0;
	printf("Queue: ");
	for (i = q->front + 1; i <= q->rear; i++)
	{
		printf("%d ", q->queue[i]);
	}

	printf("\n");
}
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void print_maze(char **maze, int row, int column)
{
	int i = 0, j = 0;

	for (i = 0; i<row; i++)
	{
		//print row, column numbers
		gotoxy(i * 4 + 5, 1);
		printf(" c%d", i);

		gotoxy(1, i * 2 + 4);
		printf("r%d", i);
		for (j = 0; j<column; j++)
		{

			gotoxy(i * 4 + 6, j * 2 + 4);
			//		printf("inside print_m ftn");
			printf("%c", maze[j][i]);
		}
	}
	printf("\n\n");
}
void printAlgorithmMaze(char **maze, int row, int column, CircularQueue *queueLocations)
{
	int i = 0, j = 0;
	int location = 0;
	int currentRow = 0, currentColumn = 0;
	while (!isEmptyCQueue(queueLocations))
	{
		location = dequeue(queueLocations);
		currentRow = location / column;
		currentColumn = location % column;

		for (i = 0; i<row; i++)
		{
			//print row, column numbers
			gotoxy(i * 4 + 5, 1);
			printf(" c%d", i);

			gotoxy(1, i * 2 + 4);
			printf("r%d", i);
			for (j = 0; j<column; j++)
			{
				if (currentRow == i&& currentColumn == j)
				{
					maze[i][j] = '.';
				}

				gotoxy(i * 4 + 6, j * 2 + 4);
				//		printf("inside print_m ftn");
				printf("%c", maze[j][i]);
			}
		}
		printf("\n\n");
		getchar();
	}

}
void initMaze(char ***maze, int row, int column)
{
	int i = 0, j = 0;
	*maze = (char **)malloc(sizeof(char *)*row);
	for (i = 0; i<row; i++)
	{
		(*maze)[i] = (char *)malloc(sizeof(char) * column);
	}
	for (i = 0; i<row; i++)
	{
		for (j = 0; j<column; j++)
		{
			(*maze)[i][j] = '0';
		}
	}

	(*maze)[1][0] = 'e';
	(*maze)[row - 2][column - 1] = 'x';
}
int main()
{
	CircularQueue *queueLocations = NULL;
	char **maze = NULL;

	initCQueue(&queueLocations);
	enqueue(queueLocations, 1);
	enqueue(queueLocations, 3);
	enqueue(queueLocations, 4);
	enqueue(queueLocations, 10);

	initMaze(&maze, 6, 6);
	printAlgorithmMaze(maze, 6, 6, queueLocations);
	return 0;
}