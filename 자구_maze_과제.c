#include<stdio.h>
//#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
//#include <conio.h>
#include <signal.h>

typedef int element;
typedef struct stackNodeMaze
{
	element r;
	element c;
	struct stackNodeMaze *link;
	struct stackNodeMaze *parent;

} StackNodeMaze;

typedef struct linkedStackMaze
{
	StackNodeMaze *top;
} LinkedStackMaze;


typedef struct cdlistNode
{
	element data;
	struct cdlistNode *front_link;
	struct cdlistNode *rear_link;
}CDlistNode;
CDlistNode* new_CDNode();

void print_CDList(CDlistNode *CD_head_p, int list_size);
void linking_two_CDNode(CDlistNode *CD_front_p, CDlistNode *CD_rear_p);
void insert_first_CDNode(CDlistNode **CD_head_pp, CDlistNode **CD_tail_pp, int data);
void insert_head_CDNode(CDlistNode **CD_head_pp, CDlistNode **CD_tail_pp, int data);
void insert_tail_CDNode(CDlistNode **CD_head_pp, CDlistNode **CD_tail_pp, int data);
void insert_body_CDNode(CDlistNode *CD_head_p, CDlistNode *CD_tail_p, int data, int *cd_list_size);
int insert_CDNode(CDlistNode **CD_head_pp, CDlistNode **CD_tail_pp, int data, int *cd_list_size);

//Maze setting
void gotoxy(int x, int y);
void initMaze(char ***maze, int row, int column);
void makeMazeWall(char ***maze, int row, int column, CDlistNode **saveWallLocatoinHead, int *wallNumber);
void makeMaze(char ***maze, int row, int column, int wallNumber);
void print_maze(char **maze, int row, int column);

//Helper
void init_location(StackNodeMaze **here, StackNodeMaze **entry);
void makeStartingPointHelper(char ***maze, char type, int helperNumber, int row, int column, CDlistNode **saveWallLocatoinHead, int *wallCount);

void DFS(char** maze, int row, int column);
void BFS(char** maze, int row, int column);
int IsWalkableAt(char** maze, int r, int c, int row, int column);
int CompareNode(StackNodeMaze n1, StackNodeMaze n2);
LinkedStackMaze* NewStack();
StackNodeMaze* PushStack(LinkedStackMaze* head, int r, int c, StackNodeMaze* parent);
void PushLastStack(LinkedStackMaze* head, int r, int c, StackNodeMaze* parent);
StackNodeMaze* PopStack(LinkedStackMaze* head);
StackNodeMaze* PeekStack(LinkedStackMaze* head);
int CompareNode(StackNodeMaze n1, StackNodeMaze n2);


int main()
{

	char **maze = NULL;
	makeMaze(&maze, 6, 6, 4);
	DFS(maze, 6, 6);

	//BFS(maze, 6, 6);
	return 0;

}

void stopwatch(int onOff, int *oldTime, int *timerBuffer, int endTime)
{



	if (onOff == 1)

	{

		*oldTime = (int)time(NULL);

	}



	else if (onOff == 0)

	{

		*timerBuffer = (int)time(NULL) - *oldTime;

	}



	//	*timerBuffer = (int)time(NULL) - *oldTime;

	//	printf("timer: %d\n", *oldTime);



	if (*timerBuffer >= endTime)

	{
		printf("timeover >> timer: %d\n", *timerBuffer);
//		_exit;
	}

}

void timeOutExitMainFunction(int timer)
{



}

void gotoExit(char ***maze, int row, int column, StackNodeMaze **here, StackNodeMaze **entry)

{

	(*here)->r = row - 2;

	(*here)->c = column - 1;

}

void init_location(StackNodeMaze **here, StackNodeMaze **entry)
{

	*here = (StackNodeMaze *)malloc(sizeof(StackNodeMaze));

	*entry = (StackNodeMaze *)malloc(sizeof(StackNodeMaze));

	(*here)->r = 1, (*here)->c = 0;

	(*entry)->r = 1, (*entry)->c = 0;

}

