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

void DrawPlanets(int mov);
 void on_timer1( int value){  
        if(value != 0)
            return;
        hour+=6;

        glutPostRedisplay();

        if(timer_active)
            glutTimerFunc(50, on_timer1, 0);
}

/*void DrawSquare(float trans1, float trans2, float trans3, float scal){
    glPushMatrix();
        glColor3f(1,0,0);
        glTranslatef(trans1,0.1,trans3);
        glScalef(scal, scal, scal);
        glutSolidCube(0.5);
    glPopMatrix(); 
    glPushMatrix();     
        glColor3f(0,1,0);
        glTranslatef(-trans1,0.1,trans3);
        glScalef(scal, scal, scal);
        glutSolidCube(0.5);
    glPopMatrix();
}*/

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
    for (j=0; j<10; j++){
        DrawPlanet(precnik, x_cord + 2*cos(x_cord), y_cord);
        x_cord += 1;
        y_cord += 2;
        if(precnik>=0.5){
            precnik = 0.1;
        }
        else{
            precnik+=0.1;
        }
    }

    x_cord = -1;
    y_cord = -1;
    for (j=0; j<10; j++){
        DrawPlanet(precnik, x_cord, y_cord + 3*sin(y_cord));
        x_cord -= 2;
        y_cord -=1;
        if(precnik>=0.5){
            precnik = 0.1;
        }
        else{
            precnik+=0.1;
        }
    }

    x_cord = 1;
    y_cord = -1;
    for (j=0; j<10; j++){
        DrawPlanet(precnik, x_cord + cos(x_cord), y_cord);
        x_cord += 2;
        y_cord-=1;
        if(precnik>=0.5){
            precnik = 0.1;
        }
        else{
            precnik+=0.1;
        }
    }

    x_cord = -1;
    y_cord = 1;
    for (j=0; j<10; j++){
        DrawPlanet(precnik, x_cord, y_cord + 2*sin(y_cord));
        x_cord -= 1;
        y_cord+=2;
        if(precnik>=0.5){
            precnik = 0.1;
        }
        else{
            precnik+=0.1;
        }
    }

}

void DrawPlanet(double radius, double x_cord, double y_cord){
    glPushMatrix();
        int levo = 1;
        int desno =255;
        
        double r = (double)(rand()%(desno-levo+1)+levo)/280;
        double g = (double)(rand()%(desno-levo+1)+levo)/290;
        double b = (double)(rand()%(desno-levo+1)+levo)/255;


        glColor3f(r,g,b);
        glTranslatef(x_cord, 0.5, y_cord);
        glutSolidSphere(radius,40, 40);
    glPopMatrix();
    

}


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

    /*glutSwapBuffers();*/
}

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
