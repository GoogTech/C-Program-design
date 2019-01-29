/*
 * @Author: HuangYuhui 
 * @Date: 2019-01-29 21:05:55 
 * @Last Modified by: HuangYuhui
 * @Last Modified time: 2019-01-29 21:07:32
 */
#ifndef _ELIMINATE_THE_BRICK_H
#define _ELIMINATE_THE_BRICK_H

//Initialize the data.
void startup();

//Draw the graph.
void clean();

//Display the drawing.
void show();

//Draw the brick.
void drawBrick();

//Update the position of ball.
void updateWithoutInput();

//Updata the data inputed by the user.
void updateWithInput();

//Initialize the data when the Game is over.
void gameOver();

#endif