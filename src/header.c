#ifndef _HEADER_H__
#define _HEADER_H__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 10

typedef struct MOVE{
    double x;
    double y;
}move;

move now;
float x_position=0, y_position=0;
float x_sceen=0, y_sceen = 0;

/*static void on_timer(int value);

static void onKeyboard(unsigned char key, int x, int y);
static void onKeyboardUp(unsigned char key,int x,int y);
*/

#endif
