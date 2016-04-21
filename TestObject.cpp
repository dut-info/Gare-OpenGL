//Squelette du cylindre. A vous de créer la suite.
//compilation barbare sous linux : g++ -Wall squelette_cylindre.cpp struct.cpp -o cylindre -lglut

#ifdef __APPLE__
//compilation sous MacOs par :
//gcc -framework GLUT -framework OpenGL -framework Cocoa source.c -o nom_executable
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#endif

#ifdef __WIN32__
//parce qu'il manque des choses aux gens qui utilisent MsWindows, où OpenGL ne peut fonctionner que s'il discute avec le gestionnaire de fenêtres ("windows.h")
	#define GLUT_DISABLE_ATEXIT_HACK	//utile si vous compilez en g++ sous windows avec le glut.lib prévu pour MsVisual
	#include <windows.h>
	#include "glut.h"	//il faut avoir le fichier "glut.h" dans le même répertoire que votre .cpp (et aussi le glut.lib et le glut.dll)
#endif

#ifdef __linux__
	//pour les non-windowiens, GLUT (fenêtrage opengl) est inclu dans les distributions
	//pour les ubuntiens : apt-get install freeglut3 freeglut3-dev
	#include <GL/glut.h>
#endif

#include <iostream>
#include <cstdlib> //pour exit(), et EXIT_SUCCESS

#include <cstdio>
#include <cmath>


#include "Object.h"
#include "Chemine.hpp"

#include "Parallelepiped.h"
#include "RailDroit.h"
#include "Train.h"
#include "Locomotive.hpp"
#include "Wagon.hpp"

#include "BezierCurve.h"
#include <vector>

#define M_PI 3.14159265358979323846

#include "Camera.h"
#include "Camera.cpp"

using namespace std;

#define WIDTH  600
#define HEIGHT 600

#define KEY_ESC 27

//Declaration des fonctions
void Display();
void Reshape (int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Idle();

//Declaration des variables et de la FreeFlyCaméra
Camera g_camera;
bool g_key[256];
bool g_shift_down = false;
bool g_fps_mode = false;
int g_viewport_width = 0;
int g_viewport_height = 0;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;

float angleX = 0.0f; //angle de rotation en Y de la scene
float angleY = 0.0f; //angle de rotation en X de la scene

//float pasDeplacement = 1.25f;


//position lumiere
float xLitePos = 0.0f;
float yLitePos = 10.0f;
float zLitePos = -100.0f;

float tx = 0.0f;
float ty = 0.0f;
float tz = 0.0f;

int nbPoints = 10;

float indice;

//Vitesse des mouvements de la caméra
const float g_translation_speed = 0.3;
const float g_rotation_speed = M_PI/180*0.02;

/* initialisation d'OpenGL*/
static void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	// Si vous avez des choses à initialiser, c'est ici.

	glEnable(GL_LIGHTING); 	// Active l'éclairage
  	glEnable(GL_LIGHT0); 	// Allume la lumière n°1

                         //différents paramètres
    GLfloat ambient[] = {0.15f,0.15f,0.15f,1.0f};
    GLfloat diffuse[] = {0.5f,0.5f,0.5f,1.0f};
    GLfloat light0_position [] = {0.0f, -10.0f, 0.0f, 0.0f};
    GLfloat specular_reflexion[] = {0.8f,0.8f,0.8f,1.0f};
    GLubyte shiny_obj = 128;

    //positionnement de la lumière avec les différents paramètres
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
    glEnable(GL_LIGHT0);

    //spécification de la réflexion sur les matériaux
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_reflexion);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,shiny_obj);
}

void affiche_repere() {
	//affiche les axes du repere
	glColor3f ( 0.0f, 1.0f, 0.0f ); //Y vert
	glBegin(GL_LINES);
		glVertex3f ( 0.0f, 0.0f, 0.0f );
		glVertex3f ( 0.0f, 20.0f, 0.0f );
	glEnd();

	glColor3f ( 0.0f, 0.0f, 1.0f ); //Z bleu
	glBegin(GL_LINES);
		glVertex3f ( 0.0f, 0.0f, 0.0f );
		glVertex3f ( 0.0f, 0.0f, 20.0f );
	glEnd();

	glColor3f ( 1.0f, 0.0f, 0.0f); //X rouge
	glBegin(GL_LINES);
		glVertex3f ( 0.0f, 0.0f, 0.0f );
		glVertex3f ( 20.0f, 0.0f, 0.0f );
	glEnd();
}

