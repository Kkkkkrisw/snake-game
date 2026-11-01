#ifndef SNAKE_H
#define SNAKE_H

#define HEIGHT 20
#define WIDTH 20
#define INIT_LEN 3
#define MAX_LEN 400
#define TICK_MS 150

extern int snakeX[MAX_LEN];//蛇身坐标x
extern int snakeY[MAX_LEN];//蛇身坐标y
extern int length;//蛇身长度
extern int dirx, diry;//当前移动方向
extern int next_dirx, next_diry;//本帧请求的下一帧移动方向
extern int foodX, foodY;//食物坐标
extern int score;//分数
extern int running;//是否进行游戏
extern int highScore;//历史最高分

void initGame(void);
void drawGame(void);
void spawnFood(void);
int isOnSnakebody(int x, int y, int test);
void readInput(void);
void updateGame(void);
int currentDelay(int nowscore);
void loadHighScore(void);
void saveHighScore(void);
void initConsole(void);
void moveCursorToTop(void);
void restoreConsole(void);

#endif
