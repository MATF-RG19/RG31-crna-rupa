#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "header.h"
#include "onKeyboard.h"
#include "ontimer.h"

static int window_width, window_height;

static void on_reshape(int width, int height);
static void on_display(void);
static void initialize(void);

int main(int argc, char **argv)
{
    x_position = 0;
    y_position = 0;
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
            1, 5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            1, 2, 3,
            0, 0, 0,
            0, 1, 0
        );

    glColor3f(0.5,0.3,0.7);
    /*glLineWidth(40);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(1, 0 ,0);
    glEnd();
    
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
    glEnd();
    
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,0, 1);
    glEnd();
    
    
    glColor3f(0, 0, 1);
        glBegin(GL_POINTS);
        glVertex3f(0, 0, 0);
        glVertex3f(0.75, 0, 0);
        glVertex3f(0.75, 0.75, 0);
        glVertex3f(0, 0.75, 0);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.75, -0.75, 0);
        glVertex3f(-0.25, -0.75, 0);
        glVertex3f(-0.25, -0.25, 0);
        glVertex3f(-0.75, -0.25, 0);
    glEnd();
    */
    
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
    glEnd();
    
    glColor3f(1, 1, 0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);
    glEnd();
    
    glColor3f(0,1,1);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,0,1);
    glEnd();
    
    
    glColor3f(25, 0, 1);
    glTranslatef(x_position, 0, y_position);
    glutWireCube(1);
    

    glutPostRedisplay();
    glutSwapBuffers();
}
