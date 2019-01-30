/*
 * @Author: HuangYuhui 
 * @Date: 2019-01-29 15:08:26 
 * @Last Modified by: HuangYuhui
 * @Last Modified time: 2019-01-29 16:56:16
 */
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h> //getch();
#define N 15
#define M 3 //checkpoint

/*
 * Declare the variable.
 */
//The position of myself.
int x, y;
//The level of game.
int level = 0;
//Demtermine whether the game is over.
int game_over;

//Draw the map by the array.
int map[M][N][N] = {
    //First checkpoint.
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {1, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
     {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
     {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
     {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
     {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    //Second checkpoint.
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 3, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
    //Third checkpoint.
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
     {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
     {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0},
     {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
     {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
     {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0}}};

/*
 * Declare the method.
 */
//TODO : Clear the console.Better than:system("CLS");
void gotoxy();
//TODO : Hide the cursor.
void HideCursor();
//User tip.
void menuTip();
//Draw the map of maze.
void printMap();
//Find the position of myself.
void findMyself();
//Move to find the exit.
int move();
//Move
int Up();
int Down();
int Right();
int Left();

/*
 * Test the project.
 */
int main(int argc, char const *argv[])
{
    HideCursor();
    menuTip();
    while (1)
    {
        game_over = move();
        if (game_over == 1)
        {
            MessageBox(0, TEXT("EXIT ?"), TEXT("USER TIP"), MB_OK | MB_ICONASTERISK);
            return 0;
        }
    }
    system("pause");
    return 0;
}

/*
 * Defined the method.
 */
//Clear the console.
void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

//Hide the cursor.
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//User tip
void menuTip()
{
    char select[10];
    printf("###### Welcome play the game of maze ######\n");
    printf("\nPlease the checkpoint : ");
    while (1)
    {
        scanf("%s", select);
        system("CLS"); //Clear the user tip.
        if (strlen(select) > 1)
        {
            printf("Error : Please enter the level of checkpoint !\n");
        }
        else
        {
            if ('1' == select[0])
            {
                level = 0;
                break;
            }
            else if ('2' == select[0])
            {
                level = 1;
                break;
            }
            else if ('3' == select[0])
            {
                level = 2;
                break;
            }
            else
            {
                printf("The checkpoint(1-3) !\n");
            }
        }
    }
}

//Draw the map of maze.
void printMap()
{
    int i, j;
    //TODO : Clear the console.Better than : system("cls") !
    gotoxy(0, 0);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (map[level][i][j] == 0)
            {
                printf("▇"); //Brick
            }
            else if (map[level][i][j] == 1)
            {
                printf("  "); //Road
            }
            else if (map[level][i][j] == 3)
            {
                printf("◎"); //You
            }
            else if (map[level][i][j] == 4)
            {
                printf("★"); //Exit
            }
        }
        printf("\n");
    }
}

//Find the position of myself.
void findMyself()
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (map[level][i][j] == 3)
            {
                x = i;
                y = j;
                break;
            }
        }
    }
}

//Find the exit of map.
int move()
{
    //Detemin whether the game is over.
    int flag;
    while (1)
    {
        flag = 0;
        //! Draw the map of maze.
        printMap();
        //! Find the position of myself.
        findMyself();
        switch (getch())
        {
        case 'w':
            flag = Up();
            break;
        case 's':
            flag = Down();
            break;
        case 'a':
            flag = Left();
            break;
        case 'd':
            flag = Right();
            break;
        case 27: //ASCII : Esc
            return 1;
        default:
            break;
        }

        //Detemin whether the game is over.
        if (flag == 1)
        {
            //Determin whether the checkpoint is last.
            if (level == M - 1)
            {
                system("CLS");
                printf("\n（づ￣3￣）づ╭❤～");
                //? Message();
                MessageBox(0, TEXT("ALL CHECKPOINT HAS BEEN FINSHED !"), TEXT("USER TIP"), MB_OK | MB_ICONASTERISK);
                return 1;
            }
            else
            {
                MessageBox(0, TEXT("SO EASY ? YES !"), TEXT("USER TIP"), MB_OK | MB_ICONASTERISK);
                //Next checkpoint.
                level++;
            }
        }
    }
}

//Control the move.
int Up()
{
    if (x != 0)
    {
        if (map[level][x - 1][y] == 1)
        {
            map[level][x - 1][y] = 3;
            map[level][x][y] = 1;
        }
        else if (map[level][x - 1][y] == 4)
        {
            return 1;
        }
    }
    return 0;
}

int Down()
{
    if (x != N - 1)
    {
        if (map[level][x + 1][y] == 1)
        {
            map[level][x + 1][y] = 3;
            map[level][x][y] = 1;
        }
        else if (map[level][x + 1][y] == 4)
        {
            return 1;
        }
    }
    return 0;
}

int Right()
{
    if (y != N - 1)
    {
        if (map[level][x][y + 1] == 1)
        {
            map[level][x][y + 1] = 3;
            map[level][x][y] = 1;
        }
        else if (map[level][x][y + 1] == 4)
        {
            return 1;
        }
    }
    return 0;
}

int Left()
{
    if (y != 0)
    {
        if (map[level][x][y - 1] == 1)
        {
            map[level][x][y - 1] = 3;
            map[level][x][y] = 1;
        }
        else if (map[level][x][y - 1] == 4)
        {
            return 1;
        }
    }
    return 0;
}