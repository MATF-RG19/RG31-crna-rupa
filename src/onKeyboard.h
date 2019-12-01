#ifndef _ON_KEYBOARD_C_
#define _ON_KEYBOARD_C_

#include "header.h"

static void onKeyboard(unsigned char key, int x, int y){
	
    switch (key) {
        case 27:
            exit(0);
            break;

        case 'w':
            now.y+=1;
            break;

        case 's':
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


static void onKeyboardUp(unsigned char key, int x,int y){

    switch (key) {
        case 27:
            exit(0);
            break;

        case 's':
            now.y+=1;
            break;

        case 'a':
            now.x+=1;
            break;

        case 'd':
            now.x-=1;
            break;
        
        case 'w':
            now.y-=1;
            break;

    }

    glutPostRedisplay();
}

#endif
