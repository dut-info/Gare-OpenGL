#include "Parallelepiped.h"
#include "Object.h"
#include "Point.h"

#ifdef __APPLE__
//compilation sous MacOs par :
//gcc -framework GLUT -framework OpenGL -framework Cocoa source.c -o nom_executable
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

#ifdef __WIN32__
//parce qu'il manque des choses aux gens qui utilisent MsWindows, où OpenGL ne peut fonctionner que s'il discute avec le gestionnaire de fenêtres ("windows.h")
#define GLUT_DISABLE_ATEXIT_HACK  //utile si vous compilez en g++ sous windows avec le glut.lib prévu pour MsVisual
#include <windows.h>
#include "glut.h"  //il faut avoir le fichier "glut.h" dans le même répertoire que votre .cpp (et aussi le glut.lib et le glut.dll)
#endif

#ifdef __linux__
//pour les non-windowiens, GLUT (fenêtrage opengl) est inclu dans les distributions
//pour les ubuntiens : apt-get install freeglut3 freeglut3-dev
#include <GL/glut.h>
#endif

Parallelepiped::Parallelepiped(double x = 1, double y = 1, double z = 1)
{
	points = new Point[8];

	// origin
	double xi = origin[0];
	double yi = origin[1];
	double zi = origin[2];

	points[0] = Point(xi, yi, zi);
	points[1] = Point(xi, yi+y, zi);
	points[2] = Point(xi+x, yi+y, zi);
	points[3] = Point(xi+x, yi, zi);
	points[4] = Point(xi, yi, zi+z);
	points[5] = Point(xi+x, yi, zi+z);
	points[6] = Point(xi+x, yi+y, zi+z);
	points[7] = Point(xi, yi+y, zi+z);
}

void normal(Point p0, Point p1, Point p2) {

	double vect1X = p0.x-p1.x;
	double vect1Y = p0.y-p1.y;
	double vect1Z = p0.z-p1.z;

	double vect2X = p2.x-p1.x;
	double vect2Y = p2.y-p1.y;
	double vect2Z = p2.z-p1.z;

	double x = vect1Y*vect2Z-vect2Y*vect1Z;
	double y = -(vect1X*vect2Z-vect2X*vect1Z);
	double z = vect1X*vect2Y-vect2X*vect1Y;

	glNormal3d(x, y, z);

}

void Parallelepiped::modelize(float indice) {
	glBegin(GL_QUADS);
		normal(points[0], points[1], points[2]);
		Object::glVertex3f(points[0]);
		Object::glVertex3f(points[1]);
		Object::glVertex3f(points[2]);
		Object::glVertex3f(points[3]);
		normal(points[1], points[7], points[6]);
		Object::glVertex3f(points[1]);
		Object::glVertex3f(points[7]);
		Object::glVertex3f(points[6]);
		Object::glVertex3f(points[2]);
		normal(points[2], points[6], points[5]);
		Object::glVertex3f(points[2]);
		Object::glVertex3f(points[6]);
		Object::glVertex3f(points[5]);
		Object::glVertex3f(points[3]);
		normal(points[5], points[4], points[0]);
		Object::glVertex3f(points[5]);
		Object::glVertex3f(points[4]);
		Object::glVertex3f(points[0]);
		Object::glVertex3f(points[3]);
		normal(points[7], points[1], points[0]);
		Object::glVertex3f(points[7]);
		Object::glVertex3f(points[1]);
		Object::glVertex3f(points[0]);
		Object::glVertex3f(points[4]);
		//normal(points[5], points[6], points[7]);
		Object::glVertex3f(points[5]);
		Object::glVertex3f(points[6]);
		Object::glVertex3f(points[7]);
		Object::glVertex3f(points[4]);

/*
		glTexCoord2f(points[0].x,points[0].y);Object::glVertex3f(points[0]);
		glTexCoord2f(points[1].x,points[1].y);Object::glVertex3f(points[1]);
		glTexCoord2f(points[2].x,points[2].y);Object::glVertex3f(points[2]);
		glTexCoord2f(points[3].x,points[3].y);Object::glVertex3f(points[3]);
		normal(points[1], points[7], points[6]);
		glTexCoord2f(points[1].x,points[1].y);Object::glVertex3f(points[1]);
		glTexCoord2f(points[7].x,points[7].y);Object::glVertex3f(points[7]);
		glTexCoord2f(points[6].x,points[6].y);Object::glVertex3f(points[6]);
		glTexCoord2f(points[2].x,points[2].y);Object::glVertex3f(points[2]);
		normal(points[2], points[6], points[5]);
		glTexCoord2f(points[2].x,points[2].y);Object::glVertex3f(points[2]);
		glTexCoord2f(points[6].x,points[6].y);Object::glVertex3f(points[6]);
		glTexCoord2f(points[5].x,points[5].y);Object::glVertex3f(points[5]);
		glTexCoord2f(points[3].x,points[3].y);Object::glVertex3f(points[3]);
		normal(points[5], points[4], points[0]);
		glTexCoord2f(points[5].x,points[5].y);Object::glVertex3f(points[5]);
		glTexCoord2f(points[4].x,points[4].y);Object::glVertex3f(points[4]);
		glTexCoord2f(points[0].x,points[0].y);Object::glVertex3f(points[0]);
		glTexCoord2f(points[3].x,points[3].y);Object::glVertex3f(points[3]);
		normal(points[7], points[1], points[0]);
		glTexCoord2f(points[7].x,points[7].y);Object::glVertex3f(points[7]);
		glTexCoord2f(points[1].x,points[1].y);Object::glVertex3f(points[1]);
		glTexCoord2f(points[0].x,points[0].y);Object::glVertex3f(points[0]);
		glTexCoord2f(points[4].x,points[4].y);Object::glVertex3f(points[4]);
		normal(points[6], points[7], points[4]);
		glTexCoord2f(points[6].x,points[6].y);Object::glVertex3f(points[6]);
		glTexCoord2f(points[7].x,points[7].y);Object::glVertex3f(points[7]);
		glTexCoord2f(points[4].x,points[4].y);Object::glVertex3f(points[4]);
		glTexCoord2f(points[5].x,points[5].y);Object::glVertex3f(points[5]);
*/
	glEnd();
}
