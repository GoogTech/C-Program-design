/*
 * @Author: HuangYuhui 
 * @Date: 2019-01-29 21:06:05 
 * @Last Modified by: HuangYuhui
 * @Last Modified time: 2019-01-29 21:07:38
 */
#include "Eliminate-the-brick.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>

#define Hight 480
#define Width 640
#define Brick_num 10

// ball.
float ball_x, ball_y;
float ball_v_x, ball_v_y;
float radius;
// baffle.
int baffle_x, baffle_y; //(x,y)
int baffle_hight, baffle_width;
int baffle_left, baffle_right, baffle_top, baffle_bottom;
// brick.
//? : Determine whether the brick is exist.(1->exist.0->hide)
int i;
int isBrickExisted[Brick_num];
int brick_hight, brick_width;
int brick_left, brick_right, brick_top, brick_bottom;

//Initialize the variable.
void startup()
{
    //Initialize the ball.
    ball_x = Width / 2;
    ball_y = Hight / 2;
    ball_v_x = 1;
    ball_v_y = 1;
    radius = 20;

    //todo : Initialize the baffle.
    baffle_hight = Hight / 20;
    baffle_width = Width / 5;
    baffle_x = Width / 2;
    baffle_y = Hight - baffle_hight / 2;
    baffle_left = baffle_x - baffle_width / 2;
    baffle_right = baffle_x + baffle_width / 2;
    baffle_top = baffle_y - baffle_hight / 2;
    baffle_bottom = baffle_y + baffle_hight / 2;

    //Initialize the brick.
    brick_width = Width / Brick_num;
    brick_hight = Hight / Brick_num;
    int i;
    for (i = 0; i < Brick_num; i++)
    {
        isBrickExisted[i] = 1;
    }

    //Initialize the size of console.
    initgraph(Width, Hight);
    BeginBatchDraw();
}

//Flush the graph.
void clean()
{
    setcolor(BLACK);
    setfillcolor(BLACK);
    //Draw the circle.
    fillcircle(ball_x, ball_y, radius); //(x,y,r)
    //Draw the baffle.
    bar(baffle_left, baffle_top, baffle_right, baffle_bottom);
    //Draw the brick.
    for (i = 0; i < Brick_num; i++)
    {
        brick_left = i * brick_width;
        brick_right = brick_left + brick_width;
        brick_top = 0;
        brick_bottom = brick_hight;
        if (!isBrickExisted[i]) //Hide the brick if it's not exist.
        {
            fillrectangle(brick_left, brick_top, brick_right, brick_bottom);
        }
    }
}

//Draw the graph.
void show()
{
    setcolor(YELLOW);
    setfillcolor(GREEN);
    //Draw the circle.
    fillcircle(ball_x, ball_y, radius);
    //Draw the baffle.
    bar(baffle_left, baffle_top, baffle_right, baffle_bottom);
    //Draw the brick.
    drawBrick();

    FlushBatchDraw();
    Sleep(3);
}

//Draw the brick.
void drawBrick()
{
    for (i = 0; i < Brick_num; i++)
    {
        brick_left = i * brick_width;
        brick_right = brick_left + brick_width;
        brick_top = 0;
        brick_bottom = brick_hight;
        if (isBrickExisted[i]) //Draw the brick if it's exist.
        {
            setcolor(BLUE);
            setfillcolor(RED);
            fillrectangle(brick_left, brick_top, brick_right, brick_bottom);
        }
    }
}

//Update the position of ball.
void updateWithoutInput()
{
    //!Algorithm : it will be bounces back when the ball collides with the paddle.
    if ((ball_y + radius >= baffle_top) && (ball_y + radius < baffle_bottom - baffle_hight / 3) || (ball_y <= baffle_bottom) && (ball_y - radius > baffle_top - baffle_hight / 3))
        if ((ball_x >= baffle_left) && (ball_x < baffle_right)) //Control the ball In the length of baffle.
            ball_v_y = -ball_v_y;

    //Update the position of ball.
    ball_x = ball_x + ball_v_x;
    ball_y = ball_y + ball_v_y;

    if ((ball_x <= radius) || (ball_x >= Width - radius))
    {
        ball_v_x = -ball_v_x;
    }
    if ((ball_y <= radius) || (ball_y >= Hight - radius))
    {
        ball_v_y = -ball_v_y;
    }

    //!Algorithm : To determine if the brick was hit.
    for (i = 0; i < Brick_num; i++)
    {
        if (isBrickExisted[i])
        {
            brick_left = i * brick_width;
            brick_right = brick_left + brick_width;
            brick_bottom = brick_hight; // 0
            if ((ball_y == brick_bottom + radius) && (ball_x >= brick_left && ball_x <= brick_right))
            {
                isBrickExisted[i] = 0;
                ball_v_y = -ball_v_y;
            }
        }
    }
}

//Updata the data inputed by the user.
void updateWithInput()
{
    char input;
    //? : kbhit();
    if (kbhit()) //Determine whether inputed by the user.
    {
        input = getch();
        if (input == 'a' && baffle_left > 0)
        {
            baffle_x = baffle_x - 15;
            baffle_left = baffle_x - baffle_width / 2;
            baffle_right = baffle_x + baffle_width / 2;
        }
        if (input == 'd' && baffle_right < Width)
        {
            baffle_x = baffle_x + 15;
            baffle_left = baffle_x - baffle_width / 2;
            baffle_right = baffle_x + baffle_width / 2;
        }
        if (input == 'w' && baffle_top > 0)
        {
            baffle_y = baffle_y - 15;
            baffle_top = baffle_y - baffle_hight / 2;
            baffle_bottom = baffle_y + baffle_hight / 2;
        }
        if (input == 's' && baffle_bottom < Hight)
        {
            baffle_y = baffle_y + 15;
            baffle_top = baffle_y - baffle_hight / 2;
            baffle_bottom = baffle_y + baffle_hight / 2;
        }
    }
}

//Initialize the data when the Game is over.
void gameOver()
{
    EndBatchDraw();
    closegraph();
}
