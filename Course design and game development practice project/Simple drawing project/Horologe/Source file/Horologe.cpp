/*
 * @Author: HuangYuhui 
 * @Date: 2019-01-21 20:16:52 
 * @Last Modified by: HuangYuhui
 * @Last Modified time: 2019-01-21 20:47:54
 */

#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <Windows.h> //gotoxy(int x,int y);

#define Hight 480
#define Width 640
#define PI 3.14159

#pragma comment(lib, "Winmm.lib") //mciSendString();

/*
 * Declare the variable.
 */
//Declare the center positioin of console.
int center_x, center_y;
//Declare the length of pointer.
int secondLength;
int minuteLength;
int hourLength;
//Declare the position of pointer.
int secondEnd_x, secondEnd_y;
int minuteEnd_x, minuteEnd_y;
int hourEnd_x, hourEnd_y;
//Declare the dynamic variable.
float secondAngle;
float minuteAngle;
float hourAngle;

/*
 * Method : flush the console.
 */
static void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

/*
 * Method : play the background music.
 */
static void playMusic()
{
    mciSendStringA("open xxx.mp3 alias bkmusic", NULL, 0, NULL);
    mciSendStringA("play bkmusic repeat", NULL, 0, NULL);
}

/*
 * Method : Draw the scale of horologe.
 */
static void drawScale(int center_x, int center_y)
{
    int x, y, i;
    for (i = 0; i < 60; i++)
    {
        x = center_x + int(Width / 4.3 * sin(PI * 2 * i / 60));
        y = center_y + int(Width / 4.3 * cos(PI * 2 * i / 60));

        if (i % 15 == 0)
        {
            setfillcolor(CYAN);
            bar(x - 5, y - 5, x + 5, y + 5); //Hour dial.
        }
        else if (i % 5 == 0)
        {
            setcolor(BROWN);
            circle(x, y, 3); //Minute dial.
        }
        else
        {
            putpixel(x, y, BLACK); //Second dial.
        }
    }
}

/*
 * Test the program.
 */
int main()
{
    //Initialize the size of console.
    initgraph(Width, Hight);
    //Initialize the background.
    setbkcolor(LIGHTGRAY);
    //Clear the console with the background.
    cleardevice();
    //Play the music.
    playMusic();

    //Get the center position.
    center_x = Width / 2;
    center_y = Hight / 2;

    //Initialize the length of pointer.
    secondLength = Width / 5;
    minuteLength = Width / 6;
    hourLength = Width / 7;

    //Store the current second.
    SYSTEMTIME current_time;

    //? Begin to draw.
    BeginBatchDraw();

    while (1)
    {
        //Scheme 1 : Clear the console.
        //gotoxy(0,0);

        //Scheme 2 : Clear the console.
        system("cls");

        //Draw a circlie in the center.
        setcolor(MAGENTA);
        circle(center_x, center_y, 6);

        //Draw the dial of horologe.
        setlinestyle(PS_SOLID, 3);
        setcolor(GREEN);
        circle(center_x, center_y, Width / 4);

        //! Algorithm : Draw the scale of horologe.
        drawScale(center_x, center_y);

        //Write the introduction.
        TCHAR introduction[] = _T("春");
        outtextxy(center_x - 8, center_y + Width / 6, introduction);

        /**
         * ! Algorithm : Draw the dynamic pointer of horologe.
         */
        //Get the current time.
        GetLocalTime(&current_time);
        //Dynamic change by the current second.
        secondAngle = current_time.wSecond * 2 * PI / 60;
        minuteAngle = current_time.wMinute * 2 * PI / 60;
        hourAngle = current_time.wHour * 2 * PI / 12;
        //todo : Algorithm : Initialize the dynamic horologe by the local time.
        secondEnd_x = center_x + secondLength * sin(secondAngle);
        secondEnd_y = center_y - secondLength * cos(secondAngle);
        minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
        minuteEnd_y = center_y - minuteLength * cos(minuteAngle);
        hourEnd_x = center_x + hourLength * sin(hourAngle);
        hourEnd_y = center_y - hourLength * cos(hourAngle);
        //Draw the pointer.
        setlinestyle(PS_SOLID, 2);
        setcolor(WHITE);
        line(center_x, center_y, secondEnd_x, secondEnd_y);
        setlinestyle(PS_SOLID, 4);
        setcolor(BLUE);
        line(center_x, center_y, minuteEnd_x, minuteEnd_y);
        setlinestyle(PS_SOLID, 6);
        setcolor(RED);
        line(center_x, center_y, hourEnd_x, hourEnd_y);

        Sleep(10);

        //? Complete unfinished drawing tasks.
        FlushBatchDraw();

        //Hide the pointer.
        setcolor(LIGHTGRAY);
        setlinestyle(PS_SOLID, 2);
        line(center_x, center_y, secondEnd_x, secondEnd_y);
        setlinestyle(PS_SOLID, 4);
        line(center_x, center_y, minuteEnd_x, secondEnd_y);
        setlinestyle(PS_SOLID, 6);
        line(center_x, center_y, hourEnd_x, hourEnd_y);
    }

    getch();
    closegraph();
    return 0;
}