void makeStartingPointHelper(char ***maze, char type, int helperNumber, int row, int column, CDlistNode **saveWallLocatoinHead, int *wallCount)
{

	int i = 0, tmpInt = 0;

	int wallNumber = *wallCount;

	int random = 0;

	int *helperCellNumber = (int *)malloc(sizeof(int)*helperNumber);

	CDlistNode *helperLocation = NULL, *tail;



	CDlistNode  *tmp = NULL;



	srand(time(NULL));



	//	insert_CDNode(saveWallLocatoinHead, &((*saveWallLocatoinHead)->front_link), (row*column-1)-column, wallCount);

	while (*wallCount < helperNumber + wallNumber)

	{

		tmpInt = *wallCount;

		random = rand() % (row*column);

		insert_CDNode(saveWallLocatoinHead, &((*saveWallLocatoinHead)->front_link), random, wallCount);

		if ((tmpInt<*wallCount) && (random != (row*column - 1) - column) && (random != column))

		{

			helperCellNumber[i] = random;

			i++;

		}

	}

	printf("fin. setting helper \n");

	tmp = (*saveWallLocatoinHead)->front_link;

	for (i = 0; i< helperNumber; i++)

	{

		(*maze)[(helperCellNumber[i]) / column][(helperCellNumber[i]) % column] = type;



	}

	printf("fin. locat helper\n");

}

void gotoStartingPoint(char ***maze, int row, int column, StackNodeMaze **here, StackNodeMaze **entry)
{

	initMaze(maze, row, column);

	init_location(here, entry);

}

void timeView()
{

	time_t t;

	time(&t);



	printf("%s", ctime_s(NULL, NULL, &t));

}



void makeMaze(char ***maze, int row, int column, int wallNumber)
{

	int timer = 5;

	int oldTime = 0, timerBuffer = 0;

	int badgeNumber = 0;

	int random = 0;

	int i = 0, j = 0;

	CDlistNode *saveWallLocatoinHead = NULL;

	//srand(time(NULL));







	stopwatch(1, &oldTime, &timerBuffer, timer);

	//malloc & without wall

	printf("initMaze\n");

	initMaze(maze, row, column);



	stopwatch(0, &oldTime, &timerBuffer, timer);

	//make wall

	printf("make wall\n");

	makeMazeWall(maze, row, column, &saveWallLocatoinHead, &wallNumber);



	stopwatch(1, &oldTime, &timerBuffer, timer);

	//print maze

	_getch();

	system("cls");

	print_maze(*maze, row, column);



	stopwatch(0, &oldTime, &timerBuffer, timer);

	//add helper

	_getch();

	makeStartingPointHelper(maze, 'H', 1, row, column, &saveWallLocatoinHead, &wallNumber);

	print_maze(*maze, row, column);

	_getch();

	printf("add Helper\n");



	stopwatch(1, &oldTime, &timerBuffer, timer);

	//add Badge

	_getch();

	makeStartingPointHelper(maze, 'B', 2, row, column, &saveWallLocatoinHead, &wallNumber);

	print_maze(*maze, row, column);

	_getch();



	//timer

	stopwatch(0, &oldTime, &timerBuffer, timer);





}

