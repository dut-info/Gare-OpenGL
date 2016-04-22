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
#define GLUT_DISABLE_ATEXIT_HACK	//utile si vous compilez en g++ sous windows avec le glut.lib prévu pour MsVisual
#include <windows.h>
#include "glut.h"	//il faut avoir le fichier "glut.h" dans le même répertoire que votre .cpp (et aussi le glut.lib et le glut.dll)
#endif

#ifdef __linux__
//pour les non-windowiens, GLUT (fenêtrage opengl) est inclu dans les distributions
//pour les ubuntiens : apt-get install freeglut3 freeglut3-dev
#include <GL/glut.h>
#endif


Object::Object()
{
	//origin[3] = {0, 0, 0};
}

void Object::glVertex3f(Point p) {
	glVertex3d(p.x, p.y, p.z);
}

void Object::draw(float indice) {
	glPushMatrix();
	modelize(indice);
	glPopMatrix();
}
