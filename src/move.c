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
double x_position = 0, y_position = 0;
float animation_parametar = 0;
float x_sceen, y_sceen;
int gameStarted = 0;
int gameActive = 0;
double eps1  = 0.5;


/*Tajmer funkcija kojom regulisem kretanje rupe.*/
void on_timer (int value){
    if(value != TIMER_ID)
        return;
    /*printf("%lf %lf\n", x_position, y_position);*/

    if(indikator){
        polozaj pomocni;
        pomocni.x = x_position;
        pomocni.y = y_position;
        polozaj* nadjen = NULL;
        /*Niz planetPosition je podeljen u cetiri dela na osnovu toga kom kvadrantu planeta pripada.
        Ovde je implementirana linearna pretraga, jer imam samo 20 planeta po kvadrantu, pa nema potrebe za slozenijom pretragom.
        I jos smpo pretragu oprimzovali samo na deo niza koji se poklapa sa kvadrantom u kome je planeta.
        */

       /*Prvi kvdrant*/
        if(x_position >= 0 && y_position >= 0){
            int i;
            for(i=0; i<20; i++){
                /*Proveravamo da li je razlika x i y koordinata nase rupe i planete po apsolutnoj vrednosti manja od epsilon.
                Proveravamo na ovaj nacin jer su u pitanju realni brojevi pa poredjenje sa nulom nije dobra ideja,
                Takodje preko parametra eaten znamo d ali smo vec pojeli planetu jer je ne mzemo dva puta "usisati"
                */
                if(((-1)*eps1<x_position-planetPosition[i].x && x_position-planetPosition[i].x<eps1) 
                && (-1)*eps1<y_position-planetPosition[i].y && y_position-planetPosition[i].y<eps1 
                && planetPosition[i].eaten == 0){
                    /*Mozad ce trebati za debagovanje
                    printf("1\nPlaneta:%lf %lf\n Rupa: %lf %lf\n", planetPosition[i].x, planetPosition[i].y, x_position, y_position);
                    */
                    planetPosition[i].eaten = 1;
                    planetsLeft--;
                    break;
                }
            }        
        }
        /*Drugi kvadrant*/
        if(x_position<=0 && y_position>=0){
            int i;
            for(i=20; i<40; i++){
                if((-1)*eps1<x_position-planetPosition[i].x && x_position-planetPosition[i].x<eps1 
                && (-1)*eps1<y_position-planetPosition[i].y && y_position-planetPosition[i].y<eps1
                && planetPosition[i].eaten == 0){
                    /*
                    printf("2\nPlaneta:%lf %lf\n Rupa: %lf %lf\n", planetPosition[i].x, planetPosition[i].y, x_position, y_position);
                    */
                    planetPosition[i].eaten = 1;
                    planetsLeft--;
                    break;
                }
            }    
        }

        /*Treci kvadrant*/
        if(x_position<=0 && y_position<=0){
            int i;
            for(i=40; i<60; i++){
                if((-1)*eps1<x_position-planetPosition[i].x && x_position-planetPosition[i].x<eps1
                 && (-1)*eps1<y_position-planetPosition[i].y && y_position-planetPosition[i].y<eps1
                 && planetPosition[i].eaten == 0){
                    /*
                    printf("3\nPlaneta:%lf %lf\n Rupa: %lf %lf\n", planetPosition[i].x, planetPosition[i].y, x_position, y_position);
                    */
                    planetPosition[i].eaten = 1;
                    planetsLeft--;
                    break;
                }
            }    
        }

        /*Cetvrti kvadrant*/
        if(x_position>=0 && y_position<=0){
            int i;
            for(i=60; i<80; i++){
                if((-1)*eps1<x_position-planetPosition[i].x && x_position-planetPosition[i].x<eps1 
                    && (-1)*eps1<y_position-planetPosition[i].y && y_position-planetPosition[i].y<eps1
                    && planetPosition[i].eaten == 0){
                    /*
                    printf("4\nPlaneta:%lf %lf\n Rupa: %lf %lf\n", planetPosition[i].x, planetPosition[i].y, x_position, y_position);
                    */
                    planetPosition[i].eaten = 1;
                    planetsLeft--;
                    break;
                }
            }    
        }
    }

    x_position +=now.x*0.07;
    y_position +=now.y*0.07;
    animation_parametar+=0.5;


    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    
}

/*Funkcija koja detektuje kada se klikne taster.
Imam gameActive parametar koji kada se aktivira kada se prvi put klikne neki od tastera za kretanje rupe,
Incae se na ekranu ne pokazuje scena vec ulazni prozor*/
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

/*Funkcija koj areaguje na podizanje tastera, koja zaustavlja kretanje rupe u tom trenurku*/
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
