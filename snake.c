#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define HEIGHT 20
#define WIDTH 20
#define INIT_LEN 3
#define MAX_LEN 400
#define TICK_MS 150

int snakeX[MAX_LEN];//蛇身坐标x
int snakeY[MAX_LEN];//蛇身坐标y
int length;//蛇身长度
int dirx,diry;//当前移动方向
int next_dirx,next_diry;//本帧请求的下一帧移动方向
int foodX,foodY;//食物坐标
int score;//分数
int running;//是否进行游戏

void initGame(void);
void drawGame(void);
void spawnFood(void);
int isOnSnakebody(int x,int y);
void readInput(void);
void updateGame(void);

int main(void)
{
	srand((unsigned)time(NULL));

	initGame();
	drawGame();

	while (running)
	{
		readInput();
		updateGame();
		drawGame();
		Sleep(TICK_MS);
	}

	return 0;
}

void initGame(void)
{
	length = INIT_LEN;

	snakeX[0] = 10;
	snakeY[0] = 10;
	snakeX[1] = 9;
	snakeY[1] = 10;
	snakeX[2] = 8;
	snakeY[2] = 10;

	dirx = 1;
	diry = 0;

	next_dirx = 1;
	next_diry = 0;

	score = 0;
	running = 1;

	spawnFood();
}

int isOnSnakebody(int x, int y)
{
	for (int i = 0; i < length; i++)
	{
		if (snakeX[i] == x && snakeY[i] == y)
		{
			return 1;
		}
	}
	return 0;
}

void spawnFood(void)
{
	do
	{
		foodX = rand() % (WIDTH - 2) + 1;
		foodY = rand() % (HEIGHT - 2) + 1;
	} while (isOnSnakebody(foodX, foodY));
}

void drawGame(void)
{
	system("cls");
	printf("Snake v0.1 Score: %d\n\n",score);

	for (int row = 0; row < HEIGHT; row++)
	{
		for (int col = 0; col <WIDTH ; col++)
		{
			if (row == 0 || row ==HEIGHT - 1 || col == 0 || col == WIDTH  - 1)
			{
				printf("#");
			}
			else if (col== snakeX[0] && row == snakeY[0])
			{
				printf("O");
			}
			else if (isOnSnakebody(col, row))
			{
				printf("o");
			}
			else if (col== foodX && row== foodY)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void readInput(void)
{
	if (!_kbhit())
	{
		return;
	}

	int key = _getch();

	if (key == 0 || key == 224)
	{
		key = _getch();
	}
	else
	{
		return;
	}

	int indirx = 0;
	int indiry = 0;

	switch (key)
	{
	case 72: indirx = 0; indiry = -1; break;
	case 80: indirx = 0; indiry = 1; break;
	case 75: indirx = -1; indiry = 0; break;
	case 77: indirx = 1; indiry = 0; break;
	default: return;
	}

	if (indirx == -dirx && indiry == -diry)
	{
		return;
	}

	next_dirx = indirx;
	next_diry = indiry;
}

void updateGame(void)
{
	dirx = next_dirx;
	diry = next_diry;

	int newHeadX = snakeX[0] + dirx;
	int newHeadY = snakeY[0] + diry;

	for (int i = length - 1; i > 0; i--)
	{
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
	}

	snakeX[0] = newHeadX;
	snakeY[0] = newHeadY;
}