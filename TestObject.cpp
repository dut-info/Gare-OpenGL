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

#include <GL/glut.h>

#include "Object.h"
#include "Parallelepiped.h"
#include "RailDroit.h"
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
void Grid();

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

float angle;

//Vitesse des mouvements de la caméra
const float g_translation_speed = 0.005;
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

/*
void rotation_souris(float& ax, float& ay) {
//rotation de la scene suivant les mouvements de la souris
//cout << "x : " << ax << "   y : " << ay << endl;

	glRotatef ( -ay, 0.0f, 0.0f, 1.0f );
	glRotatef ( ax, 1.0f, 0.0f, 0.0f );

	glTranslatef ( tx, ty, tz );

	glRotatef ( -ay, 0.0f, 0.0f, 1.0f );
	glRotatef ( ax, 0.0f, 1.0f, 0.0f );
}
*/

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
	
	//Description de la scene
	glLoadIdentity();

	affiche_repere();
	g_camera.Refresh();

    glColor3f(0.78f, 0.15f, 0.15f);

    Grid();

	//rotation_souris(angleX, angleY);
/*
    y
    |
    |
    |
    |__________ x
    /.   .   .
   /.   .   .
  /.   .   .
 /.   .   .
 z
*/

 		RailDroit rd(20, 1.5);

 		Parallelepiped p(2, 2, 2);
 		
 		rd.draw();
glPushMatrix();
	glTranslated(angle/4, 0, 0);
 	p.draw();
glPopMatrix();
/*

		Parallelepiped o(5,10,7);
		
		glRotatef( (angle*angle)/100, 1.0f, 1.0f, 0.0f);

		o.draw();

			double rayon = 4;
			double hauteur = 20;

			point3 centerBottom(0, 0, -hauteur/2);
			point3 centerTop(0, 0, hauteur/2);

			point3 tab[2*nbPoints];

			double teta = 2*M_PI/nbPoints;

			for (int i = 0; i < 2*nbPoints; ++i) {
				double angle = (i%nbPoints+1)*teta;
				double haut = (i >= nbPoints) ? hauteur/2 : -hauteur/2;
				tab[i] = point3(rayon*cos(angle), rayon*sin(angle), haut);
			}


			glBegin(GL_TRIANGLES);

				glColor3f (0.1f , 0.8f, 0.8f);

				// Face bas
				for (int i = 0; i < nbPoints; ++i) {
					glVertex3f(centerBottom.x, centerBottom.y, centerBottom.z);
					int firstPtn = (i+1)%nbPoints;
					glVertex3f(tab[firstPtn].x, tab[firstPtn].y, tab[firstPtn].z);
					glVertex3f(tab[i].x, tab[i].y, tab[i].z);
				}

				// Face haut
				for (int i = 0; i < nbPoints; ++i) {
					glColor3f (0.8f , 0.1f, 0.8f);

					glVertex3f(centerTop.x, centerTop.y, centerTop.z);

					int firstPtn = (i+1)%(nbPoints)+nbPoints;
					glVertex3f(tab[firstPtn].x, tab[firstPtn].y, tab[firstPtn].z);
					
					int secondPtn = i+nbPoints;
					glVertex3f(tab[secondPtn].x, tab[secondPtn].y, tab[secondPtn].z);
				}

			glEnd();

			glBegin(GL_QUADS);
				glColor3f (0.8f , 0.8f, 0.1f);
				for(int i = 0; i < nbPoints; i++) {
					int one = (i+1)%nbPoints;
					glVertex3f(tab[one].x, tab[one].y, tab[one].z);
					glVertex3f(tab[i].x, tab[i].y, tab[i].z);
					glVertex3f(tab[i+nbPoints].x, tab[i+nbPoints].y, tab[i+nbPoints].z);
					int two = (i+1)%nbPoints+nbPoints;
					glVertex3f(tab[two].x, tab[two].y, tab[two].z);
				}
			glEnd();
*/
	glutSwapBuffers();// echange des buffers
}

/*
void calculNormal(point3 p1, point3 p2, point3 p3, point3 p4) {
	double u[3];
	double v[3];

	u[0] = p1.x-p2.x;
	u[1] = p1.y-p2.y;
	u[2] = p1.z-p2.z;

	v[0] = p3.x-p4.x;
	v[1] = p3.y-p4.y;
	v[2] = p3.z-p4.z;


	glNormal3d(u[1]*v[2]-u[2]*v[1],
			   u[2]*v[0]-u[0]*v[2],
			   u[0]*v[1]-u[1]*v[0]);
}
*/

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h) {
   g_viewport_width = w;
   g_viewport_height = h;

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //gluPerspective(70,(double)700/700,0,2000);
   glOrtho ( -20.0f, 20.0f, -20.0f, 20.0f, -20.0f, 20.0f);
   gluPerspective (1, (GLfloat)w / (GLfloat)h, 0.1 , 100.0); //set the perspective (angle of sight, width, height, ,depth)
   glMatrixMode(GL_MODELVIEW);
}

/*
GLvoid gestionSouris(int x, int y) {
	angleX = float(x/2) * 720.0f / float(WIDTH); //gere l'axe Oy
	angleY = - ( float(y/2) * 180.0f / float(HEIGHT - 90.0f) ) * 4.0f; //gere l'axe Ox

	glutPostRedisplay();
}
()*/

/*
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
*/


/*
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

		case 'r':
			tz += int(pasDeplacement);
		break;

		case 'f':
			tz -= int(pasDeplacement);
		break;

		case 'p':
			nbPoints++;
		break;

		case 'm':
			if(nbPoints > 1) nbPoints--;
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
*/

/*
GLvoid window_idle()
{
	angle+=0.1f;
glutPostRedisplay();
}
*/

//*****************************************AJOUT DE FREE FLY CAMERA****************************************************************

void Grid()
{
    glPushMatrix();
    glColor3f(1,1,1);

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glEnd();
    }

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
        glEnd();
    }

    glPopMatrix();
}

/*
void Display (void) {
    glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();

	g_camera.Refresh();

    glColor3f(0,1,0);

    glutWireTeapot(0.5);
    Grid();

    glutSwapBuffers(); //swap the buffers
}
*/

/*
void Reshape (int w, int h) {
    g_viewport_width = w;
    g_viewport_height = h;

    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1 , 100.0); //set the perspective (angle of sight, width, height, ,depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}
*/

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
    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
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
	//glutKeyboardFunc(&window_key_down);
	//glutDisplayFunc(display);
	//glutPassiveMotionFunc(gestionSouris);
	//glutSpecialFunc(&gestionFleche);
	//glutIdleFunc(&window_idle);

	glutMainLoop();

return (EXIT_SUCCESS);
}