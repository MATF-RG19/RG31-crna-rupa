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
int indikator = 0;
static double eps = 0.00005;
int planetsLeft = 80;
void placeThePlanets(double x_cord, double y_cord, double precnik, int i, int x_kvadrant, int y_kvadrant, int s, int po_x);

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
/*Funkcija koja iscrtava sve planete po kvadrantima.x_kvadrant je promenljiva koja regulise promenu parametara x pri iscrtavanju,
slicno za y_kvadrant. 
Parametar s govori d ali cemo randomizovati sa sinusom ili sa kosinusom.*/
void placeThePlanets(double x_cord, double y_cord, double precnik, int i, int x_kvadrant, int y_kvadrant, int s, int po_x){
    int j;
    int uz_x = po_x;
    int uz_y;
    if(po_x ==0)
        uz_y = 1;
    else
        uz_y = 0;
    for (j=i; j<i+20; j++){
        /*Da bismo se resili bespotrebnog racuna, samo kada se prvi put iscrtavaju planete racunacemo njihove pozicije 
        i pamtiti u niz, svali sledeci put ce planete postavljati samo na te pozicije, i tome indikator sluzi*/
        if(!indikator){
            if(s ==0){    
                DrawPlanet(precnik, x_cord + 2*cos(x_cord)*uz_x, y_cord + 3*cos(y_cord)*uz_y);
                planetPosition[j].x = x_cord + 2*cos(x_cord)*uz_x;
                planetPosition[j].y = y_cord + 2*cos(y_cord)*uz_y;
                planetPosition[j].eaten = 0;
                planetPosition[j].precnik = precnik;
            }
            else{
                DrawPlanet(precnik, x_cord + sin(x_cord)*uz_x, y_cord + 3* sin(y_cord)*uz_y);
                planetPosition[j].x = x_cord + 2*sin(x_cord)*uz_x;
                planetPosition[j].y = y_cord + 3*sin(y_cord)*uz_y;
                planetPosition[j].eaten = 0;
                planetPosition[j].precnik = precnik;
            }
        }else{
            /*Provera da li je planeta vec pojedena*/
            if(planetPosition[j].eaten == 0){
                DrawPlanet(planetPosition[j].precnik, planetPosition[j].x, planetPosition[j].y);
            }
        }
    
        if(j == 79 && indikator ==0 ){
            indikator = 1;
            qsort(planetPosition, 20, sizeof(polozaj), comparison);
            qsort(planetPosition+20, 20, sizeof(polozaj), comparison);
            qsort(planetPosition+40, 20, sizeof(polozaj), comparison);
            qsort(planetPosition+60, 20, sizeof(polozaj), comparison);
            /*mozda ce trebati za debagovanje
            int i;    
            for(i=0; i<80; i++){
                printf("%lf %lf\n", planetPosition[i].x, planetPosition[i].y);
                printf("**********************************************\n");
            }*/
        }

        
        x_cord  = x_cord + (x_kvadrant)*1;
        y_cord =  y_cord + (y_kvadrant)*2;
        /*Precik mog kruga je zapravo 0.4, ali zbog teksture izgleda vece zato kazemo da moze da proguta
        samo planete do 0.5 ptrecnika*/
        if(precnik>=0.5){
            precnik = 0.1;
        }
         else{
            precnik+=0.1;
        
        }
    }

}


void DrawObjects(void){
    double precnik = 0.1;
    srand(time(NULL));
    double x_cord;
    double y_cord;

    /*Crtamo planete u prvom kvadrantu*/
    if(!indikator){
        x_cord = 1;
        y_cord = 1;
    }
    placeThePlanets(x_cord, y_cord,precnik, 0, 1, 1, 0, 1);
    /*Crtamo planete u drugom kvadrantu*/
    if(!indikator){
        x_cord = -1;
        y_cord = 1;
    }
    placeThePlanets(x_cord, y_cord, precnik, 20, -1, 1, 1, 0);
    /*Crtamo planete u trecem kvadrantu*/
    if(!indikator){
        x_cord = -1;
        y_cord = -1;
    }
    placeThePlanets(x_cord, y_cord, precnik, 40, -1, -1, 1, 0);
    /*Crtamo planete u cetvrtom kvadrantu*/
    if(!indikator){
        x_cord = 1;
        y_cord = -1;
    }
    placeThePlanets(x_cord, y_cord, precnik, 60, 1, -1, 0, 1);

}





/*Funkcija za isctavanje jedne planete*/
void DrawPlanet(double radius, double x_cord, double y_cord){
    glPushMatrix();
        int levo = 1;
        int desno =255;
        
        /*randomizovanje boje planete, delimo sa ovim cudnim brojevim jer ako bismo delili sa 256 dobijamo nezeljeno ponasanje
        tacnije imamo samo crne planete*/
        double r = (double)(rand()%(desno-levo+1)+levo)/280;
        double g = (double)(rand()%(desno-levo+1)+levo)/290;
        double b = (double)(rand()%(desno-levo+1)+levo)/255;

        glEnable(GL_LIGHTING);

        GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1 };
        GLfloat light_diffuse1 [] ={1, 0, 0, 1}; 
    
        glEnable(GL_COLOR_MATERIAL);

        glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse1);

        GLfloat shine =10;
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
        GLfloat  diffuse_coefs1[] = {1,1,1,1};
        glEnable(GL_LIGHT1);
        glColor3f(r,g,b);
        glTranslatef(x_cord, 0.5, y_cord);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,diffuse_coefs1);
        glutSolidSphere(radius,40, 40);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHTING);
    glPopMatrix();
    

}

