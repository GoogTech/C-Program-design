/*
 * @Author: HuangYuhui 
 * @Date: 2019-02-04 19:41:36 
 * @Last Modified by:   HuangYuhui 
 * @Last Modified time: 2019-02-04 19:41:36 
 */

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#pragma comment(lib, "Winmm.lib") //Include the Window Multimedia API.

/**
 * TODO : Declare the variable.
 */
int flag = 1; //Determine whether the game is over.
int score = 0;
int bird_x, bird_y;
IMAGE img_beforegame, img_gameover, img_bk, img_bird, img_bird_bk, img_bar_up1, img_bar_up2, img_bar_down1, img_bar_down2, img_score_1[10], img_score_2[10];

//? : 柱子的左下点的坐标
int pillar_x1, pillar_y1;
int pillar_x2, pillar_y2;

/**
 * TODO : Declare the method.
 */
static void beginOrExit();
static void startup();
static void show();
static void updateWithoutInput();
static void updateWithInput();
static void printPillar();
static void printScore();
static int judgement();
static void gameover();

/**
 * TODO : Test the program. 
 */
int main()
{
    beginOrExit();
    startup();
    while (flag)
    {
        show();
        updateWithoutInput();
        updateWithInput();
    }
    gameover();

    getch();
    return 0;
}

/**
 * TODO : Defined the method.
 */
//Determine whether play the game.
static void beginOrExit()
{
    //Initialize the size of console.
    initgraph(350, 526);
    //TODO : 获取窗口句柄
    HWND hwnd = GetHWnd();
    //Set the title of console.
    SetWindowTextA(hwnd, "春");
    loadimage(&img_beforegame, _T("\\Resource\\BeginOrExit_2.jpg"));
    putimage(0, 0, &img_beforegame);

    Sleep(3000);
    getch();
}

//Initialize the game.
static void startup()
{
    //Initialize the size of console.
    initgraph(350, 524);
    //Initialize the position of bird.
    bird_x = 155;
    bird_y = 200;
    //Initialize the first pillar.
    pillar_x1 = 350;
    pillar_y1 = rand() % 210 - 555;

    BeginBatchDraw();

    //Background picture
    loadimage(&img_bk, _T("Resource\\background-2.jpg"));
    //Bird
    loadimage(&img_bird, _T("Resource\\bird2.jpg"));
    loadimage(&img_bird_bk, _T("Resource\\bird1.jpg"));
    //Score
    loadimage(&img_score_1[0], _T("Resource\\0_1.jpg"));
    loadimage(&img_score_2[0], _T("Resource\\0_2.jpg"));
    loadimage(&img_score_1[1], _T("Resource\\1_1.jpg"));
    loadimage(&img_score_2[1], _T("Resource\\1_2.jpg"));
    loadimage(&img_score_1[2], _T("Resource\\2_1.jpg"));
    loadimage(&img_score_2[2], _T("Resource\\2_2.jpg"));
    loadimage(&img_score_1[3], _T("Resource\\3_1.jpg"));
    loadimage(&img_score_2[3], _T("Resource\\3_2.jpg"));
    loadimage(&img_score_1[4], _T("Resource\\4_1.jpg"));
    loadimage(&img_score_2[4], _T("Resource\\4_2.jpg"));
    loadimage(&img_score_1[5], _T("Resource\\5_1.jpg"));
    loadimage(&img_score_2[5], _T("Resource\\5_2.jpg"));
    loadimage(&img_score_1[6], _T("Resource\\6_1.jpg"));
    loadimage(&img_score_2[6], _T("Resource\\6_2.jpg"));
    loadimage(&img_score_1[7], _T("Resource\\7_1.jpg"));
    loadimage(&img_score_2[7], _T("Resource\\7_2.jpg"));
    loadimage(&img_score_1[8], _T("Resource\\8_1.jpg"));
    loadimage(&img_score_2[8], _T("Resource\\8_2.jpg"));
    loadimage(&img_score_1[9], _T("Resource\\9_1.jpg"));
    loadimage(&img_score_2[9], _T("Resource\\9_2.jpg"));
    //Above bar
    loadimage(&img_bar_up1, _T("Resource\\bar_up1.gif"));
    loadimage(&img_bar_up2, _T("Resource\\bar_up2.gif"));
    //Below bar
    loadimage(&img_bar_down1, _T("Resource\\bar_down1.gif"));
    loadimage(&img_bar_down2, _T("Resource\\bar_down2.gif"));

    //Open the background music
    mciSendStringA("open D:\\MySong\\background-.mp3 alias bkmusic", NULL, 0, NULL);
    mciSendStringA("play bkmusic repeat", NULL, 0, NULL);
}

//Show the game.
static void show()
{
    //Background
    putimage(0, 0, &img_bk);
    //Bird
    putimage(bird_x, bird_y, &img_bird_bk, NOTSRCERASE);
    putimage(bird_x, bird_y, &img_bird, SRCINVERT);
    //Score
    putimage(250, 50, &img_score_1[0], NOTSRCERASE);
    putimage(250, 50, &img_score_2[0], SRCINVERT);

    //TODO : Print the pillar.
    printPillar();
    //TODO : Print the score.
    printScore();

    FlushBatchDraw();
    Sleep(50);
}

