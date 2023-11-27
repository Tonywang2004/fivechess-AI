#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BOARD_SIZE 12
#define EMPTY 0
#define BLACK 1
#define WHITE 2
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define START "START"
#define PLACE "PLACE"
#define TURN "TURN"
#define END "END"
struct Command
{
    int x;
    int y;
};//输入命令 
char board[BOARD_SIZE][BOARD_SIZE] = {0};//棋盘 
int myFlag;//我的落子 
int enemyFlag;//对方落子 
void debug(const char *str)
{
    printf("DEBUG %s\n", str);
    fflush(stdout);
}
BOOL isInBound(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}//判断是否在棋盘上 
void place(struct Command cmd)
{
    board[cmd.x][cmd.y] = enemyFlag;
}
void initAI(int me)
{
    enemyFlag = 3 - me;
}
void start(int flag)
{
    memset(board, 0, sizeof(board));
    int middlePlace = BOARD_SIZE / 2;
    board[middlePlace - 1][middlePlace - 1] = BLACK;
    board[middlePlace][middlePlace] = BLACK;
    board[middlePlace - 1][middlePlace] = WHITE;
    board[middlePlace][middlePlace - 1] = WHITE;
    initAI(flag);
}
void turn()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY)
            {
                printf("%d %d", i, j);
                printf("\n");
                fflush(stdout);
                board[i][j] = myFlag;
                return;
            }
        }
    }
}
void end(int x)
{
    exit(0);
}

void loop()
{
    char tag[10] = {0};
    struct Command command =
        {
            .x = 0,
            .y = 0,
        };
    int status;
    while (TRUE)
    {
        memset(tag, 0, sizeof(tag));
        scanf("%s", tag);
        if (strcmp(tag, START) == 0)
        {
            scanf("%d", &myFlag);
            start(myFlag);
            printf("OK\n");
            fflush(stdout);
        }
        else if (strcmp(tag, PLACE) == 0)
        {
            scanf("%d %d", &command.x, &command.y);
            place(command);
        }
        else if (strcmp(tag, TURN) == 0)
        {
            turn();
        }
        else if (strcmp(tag, END) == 0)
        {
            scanf("%d", &status);
            end(status);
        }
    }
}
int main(int argc, char *argv[])
{
    loop();
    return 0;
}
