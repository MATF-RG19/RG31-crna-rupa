#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

#include "move.h"
#include "drawSceen.h"
#include "shared.h"

#define PI 3.1415926535
#define num_of_dots 600

float hour;
float timer_active;

GLubyte hole_texture[3 * 4 * 4] = {
    0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,
    0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,
    0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,   0xff, 0xff, 0xdf,
    0xc8, 0x88, 0x88,   0xc8, 0x88, 0x88,   0xc8, 0x88, 0x88,   0xc8, 0x88, 0x88
};


static int window_width, window_height;

static void initialize(void);
static void on_reshape(int width, int height);
static void on_display(void);
void DrawCircle(void);
extern void DrawObjects(void);
static void renderStrokeString(int x, int y, int z, void* font, char* string);

static GLuint id_tex[1];
char statingText[50];
char name[50];

int main(int argc, char **argv)
{
    x_position = 0;
    y_position = 0;
    x_sceen = 0;
    y_sceen = 0;
    now.x = 0;
    now.y = 0;
    hour = 0;
    timer_active= 0;
    
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
    
    if(!gameStarted){
        glPushMatrix();
            int x = -24;
            int y = 11;
            int z = -1;
            glScalef(0.05, 0.05, 5);
                glPushAttrib(GL_LINE_BIT);
                    glLineWidth(4);
                    sprintf(statingText, "To start the game press a or s or d or w");
                    glColor3f(1, 1, 1);
                    renderStrokeString(x, y, z, GLUT_STROKE_MONO_ROMAN , statingText);
                glPopAttrib();
            glPopMatrix();
    }

    if(gameStarted){
        makeSceen();
        /*initialize();*/

        DrawObjects();
        glTranslatef(x_position, 0, y_position);
    
        DrawCircle();
    
    }
    glutPostRedisplay();
    glutSwapBuffers();
}

static void initialize(void)
{
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glGenTextures(1, id_tex);

    /* Kreira se prva tekstura. */
    glBindTexture(GL_TEXTURE_2D, id_tex[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, hole_texture);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawCircle(void)
{
    int i;
    glColor3f(0.5,0.5,0.5);
    /*glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glGenTextures(1, id_tex);
    glBindTexture(GL_TEXTURE_2D, id_tex[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, hole_texture);
    

    glEnable(GL_TEXTURE_2D);
    /*glEnable(GL_DEPTH_TEST);*/
    /*glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    */
    glColor4f(0.7, 0.7, 0.7, 0);
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

    /*glColor4f(1, 0, 0, 1);
    glBegin(GL_POINTS);
    for(i = 0; i < num_of_dots; i++)
    {
        glVertex3f(
            cos(2* i * PI / num_of_dots)*0.3,
            0,
            sin(2* i * PI / num_of_dots)*0.3
        );
    }
    glEnd();*/

    /*
    glColor4f(1, 0, 0, 1);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i < num_of_dots; i++) {
        glNormal3f(0, 1, 0);
        glVertex3f(
                cos(2 * i * PI / num_of_dots) * 0.3,
                   0,
                sin(2 * i * PI / num_of_dots) * 0.3
                  );
    }
    glEnd();
    */
    glColor4f(0.7, 0.7, 0.7, 0);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i < num_of_dots; i++) {
        glNormal3f(0, 1, 0);
        glVertex3f(
                cos(2 * i * PI / num_of_dots) * 0.4,
                   0,
                sin(2 * i * PI / num_of_dots) * 0.4
                  );
    }
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
}

static void renderStrokeString(int x, int y,int z,void* font, char* string){
    int len;
    glDisable(GL_LIGHTING);
    glTranslatef(x,y,z);
    glScalef(0.03,0.03,10);
    len = strlen(string);
    int i;
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(font, string[i]);
    }
}