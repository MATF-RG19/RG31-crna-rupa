#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "move.h"
#include "drawSceen.h"
#include "shared.h"

#define TIMER_ID 0
#define TIMER_INTERVAL 10

/*Promenljiva kojom zakljucujem da mi je tajmer aktivan*/
extern float timer_active;
extern void on_timer1(int value);

move now;
/*ove promenljive definisu polozaj sam rupe*/
double x_position = 0, y_position = 0;
float animation_parametar = 0;
int gameStarted = 0;
int gameActive = 0;
double eps1  = 0.5;

/*Funkcija koja detektuje kolizije*/
void EatPlanet(int j){
    int i;
    for(i=j; i<j+20; i++){
        /*Proveravamo da li je razlika x i y koordinata nase rupe i planete po apsolutnoj vrednosti manja od epsilon.
        Proveravamo na ovaj nacin jer su u pitanju realni brojevi pa poredjenje sa nulom nije dobra ideja,
        Takodje preko parametra eaten znamo d ali smo vec pojeli planetu jer je ne mzemo dva puta "usisati"
        */
        if(((-1)*eps1<x_position-planetPosition[i].x && x_position-planetPosition[i].x<eps1) 
        && (-1)*eps1<y_position-planetPosition[i].y && y_position-planetPosition[i].y<eps1 
        && planetPosition[i].eaten == 0 && planetPosition[j].precnik <= 0.4*(1+(80 - planetsLeft)*0.01)){
            /*Mozad ce trebati za debagovanje
            printf("1\nPlaneta:%lf %lf\n Rupa: %lf %lf\n", planetPosition[i].x, planetPosition[i].y, x_position, y_position);
            */
            planetPosition[i].eaten = 1;
            planetsLeft--;
            break;
        }
    } 

}


/*Tajmer funkcija kojom regulisem kretanje rupe.*/
void on_timer (int value){
    if(value != TIMER_ID)
        return;
    
    if(indikator){
        /*Niz planetPosition je podeljen u cetiri dela na osnovu toga kom kvadrantu planeta pripada.
        Ovde je implementirana linearna pretraga, jer imam samo 20 planeta po kvadrantu, pa nema potrebe za slozenijom pretragom.
        I jos smpo pretragu oprimzovali samo na deo niza koji se poklapa sa kvadrantom u kome je planeta.
        */

       /*Prvi kvdrant*/
        if(x_position >= 0 && y_position >= 0){
            EatPlanet(0);        
        }
        /*Drugi kvadrant*/
        if(x_position<=0 && y_position>=0){
            EatPlanet(20);    
        }

        /*Treci kvadrant*/
        if(x_position<=0 && y_position<=0){
            EatPlanet(40);    
        }

        /*Cetvrti kvadrant*/
        if(x_position>=0 && y_position<=0){
            EatPlanet(60);    
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
        /*Da bi detektovali pritisak pritisak tastera prvi put*/
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
