#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>

#include "drawSceen.h"
#include "move.h"
#include "shared.h"

extern float hour;
extern float timer_active;
/*Indikator koji govori da li su svi polzaji planeta vec izracunati prvi put*/
extern int indikator = 0;
static double eps = 0.00005;

int comparison (const void * a, const void * b) {
    polozaj *a1 = (polozaj *)a;
    polozaj* b1 =(polozaj*) b; 
    double a_x =  a1->x;
    double a_y =  a1->y;
    double b_x =  b1->x;
    double b_y =  b1->y;

    if(a_x-b_x <eps && a_y-b_y<eps)
        return 0;
    else if(a_x-b_x <eps && a_y<b_y)
        return -1;
    else if(a_x-b_x <eps && a_y>b_y)
        return 1;
    else if(a_x <b_x)
        return -1;
    else 
        return 1;

}


void on_timer1( int value){  
        if(value != 0)
            return;
        hour+=6;

        glutPostRedisplay();

        if(timer_active)
            glutTimerFunc(50, on_timer1, 0);
}


void DrawObjects(void){
    int mov = 0;
    /*int i;
    for(i=1; i<2; i++){
        DrawPlanets(mov);
        mov+=0.8;
    }*/
    double precnik = 0.1;
    
    double x_cord = 1;
    double y_cord = 1;
    int j;
    srand(time(NULL));
    /*Crtamo planete u prvom kvadrantu*/
    for (j=0; j<20; j++){
        /*Da bismo se resili bespotrebnog racuna, samo posto se prvi pit iscrtavaju planete racunacemo njihove pozicije 
        i pamtiti u niz, svali sledeci put ce planete postavljati samo na te pozicije, i tome indikator sluzi*/
        if(!indikator){    
            DrawPlanet(precnik, x_cord + 2*cos(x_cord), y_cord);
        }else{
            if(planetPosition[j].eaten ==0){
                DrawPlanet(precnik, planetPosition[j].x, planetPosition[j].y);
            }
        }
        if(gameStarted && indikator == 0){
            /*Planete se prvi put iscrtavaju i pamti se njihova pozicija*/      
            planetPosition[j].x = x_cord + 2*cos(x_cord);
            planetPosition[j].y = y_cord;
            planetPosition[j].eaten = 0;
        }
        
        x_cord += 1;
        y_cord += 2;
        /*Precik mog kruga je zapravo 0.4, ali zbog teksture izgleda vece zato kazemo da moze da proguta
        samo planete do 0.5 ptrecnika*/
        if(precnik>=0.5){
            precnik = 0.1;
        }
        else{
            precnik+=0.1;
        }
    }

    /*Crtamo planete u drugom kvadrantu*/
    x_cord = -1;
    y_cord = 1;
    for (j=20; j<40; j++){
        if(!indikator){
            DrawPlanet(precnik, x_cord, y_cord + 2*sin(y_cord));
        }else{
            if(planetPosition[j].eaten ==0){
                DrawPlanet(precnik, planetPosition[j].x, planetPosition[j].y);
            }
        }
        if(gameStarted && indikator==0){      
            planetPosition[j].x = x_cord;
            planetPosition[j].y = y_cord+2*sin(y_cord);
            planetPosition[j].eaten = 0;
        }


        x_cord -= 1;
        y_cord+=2;
        if(precnik>=0.5){
            precnik = 0.1;
        }
        else{
            precnik+=0.1;
        }
    }

    /*Crtamo planete u trecem kvadrantu*/
    x_cord = -1;
    y_cord = -1;
    for (j=40; j<60; j++){
        if(!indikator){
            DrawPlanet(precnik, x_cord, y_cord + 3*sin(y_cord));
        }else{
            if(planetPosition[j].eaten ==0){
                DrawPlanet(precnik, planetPosition[j].x, planetPosition[j].y);
            }
        }
        if(gameStarted && indikator==0){          
            planetPosition[j].x = x_cord;
            planetPosition[j].y = y_cord + 3*sin(y_cord);
            planetPosition[j].eaten = 0;
        }
        x_cord -= 2;
        y_cord -=1;
        if(precnik>=0.5){
            precnik = 0.1;
        }
        else{
            precnik+=0.1;
        }
    }

    /*Crtamo planete u cetvrtom kvadrantu*/
    x_cord = 1;
    y_cord = -1;
    for (j=60; j<80; j++){
        if(!indikator){
            DrawPlanet(precnik, x_cord + cos(x_cord), y_cord);
        }else{
            if(planetPosition[j].eaten ==0){
                DrawPlanet(precnik, planetPosition[j].x, planetPosition[j].y);
            }
        }
        if(gameStarted && indikator==0){      
            planetPosition[j].x = x_cord + cos(x_cord);
            planetPosition[j].y = y_cord;
            planetPosition[j].eaten = 0;
            if(j == 79)
                indikator = 1;
            qsort(planetPosition, 20, sizeof(polozaj), comparison);
            qsort(planetPosition+20, 20, sizeof(polozaj), comparison);
            qsort(planetPosition+40, 20, sizeof(polozaj), comparison);
            qsort(planetPosition+60, 20, sizeof(polozaj), comparison);
            /*mozda ce trebati za debagovanje
            int i;    
            for(i=0; i<40; i++){
                printf("%lf %lf\n", planetPosition[i].x, planetPosition[i].y);
                printf("**********************************************\n");
            }*/

        }
        x_cord += 2;
        y_cord-=1;
        if(precnik>=0.5){
            precnik = 0.1;
        }
        else{
            precnik+=0.1;
        }
    }

}





