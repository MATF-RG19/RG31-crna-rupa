#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "move.h"
#include "drawSceen.h"
#include "shared.h"

#define TIMER_ID 0
#define TIMER_INTERVAL 10

extern float timer_active;
extern void on_timer1(int value);

move now;
float x_position = 0, y_position = 0;
float x_sceen, y_sceen;
int gameStarted = 0;
int gameActive = 0;


void on_timer (int value){
    if(value != TIMER_ID)
        return;
    
    x_position +=now.x*0.05;
    y_position +=now.y*0.05;
        
    
        
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    
}

void onKeyboard(unsigned char key,int x,int y){
	
    switch (key) {
        case 27:
            exit(0);
            break;

        case 's':
        if(!gameActive){
            gameActive = 1;
            gameStarted =1;
        }            
        if(!timer_active){
                timer_active = 1;
                glutTimerFunc(50, on_timer1, 0);
        }
            now.y+=1;
            break;

        case 'w':
            if(!gameActive){
                gameActive = 1;
                gameStarted =1;
            }
            if(!timer_active){
                timer_active = 1;
                glutTimerFunc(50, on_timer1, 0);
            }
            now.y-=1;
            break;

        case 'a':
            if(!gameActive){
                gameActive = 1;
                gameStarted =1;
            }
            if(!timer_active){
                timer_active = 1;
                glutTimerFunc(50, on_timer1, 0);
            }
            if (now.x==-1)
                break;
            now.x-=1;
            break;

        case 'd':
            if(!gameActive){
                gameActive = 1;
                gameStarted =1;
            }
            if(!timer_active){
                timer_active = 1;
                glutTimerFunc(50, on_timer1, 0);
            }
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
