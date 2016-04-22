#include "RailDroit.h"
#include "Parallelepiped.h"

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


RailDroit::RailDroit(double longueur, double espacement)
{
	this->longueur = longueur;
	this->espacement = espacement;
}

void RailDroit::modelize(float indice)
{
	double balast_height = 0.2;
	double balast_width = 0.4;
	double balast_spaces = 1.2;
	double rail_width = 0.17;
	double ballast_margin = 0.3;

	int nb_ballast = (int) longueur / (balast_width+balast_spaces);
	glPushMatrix();
	for (int i = 0; i < nb_ballast; ++i)
	{
		glTranslated(balast_spaces, 0, 0);
		Parallelepiped b(balast_width, espacement+2*ballast_margin+2*rail_width, balast_height);
		b.draw();
	}
	glPopMatrix();

	//glPushMatrix();
		glTranslated(0, ballast_margin, balast_height);
		Parallelepiped r1(longueur, rail_width, 0.2);
		r1.draw();
		glTranslated(0, 0.07+espacement, 0);
		Parallelepiped r2(longueur, rail_width, 0.2);
		r2.draw();
	//glPopMatrix();
}
