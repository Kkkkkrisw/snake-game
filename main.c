#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include"snake.h"

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

	printf("Game Over! Final score: %d    Best: %d\n", score, highScore);
	if (newRecord)
	{
		printf("New High Score!\n");
	}
	printf("Press any key to exit...\n");
	_getch();

	return 0;
}