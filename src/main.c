#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

#include "image.h"
#include "move.h"
#include "drawSceen.h"
#include "shared.h"

#define PI 3.1415926535
#define num_of_dots 600
#define FILENAME0 "hole113.bmp"

float hour;
float timer_active;


static int window_width, window_height;

static void initialize(void);
static void on_reshape(int width, int height);
static void on_display(void);
void DrawCircle(void);
extern void DrawObjects(void);
static void renderStrokeString(int x, int y, int z, void* font, char* string);

char statingText[50];
static GLuint name[1];


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

    glutInitWindowSize(1200, 800);
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
    initialize();

    

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
    if(!gameStarted){
        gluLookAt(
            1, 2, 3,
            1, 1, 1,
            0, 1, 0
        );
    }
    else{
        gluLookAt(
                1+x_position, 2, 3+y_position,
                x_position, 0, y_position,
                0, 1, 0
        );
    }
    
    if(!gameStarted){
        glPushMatrix();
            int x = -37;
            int y = 12;
            int z = 0;
            glScalef(0.04, 0.04, 4);
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
    
        DrawObjects();
        glTranslatef(x_position, 0, y_position);

        DrawCircle();
    
    }   
    

    glutPostRedisplay();
    glutSwapBuffers();
}

static void initialize(void)
{
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, FILENAME0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(1, name);

    glBindTexture(GL_TEXTURE_2D, name[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

}

void DrawCircle(void)
{
    int i;
    glColor3f(0.5,0.5,0.5);
    glPushMatrix();
    glTranslatef(0, 0.2, 0);
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
    glPopMatrix();

    glTranslatef(-0.8,0.1,-0.9);
    glBindTexture(GL_TEXTURE_2D, name[0]);
    glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glTexCoord2f(0,0);
        glVertex3f(0,0,0);
        glTexCoord2f(0,1);
        glVertex3f(0,0,1.5);
        glTexCoord2f(1,1);
        glVertex3f(1.5,0,1.5);
        glTexCoord2f(1,0);
        glVertex3f(1.5,0,0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
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