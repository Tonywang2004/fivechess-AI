#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
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
int mymax(int a, int b)
{
    return a > b ? a : b;
}//�Լ�д�ıȽ����ֵ����
int mymin(int a, int b)
{
    return a < b ? a : b;
}//�Լ�д�ıȽ���Сֵ����
//ģʽ
int myFlag;//�ҵ����� 
int enemyFlag;//�Է����� 
struct Pattern {
    char pattern[10];
    int score;
};
//��һ���Ƚ��㷨��ͬ����result��ֵ�Ƚ�result_enenmy�ķ�
struct Pattern patterns[30] = {
    { "11111",  500000 },
    { "011110", 43200 },
    { "011100", 730 },
    { "001110", 730 },
    { "011010", 710 },
    { "010110", 710 },
    { "211110", 750 },
    { "011112", 750 },
    { "11011",  750 },
    { "10111",  750 },
    { "11101",  750 },
    { "001100", 120 },
    { "001010", 120 },
    { "010100", 120 },
    { "000100", 20 },
    { "001000", 20 },
};
//��3��720��710�����ģ�750��720��710����΢������������������
int dou = 0;//�Ƿ���˫�����ȵȽ�������
int dou1 = 0; //�Ƿ���˫�����ȵȽ�������
struct node {
    struct node* next[3];
    int isend;
    int sco;
};//tree��㣬�ֵ���
struct AI {
    struct node* head;
};
struct AI ac;//����һ��ͷ���
void delnode(struct node* cur);
struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    if (data != 0)
        newNode->isend = 1;
    else
        newNode->isend = 0;
    newNode->sco = data;
    newNode->next[0] = NULL;
    newNode->next[1] = NULL;
    newNode->next[2] = NULL;
    return newNode;
}//������
void destroyAI(struct AI* ai) {
    delnode(ai->head->next[0]);
    delnode(ai->head->next[1]);
    free(ai->head->next[0]);
    free(ai->head->next[1]);
    free(ai->head);
    free(ai);
}//ɾ�����
void treebuild() {
    for (int i = 0; i < 20; i++)
    {
        struct node* p = ac.head;
        int pattern_size = sizeof(patterns[i].pattern) - 1;
        for (int j = 0; patterns[i].pattern[j] != '\0'; j++)
        {
            int index = patterns[i].pattern[j] - '0';
            //printf("%d", index);
            if (p->next[index] == NULL) {
                p->next[index] = createNode(0);
                //printf("ok");
            }//�����һ�ڵ�Ϊ�գ��������
            if (patterns[i].pattern[j + 1] == '\0') {
                if (p->next[index] != NULL)
                {
                    p->next[index]->isend = 1;
                    p->next[index]->sco = patterns[i].score;
                }
            }//�ж����Ϊ0���ͽ�������ֵisend��score
            else
            {
                p = p->next[index];
            }//����Ϊ0������ת����һ��
        }
        //printf("\n");
    }
}//������
void delnode(struct node* cur) {
    for (int i = 0; i < 3; ++i)
    {
        if (cur->next[i] == 0) continue;
        delnode(cur);
        free(cur->next[i]);
        cur->next[i] = 0;
    }
}
int ACSearch(const char x[], int role) {
    int result[30] = { 0 };
    int result1[30] = { 0 };
    int now = 0;
    int now1 = 0;
    int lenth = 0;
    //printf("%s  ", x);
    int i;
    for (i = 0; x[i] != '\0'; i++)
    {
        struct node* p = ac.head;
        for (int j = 0; x[i + j] != '\0'; j++) {
            int index = (int)x[i + j] - '0';
            //printf("%d", index);
            if (p->isend == 0)
                if (p->next[index] != NULL)
                {
                    p = p->next[index];
                }
                else
                    break;
            else if (p->isend == 1) {
                if (p->sco > 700 && role == enemyFlag)
                {
                    // printf("%s\n", x);
                    dou++;
                }
                i = i + j ;
                result[now] = p->sco;
                now++;
                break;
            }
        }
        //printf("\n");
    }//�����������������Ϊpattern�������result����洢���������ں���Ĳ����н������
    int re = 0;
    for (int j = 0; j < 30; j++)
        re += result[j];
    for (i = 0; x[i] != '\0'; i++)
        lenth = i;
    for (i=lenth; i>=0; i--)
    {
        struct node* p = ac.head;
        for (int j = 0; i - j >=0; j++) {
            int index = (int)x[i - j] - '0';
            //printf("%d", index);
            if (p->isend == 0)
                if (p->next[index] != NULL)
                {
                    p = p->next[index];
                }
                else
                    break;
            else if (p->isend == 1) {
                if (p->sco > 700 && role == enemyFlag)
                {
                    dou1++;
                }
                i = i - j;
                result1[now1] = p->sco;
                now1++;
                break;
            }
        }
        //printf("\n");
    }
    //���з������������Ϊpattern�������result����洢���������ں���Ĳ����н������
    int re1 = 0;
    for (int j = 0; j < 30; j++)
        re1 += result1[j];
    return mymax(re,re1);//����ֵΪ�����������÷ֵ����ֵ��Ϊ�������ĵ÷�
}
//������
struct Command
{
    int x;
    int y;
};//�������� 
struct Commandandscore {
    struct Command command;
    int score;
};
char board[BOARD_SIZE][BOARD_SIZE] = { 0 };//���� 
//����λ�����֣�����board�ǵ�ǰ���̣�p��λ�ã�role�����ֽ�ɫ������role��Human��������������֣�����role��computer���Ƕ��ڵ�������
int evaluatePoint(const char board[BOARD_SIZE][BOARD_SIZE], struct Command p, int color) {
    int result, result_enemy = 0;
    int i, j;
    int role;
    result = 0;
    role = enemyFlag;
    char lines[4][30];//����
    memset(lines, '\0', sizeof(lines));
    char lines1[4][30];//�Լ�
    memset(lines1, '\0', sizeof(lines1));
    for (i = mymax(0, p.x - 5); i < mymin(BOARD_SIZE, p.x + 6); i++) {
        if (i != p.x) {
            strcat(lines[0], (board[i][p.y] == role ? "1" : board[i][p.y] == 0 ? "0" : "2"));
            strcat(lines1[0], (board[i][p.y] == role ? "2" : board[i][p.y] == 0 ? "0" : "1"));
        }
        else {
            strcat(lines[0], ("1"));
            strcat(lines1[0], ("1"));
        }
    }//��
    for (i = mymax(0, p.y - 5); i < mymin(BOARD_SIZE, p.y + 6); i++) {
        if (i != p.y) {
            strcat(lines[1], (board[p.x][i] == role ? "1" : board[p.x][i] == 0 ? "0" : "2"));
            strcat(lines1[1], (board[p.x][i] == role ? "2" : board[p.x][i] == 0 ? "0" : "1"));
        }
        else {
            strcat(lines[1], ("1"));
            strcat(lines1[1], ("1"));
        }
    }//��
    for (i = p.x - mymin(mymin(p.x, p.y), 5), j = p.y - mymin(mymin(p.x, p.y), 5); i < mymin(BOARD_SIZE, p.x + 6) && j < mymin(BOARD_SIZE, p.y + 6); i++, j++) {
        if (i != p.x) {
            strcat(lines[2], (board[i][j] == role ? "1" : board[i][j] == 0 ? "0" : "2"));
            strcat(lines1[2], (board[i][j] == role ? "2" : board[i][j] == 0 ? "0" : "1"));
        }
        else {
            strcat(lines[2], ("1"));
            strcat(lines1[2], ("1"));
        }
    }//б��
    for (i = p.x + mymin(mymin(p.y, BOARD_SIZE - 1 - p.x), 5), j = p.y - mymin(mymin(p.y, BOARD_SIZE - 1 - p.x), 5); i >= mymax(0, p.x - 5) && j < mymin(BOARD_SIZE, p.y + 6); i--, j++) {
        if (i != p.x) {
            strcat(lines[3], (board[i][j] == role ? "1" : board[i][j] == 0 ? "0" : "2"));
            strcat(lines1[3], (board[i][j] == role ? "2" : board[i][j] == 0 ? "0" : "1"));
        }
        else {
            strcat(lines[3], ("1"));
            strcat(lines1[3], ("1"));
        }
    }
    //б��
    //printf("%s\n", lines[1]);
    for (i = 0; i < 4; i++) {
        strcat(lines[i], "2");
        int tmp = ACSearch(lines[i], enemyFlag);
        result_enemy += tmp;
        if (dou >= 2) {
            result_enemy += 10000;
            dou = 0;
        }
        if (dou1 >= 2) {
            result_enemy += 10000;
            dou1 = 0;
        }
        strcat(lines1[i], "2");
        int tmp1 = ACSearch(lines1[i], myFlag);
        result += tmp1;
    }
    dou = 0;//�ж��Ƿ�˫�� ����
    dou1 = 0;//�ж��Ƿ�˫�� ����
    if (result >= 500000)
        return 50000000;
    if (color == enemyFlag)
        return result_enemy;
    if (color == -1)
        return result;
    if (result >= result_enemy)
        return result + 1;
    else
        return result_enemy;
}//���ݲ������ز�ͬ��ֵ
int alpha_beta(int depth, int alpha, int beta, int color, struct Command p) {
    if (depth == 0) {
        return evaluatePoint(board, p, color);
    }
    return evaluatePoint(board, p, color);
}//�������˵ļ�֦��Ŀǰ��ֱ��������ֺ���
void showboard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%d", (int)board[i][j]);
        }
        printf("\n");
    }
}//�����ã�չʾ�����ӵĺ���
void debug(const char* str)
{
    printf("DEBUG %s\n", str);
    fflush(stdout);
}
BOOL isInBound(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE&& y >= 0 && y < BOARD_SIZE;
}//�ж��Ƿ��������� 
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
    board[middlePlace - 1][middlePlace - 1] = 3 - BLACK;
    board[middlePlace][middlePlace] = 3 - BLACK;
    board[middlePlace - 1][middlePlace] = 3 - WHITE;
    board[middlePlace][middlePlace - 1] = 3 - WHITE;
    initAI(flag);
}
void turn()
{
    int i_real = 0, j_real = 0, cur_point = 0;
    struct Commandandscore p;
    p.command.x = 0;
    p.command.y = 0;
    p.score = -1;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY)
            {
                struct Command p_mid = { i,j };
                p.score = alpha_beta(0, 0, 0, myFlag, p_mid);
                if (p.score > cur_point)
                {
                    cur_point = p.score;
                    i_real = p_mid.x, j_real = p_mid.y;
                }
                else if (p.score == cur_point)
                {
                    struct Command real = { i_real,j_real };
                    if (alpha_beta(0, 0, 0, enemyFlag, p_mid) > alpha_beta(0, 0, 0, enemyFlag, real))
                    {
                        cur_point = p.score;
                        i_real = p_mid.x, j_real = p_mid.y;
                    }
                    else if (alpha_beta(0, 0, 0, enemyFlag, p_mid) == alpha_beta(0, 0, 0, enemyFlag, real))
                    {
                        if (alpha_beta(0, 0, 0, -1, p_mid) > alpha_beta(0, 0, 0, -1, real)) {
                            cur_point = p.score;
                            i_real = p_mid.x, j_real = p_mid.y;
                        }
                    }
                }
            }
        }
    }
    //�������ҵ������������ĵ�����������������ͬ���ж����ӶԶ������ֵĸߵ�
    printf("%d %d", i_real, j_real);
    printf("\n");
    fflush(stdout);
    board[i_real][j_real] = myFlag;
    //showboard();
    return;
}
void end(int x)
{
    exit(0);
}

void loop()
{
    char tag[10] = { 0 };
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
int main(int argc, char* argv[])
{
    ac.head = createNode(0);
    treebuild();//�ȹ�����
    loop();
    return 0;
}