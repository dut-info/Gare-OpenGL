//Squelette pour la transformation. A vous de créer la suite.
//compilation barbare sous linux : g++ -Wall tp_rotation.cpp -o tp_rotation -lglut

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

#include <GL/glut.h>

using namespace std;

#define WIDTH  600
#define HEIGHT 600
#define NBMAXOFPOINTS 100
#define PI 3.14159

#define KEY_ESC 27

float angleX = 0.0f; //angle de rotation en Y de la scene
float angleY = 0.0f; //angle de rotation en X de la scene

//variable pour l'angle de rotation de la théière
float angle=0.0f;

float pasDeplacement = 1.25f;


//position lumiere
int LightPos[4] = {100,100,100,1};
int MatSpec [4] = {1,1,1,1};

float tx = 0.0f;
float ty = 0.0f;
float tz = 0.0f;

float h = 30;
float r = 6;

float x,y,z;


int la = 10;
int lo = 25;


/* initialisation d'OpenGL*/
static void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

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


void rotation_souris(float& ax, float& ay) {
//rotation de la scene suivant les mouvements de la souris
	glRotatef ( -ay, 0.0f, 0.0f, 1.0f );
	glRotatef ( ax, 0.0f, 1.0f, 0.0f );
	glTranslatef ( tx, ty, tz );

	glRotatef ( -ay, 0.0f, 0.0f, 1.0f );
	glRotatef ( ax, 0.0f, 1.0f, 0.0f );
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

    glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;//effacement du buffer
    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

	//Description de la scene
	glLoadIdentity();
	affiche_repere();
    rotation_souris(angleX, angleY);


    //Code ici...
    float vt = angle;
    float vs = 0.5*angle;

	// soleil
	glPushMatrix();
		glColor3f( 0.9f, 0.8f, 0.2f );
		glRotatef( vs, 0.0f, 0.0f, 1.0f );
		glutWireSphere(4.0f, lo, la);
	glPopMatrix();

	// terre
	glPushMatrix();
		glColor3f( 0.0f, 0.6f, 1.1f );	
		glRotatef(vt, 0.0f, 0.0f, 1.0f );
		glTranslatef(10.0f, 0.0f, 0.0f);
		glRotatef( 3*vs, 0.0f, 0.0f, 1.0f );
		glutWireSphere(2.0f, lo, la);

		// lune
		glPushMatrix();
			glColor3f( 0.6f, 0.6f, 0.6f );
			glRotatef(2*vt, 0.0f, 0.0f, 1.0f );
			glTranslatef(4.0f, 0.0f, 0.0f);
			glRotatef(1.5*vs, 0.0f, 0.0f, 1.0f );
			glutWireSphere(1.0f, lo, la);
		glPopMatrix();

	glPopMatrix();


	glPushMatrix();
		glColor3f( 1.6f, 0.2f, 0.1f );
		glRotatef(vt-100.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef(18.0f, 0.0f, 0.0f);
		glRotatef(vs, 0.0f, 0.0f, 1.0f );
		glutWireSphere(1.8f, lo, la);		
	glPopMatrix();
	//Mise en couleur

	//ajout dans la scéne d'une théière (après les transformations)


    glFlush();
	glutSwapBuffers();// echange des buffers
}

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   //gluPerspective(120,(double)640/480,0,2000);
   
   //gluLookat (0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0)
   glOrtho ( -20.0f, 20.0f, -20.0f, 20.0f, -20.0f, 20.0f);

   glMatrixMode(GL_MODELVIEW);
}

GLvoid gestionSouris(int x, int y) {
	angleX = float(x) * 720.0f / float(WIDTH); //gere l'axe Oy
	angleY = - ( float(y) * 180.0f / float(HEIGHT - 90.0f) ) * 4.0f; //gere l'axe Ox

	glutPostRedisplay();
}

GLvoid gestionFleche(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP :
			tz += int(pasDeplacement);
		break;

		case GLUT_KEY_DOWN :
			tz -= int(pasDeplacement);
		break;
	}
	glutPostRedisplay();
}

GLvoid window_key_down(unsigned char key, int x, int y)  { //appuie des touches
switch (key) {
//deplacement de la camera
	case 'z':
		ty += int(pasDeplacement);
	break;

	case 's':
		ty -= int(pasDeplacement);
	break;

	case 'q':
		tx -= int(pasDeplacement);
	break;

	case 'd':
		tx += int(pasDeplacement);
	break;

	case 'e':
		tz -= int(pasDeplacement);
	break;

	case 'r':
		tz += int(pasDeplacement);
	break;

//sortie
	case KEY_ESC:
		exit(0);
		break;

	default:
		cerr << "Touche " << key << " non active.\n";
	break;
	}

glutPostRedisplay();
}

//Si on n'a rien à afficher, on lance cette fonction
//attention : la période n'est pas fixe (fonctionnement "quand on à le temps")
GLvoid window_idle()
{
	angle+=0.5f;
glutPostRedisplay();


}

int main(int argc, char **argv) {
	glutInitWindowSize(700, 700);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Ma fenetre");

	init();

	glutReshapeFunc(reshape);
	glutKeyboardFunc(&window_key_down);
	glutDisplayFunc(display);
	//glutPassiveMotionFunc(gestionSouris);
	glutSpecialFunc(&gestionFleche);

	//fonction appellée dès que le temps le permet
	glutIdleFunc(&window_idle);

	glutMainLoop();

return (EXIT_SUCCESS);
}