/* Dessin */
void display(void) {
	glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//effacement du buffer

	glLoadIdentity();

	affiche_repere();
	g_camera.Refresh();

  glColor3f(1.0f, 0.15f, 0.15f);

	glRotatef(-90, 1, 0, 0);

	// RAILS
	RailDroit rail1(200, 2.2);
	RailDroit rail2(200, 2.2);

	glPushMatrix();
		glTranslatef(-100, 0, 0);
		rail1.draw();

		glPushMatrix();
			glTranslatef(0, 4.5, 0);
			rail2.draw();
		glPopMatrix();
	glPopMatrix();


	// TRAIN
	Train train1;
	Train train2;

	float mvnt = indice;
/*
	if(indice > 50 && indice < 70) {
		mvnt =

		3*(indice - 17.15) / sqrt(1 + (indice - 17.15)*(indice - 17.15)) + 2.95;
	}
*/
	glPushMatrix();
		glTranslatef(mvnt/4-50, 1.5, 2.1);
		train1.draw();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-mvnt/4+50, 6, 2.1);
		train1.draw();
	glPopMatrix();

	glutSwapBuffers();// echange des buffers
}

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h) {
   g_viewport_width = w;
   g_viewport_height = h;

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //gluPerspective(70,(double)700/700,0,2000);
   glOrtho ( -20.0f, 20.0f, -20.0f, 20.0f, -20.0f, 20.0f);
   gluPerspective (1, (GLfloat)w / (GLfloat)h, 50 , 1); //set the perspective (angle of sight, width, height, ,depth)
   glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
    if(key == 27) {
        exit(0);
    }

    if(key == ' ') {
        g_fps_mode = !g_fps_mode;

        if(g_fps_mode) {
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(g_viewport_width/2, g_viewport_height/2);
        }
        else {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        g_shift_down = true;
    }
    else {
        g_shift_down = false;
    }

    g_key[key] = true;
}

void KeyboardUp(unsigned char key, int x, int y)
{
    g_key[key] = false;
}

void Timer(int value)
{
    if(g_fps_mode) {
        if(g_key['z'] || g_key['Z']) {
            g_camera.Move(g_translation_speed);
        }
        else if(g_key['s'] || g_key['S']) {
            g_camera.Move(-g_translation_speed);
        }
        else if(g_key['q'] || g_key['Q']) {
            g_camera.Strafe(g_translation_speed);
        }
        else if(g_key['d'] || g_key['D']) {
            g_camera.Strafe(-g_translation_speed);
        }
        else if(g_mouse_left_down) {
            g_camera.Fly(g_translation_speed);
        }
        else if(g_mouse_right_down) {
            g_camera.Fly(-g_translation_speed);
        }
    }

    glutTimerFunc(1, Timer, 0);
}

void Idle()
{
		indice += 0.1f;
    display();
}

void Mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN) {
        if(button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = true;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = true;
        }
    }
    else if(state == GLUT_UP) {
        if(button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = false;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = false;
        }
    }
}

void MouseMotion(int x, int y)
{
    static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }

    if(g_fps_mode) {
        int dx = x - g_viewport_width/2;
        int dy = g_viewport_height/2 - y;

        if(dx) {
            g_camera.RotateYaw(g_rotation_speed*dx);
        }

        if(dy) {
            g_camera.RotatePitch(g_rotation_speed*dy);
        }

        glutWarpPointer(g_viewport_width/2, g_viewport_height/2);

        just_warped = true;
    }
}

//*****************MAIN*****************MAIN****************MAIN****************MAIN********************
int main(int argc, char **argv) {
	//Ajout pour la caméra
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Projet Gare : C.HEMBISE / F.DUBOIS / A.RATO");
	glutIgnoreKeyRepeat(1);

  glutTimerFunc(1, Timer, 0);

	init();
	//Ajout pour la caméra
  glutMouseFunc(Mouse);
  glutMotionFunc(MouseMotion);
  glutPassiveMotionFunc(MouseMotion);
  glutKeyboardFunc(Keyboard);
  glutKeyboardUpFunc(KeyboardUp);
  glutIdleFunc(Idle);

	glutReshapeFunc(reshape);
	glutMainLoop();

	return (EXIT_SUCCESS);
}
