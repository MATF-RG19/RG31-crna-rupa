#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "move.h"

#define TIMER_ID 0
#define TIMER_INTERVAL 10

move now;
float x_position = 0, y_position = 0;
float x_sceen, y_sceen;

void on_timer (int value){
    if(value != TIMER_ID)
        return;
    x_position +=now.x*0.01;
    y_position +=now.y*0.01;
    
    y_sceen +=now.y*0.1;
    x_sceen +=now.x*0.1;
    
    
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
}

void onKeyboard(unsigned char key,int x,int y){
	
    switch (key) {
        case 27:
            exit(0);
            break;

        case 's':
            now.y+=1;
            break;

        case 'w':
            now.y-=1;
            break;

        case 'a':
            if (now.x==-1)
                break;
            now.x-=1;
            break;

        case 'd':
            if (now.x==1)
                break;
            now.x+=1;
            break;
    }

   glutPostRedisplay();
}


void onKeyboardUp(unsigned char key,int x,int y){

    switch (key) {
        case 27:
            exit(0);
            break;

        case 'w':
            now.y+=1;
            break;

        case 'a':
            now.x+=1;
            break;

        case 'd':
            now.x-=1;
            break;
        
        case 's':
            now.y-=1;
            break;

    }

    glutPostRedisplay();
}
