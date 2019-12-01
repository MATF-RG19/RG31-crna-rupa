#ifndef _ON_TIMER_C_
#define _ON_TIMER_C_

#include "header.h"

static void on_timer (int value){
    if(value != TIMER_ID)
        return;
    x_position +=now.x*0.01;
    y_position +=now.y*0.01;
    
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
}

#endif
