#ifndef _DRAW_SCEEN__
#define _DRAW_SCEEN__
#define TIMER_INTERVAL_1 150


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef struct POLOZAJ{
    double x;
    double y;
    int eaten;
}polozaj;


extern int indikator;

extern void DrawObjects(void);
extern void makeSceen(void);
extern float hour;
extern float timer_active;
/*niz u kome mcemo za svaku planetu cuvati njen prvobtno izracunat polozaj kao i 
informaciju o tome da li je ona usisana*/
polozaj planetPosition[85];

void DrawPlanets(int mov); 
void on_timer1( int value);
void DrawPlanet(double radius, double x_cord, double y_cord);
int comparison (const void * a, const void * b);

#endif