void cellNumberToCoordinate(int cellNumber, int mazeRow, int mazeColumn, int *row, int *column)
{

	/* 4*4

	0(0,0)	1(0,1)	2	3

	4(1,0)	5(1,1)	6	7

	.......

	*/

	/* 5*2

	0 1 2 3 4

	5 6 7 8 9

	*/

	*row = cellNumber / mazeColumn;

	mazeColumn = cellNumber % mazeColumn;



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

void makeMazeWall(char ***maze, int row, int column, CDlistNode **saveWallLocatoinHead, int *wallNumber)
{

	int i = 0;

	int wallCount = 0;

	int random = 0;

	CDlistNode  *saveWallLocationTail = NULL, *tmp = NULL;

	//	*wallLocationRows = (int *)malloc(sizeof(int)*wallNumber);

	//	*wallLocationColumns = (int *)malloc(sizeof(int)*wallNumber);

	srand(time(NULL));



	while (wallCount< *wallNumber)

	{

		random = rand() % (row*column);

		insert_CDNode(saveWallLocatoinHead, &saveWallLocationTail, random, &wallCount);

	}

	printf("fin.setting wall# \n");

	tmp = *saveWallLocatoinHead;

	for (i = 0; i< *wallNumber; i++)

	{

		//		*wallLocationRows[i] = rand() % row;

		//		*wallLocationColumns[i] = rand() % row;



		(*maze)[(tmp->data) / column][(tmp->data) % column] = '1';

		tmp = tmp->rear_link;



		printf("setting wall %d \n", i + 1);

	}

	printf("fin.setting wall coor. \n");

}


void setting_maze(char ***maze, int row, int column)
{



	int random = 0;

	int i = 0, j = 0;

	srand(time(NULL));



	*maze = (char **)malloc(sizeof(char *)*row);

	for (i = 0; i<row; i++)

	{

		(*maze)[i] = (char *)malloc(sizeof(char) * column);

	}

	//	printf("msetting finish\n");

	for (i = 0; i<row; i++)

	{

		for (j = 0; j<column; j++)

		{

			random = rand() + 1;

			//			printf("r:%d",random);

			if (random % 2 == 0)

			{

				(*maze)[i][j] = '1';

				//				printf("maze[%d][%d]:%c\n",i,j,(*maze)[i][j]);

			}

			else

			{

				(*maze)[i][j] = '0';

				//				printf("maze[%d][%d]:%c\n", i, j, (*maze)[i][j]);

			}

		}

	}

	//	printf("vsetting finish\n");

	(*maze)[1][0] = 'e';

	//	printf("[1][0]:%c\n",(*maze)[1][0]);

	(*maze)[row - 2][column - 1] = 'x';

	//	printf("[3][4]:%c\n", (*maze)[3][4]);

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









CDlistNode* new_CDNode()
{

	CDlistNode *CD_p = (CDlistNode *)malloc(sizeof(CDlistNode));

	CD_p->data = 0;

	CD_p->front_link = NULL;

	CD_p->rear_link = NULL;

	return CD_p;

}

void print_CDList(CDlistNode *CD_head_p, int list_size)
{

	int i = 0;

	CDlistNode *CD_print_p = CD_head_p;



	printf("\n <Print circular double linked list> \n");

	printf("head->");

	for (i = 0; i < list_size; i++)

	{

		printf(" '%d' ", CD_print_p->data);

		CD_print_p = CD_print_p->rear_link;

	}

	printf("<-tail");

	printf("\n\n");

}

void linking_two_CDNode(CDlistNode *CD_front_p, CDlistNode *CD_rear_p)
{
	CD_front_p->rear_link = CD_rear_p;
	CD_rear_p->front_link = CD_front_p;

}

void insert_first_CDNode(CDlistNode **CD_head_pp, CDlistNode **CD_tail_pp, int data)
{

	CDlistNode *CD_p = new_CDNode();

	CD_p->data = data;



	*CD_head_pp = *CD_tail_pp = CD_p;

}

void insert_head_CDNode(CDlistNode **CD_head_pp, CDlistNode **CD_tail_pp, int data)

{

	CDlistNode *CD_p = new_CDNode();
	CD_p->data = data;
	linking_two_CDNode(CD_p, *CD_head_pp);
	linking_two_CDNode(*CD_tail_pp, CD_p);

	*CD_head_pp = CD_p;

}

void insert_tail_CDNode(CDlistNode **CD_head_pp, CDlistNode **CD_tail_pp, int data)

{
	CDlistNode *CD_p = new_CDNode();
	CD_p->data = data;
	linking_two_CDNode(*CD_tail_pp, CD_p);
	linking_two_CDNode(CD_p, *CD_head_pp);	
	*CD_tail_pp = CD_p;
}

void insert_body_CDNode(CDlistNode *CD_head_p, CDlistNode *CD_tail_p, int data, int *cd_list_size)

{
	int i = 0;
	CDlistNode *CD_p = new_CDNode();
	CDlistNode *CD_catch_p = CD_head_p;
	CDlistNode *CD_catch_rear_p = NULL;

	for (i = 0; i < *cd_list_size; i++)
	{
		if (data == CD_catch_p->data)
		{
			printf(">>>same data - delete \n");
			(*cd_list_size)--;
			return;
		}

		else if ((data > CD_catch_p->data) && (data < CD_catch_p->rear_link->data))
		{
			CD_p->data = data;
			CD_catch_rear_p = CD_catch_p->rear_link;			
			linking_two_CDNode(CD_catch_p, CD_p);
			linking_two_CDNode(CD_p, CD_catch_rear_p);
			return;
		}
		CD_catch_p = CD_catch_p->rear_link;
	}
}

int insert_CDNode(CDlistNode **CD_head_pp, CDlistNode **CD_tail_pp, int data, int *cd_list_size)
{
	printf("\n <Insert CDNode> \n");

	if (*cd_list_size == 0)
	{
		insert_first_CDNode(CD_head_pp, CD_tail_pp, data);
	}
	else if (data < (*CD_head_pp)->data)
	{
		insert_head_CDNode(CD_head_pp, CD_tail_pp, data);
	}
	else if (data >(*CD_tail_pp)->data)
	{
		insert_tail_CDNode(CD_head_pp, CD_tail_pp, data);
	}
	else
	{
		insert_body_CDNode(*CD_head_pp, *CD_tail_pp, data, cd_list_size);
	}
	(*cd_list_size)++;
	return (*cd_list_size);
}
//------------------------------------
//BFS Breath First Search
void BFS(char** maze, int row, int column)
{
	LinkedStackMaze* openList = NULL;
	LinkedStackMaze* closeList = NULL;

	StackNodeMaze startNode = { 1,0 };
	StackNodeMaze endNode = { row - 2,column - 1 };

	StackNodeMaze* node = NULL;		//현재 위치 잡아줄 놈
	
	openList = NewStack();
	closeList = NewStack();
	
	PushStack(openList, startNode.r, startNode.c, NULL);
	while (PeekStack(openList))		
	{
		node = PopStack(openList);	//오픈에서 가져오기
		PushStack(closeList, node->r, node->c, NULL);	//close에 넣기
		if (CompareNode(*node, endNode))
		{
			while (node != NULL) 
			{
				gotoxy(node->c * 4 + 6, node->r * 2 + 4);
				printf("#");
				node = node->parent;
				getch();
			}
			return; //경로 탐색 완료
		}
		//위
		if (IsWalkableAt(maze, node->r-1, node->c, row, column)) 
		{
			if(CheckNode(openList, node->r - 1, node->c) != 1
				&& CheckNode(closeList, node->r - 1, node->c) != 1)
				PushLastStack(openList, node->r-1, node->c, node);
		}
		//오른쪽
		if (IsWalkableAt(maze, node->r, node->c+1, row, column))
		{
			if (CheckNode(openList, node->r, node->c + 1) != 1
				&& CheckNode(closeList, node->r, node->c + 1) != 1)
				PushLastStack(openList, node->r, node->c+1, node);
		}
		//아래
		if (IsWalkableAt(maze, node->r+1, node->c, row, column))
		{
			if (CheckNode(openList, node->r + 1, node->c) != 1
				&& CheckNode(closeList, node->r + 1, node->c) != 1)
			PushLastStack(openList, node->r+1, node->c, node);
		}
		//왼쪽
		if (IsWalkableAt(maze, node->r, node->c-1, row, column))
		{
			if (CheckNode(openList, node->r, node->c - 1) != 1
				&& CheckNode(closeList, node->r, node->c - 1) != 1)
			PushLastStack(openList, node->r, node->c-1, node);
		}

	}
	return;	//경로 검색 불가

}
//------------------------------------
//DFS Deep First Search
void DFS(char** maze, int row, int column)
{
	LinkedStackMaze* openList = NULL;
	LinkedStackMaze* closeList = NULL;

	StackNodeMaze startNode = { 1,0 };
	StackNodeMaze endNode = { row - 2,column - 1 };

	StackNodeMaze* node = NULL;		//현재 위치 잡아줄 놈

	openList = NewStack();
	closeList = NewStack();

	PushStack(openList, startNode.r, startNode.c, NULL);
	while (PeekStack(openList))
	{
		node = PopStack(openList);	//오픈에서 가져오기
		PushStack(closeList, node->r, node->c, NULL);	//close에 넣기
		////
		gotoxy(node->c * 4 + 6, node->r * 2 + 4);
		printf("!");
		getch();

		////
		if (CompareNode(*node, endNode))
		{
			while (node != NULL)
			{
				gotoxy(node->c * 4 + 6, node->r * 2 + 4);
				printf("#");
				node = node->parent;
				getch();
			}
			return; //경로 탐색 완료
		}
		//위
		if (IsWalkableAt(maze, node->r - 1, node->c, row, column))
		{
			if (CheckNode(openList, node->r - 1, node->c) != 1
				&& CheckNode(closeList, node->r - 1, node->c) != 1)
				PushStack(openList, node->r - 1, node->c, node);
		}
		//오른쪽
		if (IsWalkableAt(maze, node->r, node->c + 1, row, column))
		{
			if (CheckNode(openList, node->r, node->c + 1) != 1
				&& CheckNode(closeList, node->r, node->c + 1) != 1)
				PushStack(openList, node->r, node->c + 1, node);
		}
		//아래
		if (IsWalkableAt(maze, node->r + 1, node->c, row, column))
		{
			if (CheckNode(openList, node->r + 1, node->c) != 1
				&& CheckNode(closeList, node->r + 1, node->c) != 1)
				PushStack(openList, node->r + 1, node->c, node);
		}
		//왼쪽
		if (IsWalkableAt(maze, node->r, node->c - 1, row, column))
		{
			if (CheckNode(openList, node->r, node->c - 1) != 1
				&& CheckNode(closeList, node->r, node->c - 1) != 1)
				PushStack(openList, node->r, node->c - 1, node);
		}

	}
	return;	//경로 검색 불가

}

int CheckNode(LinkedStackMaze* stack, int r, int c)
{
	StackNodeMaze* temp = stack->top;
	while (temp != NULL)
	{
		if (temp->r == r && temp->c == c )
			return 1;

		temp = temp->link;
	}
	return 0;
}
int IsWalkableAt(char** maze, int r, int c, int row, int column) 
{
	char ch = '0';
	if ((r >= 0 && r < row) && (c > 0 && c < column))
	{
		ch = maze[r][c];
		if (ch != 'H' && ch != 'B' && ch != '1')
		{
			return 1;
		}
	}
	return 0;
}

int CompareNode(StackNodeMaze n1, StackNodeMaze n2) 
{
	if (n1.r == n2.r && n1.c == n2.c)
		return 1;
	return 0;
}
LinkedStackMaze* NewStack()
{
	LinkedStackMaze* newStack = (LinkedStackMaze*)malloc(sizeof(LinkedStackMaze));
	newStack->top=NULL;
	return newStack ;
}
StackNodeMaze* PushStack(LinkedStackMaze* head, int r, int c, StackNodeMaze* parent)
{
	//스택 유무 검사
	if(head == NULL)
	{
		return NULL;
	}
	//노드 생성 및 초기화
	StackNodeMaze* temp = (StackNodeMaze*)malloc(sizeof(StackNodeMaze));
	temp->c = c;
	temp->r = r;
	temp->link = head->top;
	temp->parent = parent;

	temp->link = head->top;
	head->top = temp;

	return temp;
}
void PushLastStack(LinkedStackMaze* head, int r, int c, StackNodeMaze* parent)
{
	StackNodeMaze* top = head->top;
	if (top == NULL)
	{
		PushStack(head, r, c, NULL);
		return;
	}
	while (top->link != NULL)
	{
		top = top->link;
	}
	//top이 NULL 인경우
	StackNodeMaze* temp = (StackNodeMaze*)malloc(sizeof(StackNodeMaze));
	temp->c = c;
	temp->r = r;
	temp->link = NULL;
	temp->parent = parent;
	top->link = temp;

	return;
}
StackNodeMaze* PopStack(LinkedStackMaze* head)
{
	StackNodeMaze* temp = NULL;
	//맨윗놈 가져오기
	temp = head->top;
	if (temp != NULL) {
		head->top = temp->link;
//		temp->link = NULL;
	}
	return temp;
}
StackNodeMaze* PeekStack(LinkedStackMaze* head)
{
	if (head == NULL)
		return NULL;
	return head->top;
}

