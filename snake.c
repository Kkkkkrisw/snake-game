#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

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

int main(void)
{
	srand((unsigned)time(NULL));

	initGame();
	drawGame();

	printf("\nPress any key to exit...\n");
	_getch();

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