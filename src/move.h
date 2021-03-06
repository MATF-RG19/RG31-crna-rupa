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

int gameStarted;
int gameActive;
extern int gameOver;
extern int needHelp;


move now;
extern double x_position, y_position;
extern float x_sceen, y_sceen;
extern float animation_parametar;

extern void on_timer(int value);

extern void onKeyboard(unsigned char key, int x, int y);
extern void onKeyboardUp(unsigned char key,int x,int y);


#endif
