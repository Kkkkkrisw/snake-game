#define _CRT_SECURE_NO_WARNINGS
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
int highScore;//历史最高分

void initGame(void);
void drawGame(void);
void spawnFood(void);
int isOnSnakebody(int x,int y,int test);
void readInput(void);
void updateGame(void);
int currentDelay(int nowscore);
void loadHighScore(void);
void saveHighScore(void);

int main(void)
{
    int newRecord = 0;

	srand((unsigned)time(NULL));
	
	loadHighScore();
	initGame();
	drawGame();

	while (running)
	{
		readInput();
		updateGame();
		drawGame();
		Sleep(currentDelay(score));
	}

	if (score > highScore)
	{
		highScore = score;
		newRecord = 1;
		saveHighScore();
	}

	printf("Game Over! Final score: %d    Best: %d\n", score,highScore);
	if (newRecord)
	{
		printf("New High Score!\n");
	}
	printf("Press any key to exit...\n");
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

int isOnSnakebody(int x, int y,int test)
{
	for (int i = 0; i < test; i++)
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
	} while (isOnSnakebody(foodX, foodY,length));
}

void drawGame(void)
{
	system("cls");

	printf("Snake v0.2 Score: %d  Best: %d\n\n",score,highScore);

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
			else if (isOnSnakebody(col, row,length))
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

	if (newHeadX <= 0 || newHeadX >= 19 || newHeadY <= 0 || newHeadY >= 19)
	{
		running = 0;
		return;
	}
	
	int ifeaten = 0;

	if (newHeadX == foodX && newHeadY == foodY&& length<MAX_LEN )
	{
		ifeaten = 1;
		if (isOnSnakebody(newHeadX, newHeadY,length))
		{
			running = 0;
			return;
		}
	}
	else
	{
		if (isOnSnakebody(newHeadX, newHeadY,length-1))
		{
			running = 0;
			return;
		}
	}

	if (ifeaten)
	{
		score++;
		length++;
	}

	for (int i = length - 1; i > 0; i--)
	{
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
	}

	snakeX[0] = newHeadX;
	snakeY[0] = newHeadY;

	if (ifeaten == 1)
	{
		spawnFood();
	}
}

int currentDelay(int nowscore)
{
	int delay = TICK_MS - nowscore * 10;
	if (delay >=60 )
	{
		return delay;
	}
	else
	{
		return 60;
	}
}

void loadHighScore(void)
{
	FILE* fp;
	int value=0;

	highScore = 0;

	fp = fopen("highscore.txt", "r");
	if (fp == NULL)
	{
		return;
	}

	if (fscanf(fp, "%d", &value) == 1 && value >= 0)
	{
		highScore = value;
	}

	fclose(fp);
}

void saveHighScore(void)
{
	FILE* fp;

	fp = fopen("highscore.txt", "w");
	if (fp == NULL)
	{
		printf("Warning: cannot save high score.\n");
		return;

	}

	fprintf(fp, "%d\n", highScore);
	fclose(fp);
}