//Automatic updates.
static void updateWithoutInput()
{
    if (bird_y < 580)
    {
        bird_y = bird_y + 5;
    }
    //TODO : Determin whether the game is over.
    flag = judgement();
}

//Inputed by the user.
static void updateWithInput()
{
    char input;
    if (kbhit())
    {
        input = getch();
        if (input == ' ' && bird_y > 20)
        {
            bird_y = bird_y - 60;
        }

        mciSendStringA("close jpmusic", NULL, 0, NULL); //Close the last music firstly.
        mciSendStringA("open D:\\MySong\\Jump.mp3 alias jpmusic", NULL, 0, NULL);
        mciSendStringA("play jpmusic", NULL, 0, NULL); //Play the music only once.
    }
}

//! Algorithm : Move the pillar.
static void printPillar()
{
    Sleep(6);
    if (pillar_x1 > 0) //Draw the two pillar.
    {
        //TODO : 三光栅操作
        putimage(pillar_x1, pillar_y1, &img_bar_up1, NOTSRCERASE);
        putimage(pillar_x1, pillar_y1, &img_bar_up2, SRCINVERT);
        putimage(pillar_x1, pillar_y1 + 750, &img_bar_up1, NOTSRCERASE);
        putimage(pillar_x1, pillar_y1 + 750, &img_bar_up2, SRCINVERT);

        putimage(pillar_x2, pillar_y2, &img_bar_down2, NOTSRCERASE);
        putimage(pillar_x2, pillar_y2, &img_bar_down1, SRCINVERT);
        putimage(pillar_x2, pillar_y2 + 750, &img_bar_down2, NOTSRCERASE);
        putimage(pillar_x2, pillar_y2 + 750, &img_bar_down1, SRCINVERT);

        //Control the speed of moving.
        pillar_x1 = pillar_x1 - 5;
        pillar_x2 = pillar_x2 - 5;
    }

    //Create the new paillar.
    if (pillar_x1 == 0)
    {
        pillar_x1 = 350;
        //TODO : Dynamic change.
        pillar_y1 = rand() % 350 - 555; //-205

        putimage(pillar_x1, pillar_y1, &img_bar_up2, NOTSRCERASE);
        putimage(pillar_x1, pillar_y1, &img_bar_up1, SRCINVERT);

        putimage(pillar_x2, pillar_y2 + 750, &img_bar_down2, NOTSRCERASE);
        putimage(pillar_x2, pillar_y2 + 750, &img_bar_down1, SRCINVERT);

        pillar_x1 = pillar_x1 - 5;
        pillar_x2 = pillar_x2 - 5;
    }
}

//Print and update the score.
static void printScore()
{
    IMAGE *img_score_11[6], *img_score_22[6];

    int he, weishu = 1, i = 0, current_score = score;
    if (current_score == 0)
    {
        putimage(250, 50, &img_score_1[0], NOTSRCERASE);
        putimage(250, 50, &img_score_2[0], SRCINVERT);
    }
    while (current_score > 0)
    {
        he = current_score % 10;

        img_score_11[i] = &img_score_1[he];
        img_score_22[i] = &img_score_2[he];
        putimage(300 - 50 * weishu, 50, img_score_11[i], NOTSRCERASE);
        putimage(300 - 50 * weishu, 50, img_score_22[i], SRCINVERT);

        current_score /= 10;

        i++;
        weishu++;
    }
}

/**
 * ! Algorithm : Judgement
 * ? Dynamic change : pillar_y1
 * TODO : Attention bird_x : 155 
 */
static int judgement()
{
    //TODO : The width of pillar.
    if ((pillar_x1 >= 0 && pillar_x1 <= 155))
    {
        //TODO : [ 鸟撞到管道口的上下 ]
        if ((bird_y > (pillar_y1 + 576) && bird_y < (pillar_y1 + 600)) || ((bird_y > (pillar_y1 + 726)) && bird_y < (pillar_y1 + 750)))
        {
            //TODO : in 576->600 / 726->750
            return 0;
        }
        //TODO : [ 鸟撞到管道的墙壁 ]
        if (!(bird_y > (pillar_y1 + 600) && bird_y < (pillar_y1 + 726)))
        {
            //TODO : not in 600->726
            return 0;
        }
    }
    //TODO : Get the score.
    if (pillar_x1 == 10)
    {
        score++;
    }
}

//Game over.
static void gameover()
{
    //Initialize the size of console.
    initgraph(350, 260);
    //Initialize the background picture.
    loadimage(&img_gameover, _T("Resource\\GameOver.jpg"));
    putimage(0, 0, &img_gameover);

    //close the background music.
    mciSendStringA("close bkmusic", NULL, 0, NULL);

    EndBatchDraw();
    getch();
    closegraph();
}
