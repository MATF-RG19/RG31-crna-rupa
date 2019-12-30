#ifndef _DRAW_SCEEN__
#define _DRAW_SCEEN__
#define TIMER_INTERVAL_1 50


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

extern void DrawObjects(void);
extern void makeSceen(void);
extern float hour;
extern float timer_active;

void DrawPlanets(int mov); 
void on_timer1( int value);

#endif