/*Funkcija z aisctavanje jedne planete*/
void DrawPlanet(double radius, double x_cord, double y_cord){
    glPushMatrix();
        int levo = 1;
        int desno =255;
        
        /*randomizovanje boje planete, delimo sa ovim cudnim brojevim jer ako bismo delili sa 256 dobijamo nezeljeno ponasanje
        tacnije imamo samo crne planete*/
        double r = (double)(rand()%(desno-levo+1)+levo)/280;
        double g = (double)(rand()%(desno-levo+1)+levo)/290;
        double b = (double)(rand()%(desno-levo+1)+levo)/255;


        glColor3f(r,g,b);
        glTranslatef(x_cord, 0.5, y_cord);
        glutSolidSphere(radius,40, 40);
    glPopMatrix();
    

}

/*Ovo je bilo deo programa ali ipak necemo, mozda dodam na kraju*/

/*
void DrawPlanets(int mov){
    glPushMatrix();
    float sun_rotation;
    float earth_rotation, earth_revolution;
    float moon_rotation, moon_revolution;

    sun_rotation = 360 * hour / (15 * 24);
    glTranslatef(-0.1,0.5,0.1);
    glPushMatrix();
        glRotatef(sun_rotation, 0, 1, 0);
        glColor3f(1, 1, 0);
        glutSolidSphere(0.35, 40, 40);
    glPopMatrix();
    
    earth_revolution = 360 * hour / (365 * 24);
    earth_rotation = 360 * hour / (1 * 24);

    glRotatef(earth_revolution, 0, 1, 0);
    glTranslatef(2,0.5,0.1);
    glPushMatrix();
        glRotatef(earth_rotation, 0, 1, 0);
        glColor3f(0, 0, 1);
        glutSolidSphere(0.3, 40, 40);
    glPopMatrix();
    
    moon_revolution = 360 * hour / (28 * 24);
    moon_rotation = 360 * hour / (28 * 24);

    glRotatef(moon_revolution, 0, 1, 0);
    glTranslatef(0.5,0 ,0.1);

    glRotatef(moon_rotation, 0, 1, 0);
    glColor3f(1, 1, 1);
    glutSolidSphere(0.1, 40, 40);

    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(2, 0.5, 2);
        glColor3f(1, 0, 0);
        glutSolidSphere(0.5, 40, 40);
        glTranslatef(1, -0.1, -3);
        glColor3f(0, 1, 0);
        glutSolidSphere(0.4, 40, 40);
    glPopMatrix();

    glutSwapBuffers();
}
*/
void makeSceen(void){
    GLfloat light_position[] = { 1, 2, 3, 0 };
    
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1 };
    GLfloat light_diffuse[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

}
