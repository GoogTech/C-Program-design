/*
 * @Author: HuangYuhui 
 * @Date: 2019-01-29 21:03:29 
 * @Last Modified by:   HuangYuhui 
 * @Last Modified time: 2019-01-29 21:03:29 
 */
#include "Eliminate-the-brick.h"
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Test the program.
 */
int main()
{
    startup();
    while (1)
    {
        clean();
        updateWithoutInput();
        updateWithInput();
        show();
    }
    gameOver();

    system("pause");
    return 0;
}
