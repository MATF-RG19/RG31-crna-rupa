#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "drawSceen.h"

void DrawPlanets(int mov);


void DrawSquare(float trans1, float trans2, float trans3, float scal){
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
}

void DrawObjects(void){
    int mov = 0;
    int i;
    for(i=1; i<3; i++){
        DrawPlanets(mov);
        mov+=0.8;
    }
}

void DrawPlanets(int mov){
    glPushMatrix();
        glTranslatef(-0.1+mov,0.5,0.1+mov);
        glColor3f(1, 1, 0);
        glutSolidSphere(0.35, 40, 40);
    glPopMatrix();
    
    
    glPushMatrix();
        glTranslatef(2+mov,0.5+mov ,0.1+mov);
        glColor3f(0, 0, 1);
        glutSolidSphere(0.3, 40, 40);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(2.5+mov,0.5+mov ,0.1+mov);
        glColor3f(1, 1, 1);
        glutSolidSphere(0.1, 40, 40);
    glPopMatrix();

}

void makeSceen(void){
    GLfloat light_position[] = { 1, 2, 3, 0 };
    
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1 };
    GLfloat light_diffuse[] = { 0, 0, 0, 1 };
    GLfloat light_specular[] = { 0, 0, 0, 1 };
    
    GLfloat ambient_coeffs[] = { 1.0, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs[] = { 0.0, 0.0, 0.8, 1 };
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    GLfloat shininess = 20;
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
}
