#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
/*#include "header.c"
#include "onKeyboard.c"
#include "onTimer.c"
*/
#include "move.h"

#define PI 3.1415926535
#define num_of_dots 600

static int window_width, window_height;

static void on_reshape(int width, int height);
static void on_display(void);
void DrawCircle(void);
void DrawObjects(void);


int main(int argc, char **argv)
{
    x_position = 0;
    y_position = 0;
    x_sceen = 0;
    y_sceen = 0;
    now.x = 0;
    now.y = 0;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    glutKeyboardFunc(onKeyboard);
    glutKeyboardUpFunc(onKeyboardUp);
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);

    glutMainLoop();

    return 0;
}


static void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            60,
            window_width/(float)window_height,
            1, 12);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            1+(cos(PI/12)*0.1), 2, 3+(cos(PI/12)*0.1),
            x_sceen, 0, y_sceen,
            0, 1, 0
        );

    glColor3f(0.5,0.3,0.7);
    
    /*glTranslatef(x_sceen, 0, y_sceen);*/
    DrawObjects();
    glTranslatef(x_position, 0, y_position);
    
    DrawCircle();
    
    glutPostRedisplay();
    glutSwapBuffers();
}


void DrawCircle(void)
{
    /*glClear(GL_COLOR_BUFFER_BIT);*/
    
    int i;
    glColor3f(0,0,0);
    
    glBegin(GL_POINTS);
    for(i = 0; i < num_of_dots; i++)
    {
        glVertex3f(
            cos(2* i * PI / num_of_dots)*0.4,
            0,
            sin(2* i * PI / num_of_dots)*0.4
        );
    }
    glEnd();

    
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i < num_of_dots; i++) {
        glVertex3f(
                cos(2 * i * PI / num_of_dots) * 0.4,
                   0,
                sin(2 * i * PI / num_of_dots) * 0.4
                  );
    }

    glEnd();
}


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
    int i;
    float trans1 =0.1, trans2 = 0.1;
    float scale = 0.3;
    for(i=0; i<4; i++){
        DrawSquare(trans1, trans1, trans2,  scale);
        trans1 +=0.1;
        trans2 +=0.2;
        
    }
}

