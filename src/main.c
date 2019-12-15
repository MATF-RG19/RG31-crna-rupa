#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "move.h"
#include "drawSceen.h"

#define PI 3.1415926535
#define num_of_dots 600

GLubyte hole_texture[3 * 4 * 4] = {
    0, 0, 0,   0, 0, 0,   0, 0, 0,   0, 0, 0,
    0, 0, 0,   0, 0, 0,   0, 0, 0,   0, 0, 0,
    1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1,
    1, 1, 1,   1, 1, 1,   1, 1, 1,   1, 1, 1
};


static int window_width, window_height;

static void initialize(void);
static void on_reshape(int width, int height);
static void on_display(void);
void DrawCircle(void);
void DrawObjects(void);

static GLuint id_tex[1];


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
    
    glClearColor(0, 0, 0, 0);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

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
            1+x_position, 2, 3+y_position,
            x_position, 0, y_position,
            0, 1, 0
        );

    makeSceen();
    
    DrawObjects();
    glTranslatef(x_position, 0, y_position);
    
    DrawCircle();
    
    glutPostRedisplay();
    glutSwapBuffers();
}

static void initialize(void)
{
    glEnable(GL_COLOR_MATERIAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glGenTextures(1, id_tex);

    /* Kreira se prva tekstura. */
    glBindTexture(GL_TEXTURE_2D, id_tex[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 1,
                 GL_RGB, GL_UNSIGNED_BYTE, hole_texture);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

#define SEGMENTS 16
void DrawCircle(void)
{
    int i;
    glColor3f(0.5,0.5,0.5);
    glBindTexture(GL_TEXTURE_2D, id_tex[0]);
    glEnable(GL_TEXTURE_2D);

    
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
        glNormal3f(0, 1, 0);
        glTexCoord2f(i / (float) SEGMENTS, 0);
        glVertex3f(
                cos(2 * i * PI / num_of_dots) * 0.4,
                   0,
                sin(2 * i * PI / num_of_dots) * 0.4
                  );
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
    
#undef SEGMENTS
}


