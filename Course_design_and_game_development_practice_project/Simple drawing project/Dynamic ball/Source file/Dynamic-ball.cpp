/*
 * @Author: HuangYuhui 
 * @Date: 2019-01-26 20:15:43 
 * @Last Modified by:   HuangYuhui 
 * @Last Modified time: 2019-01-26 20:15:43 
 */

#include <graphics.h>
#include <conio.h>
#define Hight 480
#define Width 640
#define BallNum 1000

/*
 * Declare the variable.
 */
float ball_x[BallNum], ball_y[BallNum];
float ball_v_x[BallNum], ball_v_y[BallNum];
float radius = 5;
int i, j;

/*
 * Test the program.
 */
int main(int argc, char const *argv[])
{
    //Initialize the size of console.
    initgraph(Width, Hight);

    //Initialize the position of ball.[ radius:(x,y) ]
    for (i = 0; i < BallNum; i++)
    {
        ball_x[i] = rand() % int(Width - 4 * radius) + 2 * radius;
        ball_y[i] = rand() % int(Hight - 4 * radius) + 2 * radius;
        ball_v_x[i] = (rand() % 2) * 2 - 1; // 1 / -1
        ball_v_y[i] = (rand() % 2) * 2 - 1;
    }

    //? Prevent the screen from flashing.
    BeginBatchDraw();

    //Draw the dynamic ball.
    while (1)
    {
        //Draw the ball.(Hide)
        setcolor(BLACK);
        setfillcolor(BLACK);
        for (i = 0; i < BallNum; i++)
        {
            //? void fillcircle(int x,int y,int radius);
            fillcircle(ball_x[i], ball_y[i], radius);
        }

        //Update the position of ball.
        for (i = 0; i < BallNum; i++)
        {
            ball_x[i] = ball_x[i] + ball_v_x[i];
            ball_y[i] = ball_y[i] + ball_v_y[i];
            //If the ball out of the border.Take it return.
            if (ball_x[i] < radius)
            {
                ball_x[i] = radius;
            }
            if (ball_y[i] < radius)
            {
                ball_y[i] = radius;
            }
            if (ball_x[i] > Width - radius)
            {
                ball_x[i] = Width - radius;
            }
            if (ball_y[i] > Hight - radius)
            {
                ball_y[i] = Hight - radius;
            }
        }

        /**
         * ? The dynamic position of ball.
		 * todo : ball_x<=radius : It's will be rebounded when the ball out of the border.
		 * todo : ball_x>=Width-radius : Control the ball not out of the border.
		 */
        for (i = 0; i < BallNum; i++)
        {
            if ((ball_x[i] <= radius) || (ball_x[i] >= Width - radius)) //left and right.
            {
                ball_v_x[i] = -ball_v_x[i];
            }
            if ((ball_y[i] <= radius) || (ball_y[i] >= Hight - radius)) //top and below.
            {
                ball_v_y[i] = -ball_v_y[i];
            }
        }

        //! Record the minimum distance and index of each ball.
        float minDistance_index[BallNum][2];
        for (i = 0; i < BallNum; i++)
        {
            minDistance_index[i][0] = 9999999;
            minDistance_index[i][1] = -1;
        }

        //todo : Get the distance squared of each ball.
        //!Algorithm : so simple ~
        for (i = 0; i < BallNum; i++)
        {
            for (j = 0; j < BallNum; j++)
            {
                if (i != j) //Except for yourself.
                {
                    float distance;
                    distance = ((ball_x[i] - ball_x[j]) * (ball_x[i] - ball_x[j]) + (ball_y[i] - ball_y[j]) * (ball_y[i] - ball_y[j]));
                    if (distance < minDistance_index[i][0])
                    {
                        minDistance_index[i][0] = distance;
                        minDistance_index[i][1] = j;
                    }
                }
            }
        }

        //todo : Determine whether the ball is colliding.
        //!Algorithm : so cool ~
        for (i = 0; i < BallNum; i++)
        {
            //? 4*radius*radius :
            if (minDistance_index[i][0] <= 4 * radius * radius)
            {
                j = minDistance_index[i][1];
                //Exchange speed.
                int temp;
                temp = ball_v_x[i];
                ball_v_x[i] = ball_v_x[j];
                ball_v_x[j] = temp;

                temp = ball_v_y[i];
                ball_v_y[i] = ball_v_y[j];
                ball_v_y[j] = temp;

                //?
                minDistance_index[j][0] = 999999999;
                minDistance_index[j][1] = -1;
            }
        }

        //Draw the ball.
        setcolor(YELLOW);
        setfillcolor(GREEN);
        for (i = 0; i < BallNum; i++)
        {
            fillcircle(ball_x[i], ball_y[i], radius);
        }

        //? Prevent the screen from flashing.
        FlushBatchDraw();

        //Sleep
        Sleep(3);
    }
    //End the draw.
    EndBatchDraw();
    //Release the resource.
    closegraph();

    _getch();
    return 0;
}
