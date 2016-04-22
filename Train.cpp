#include "Train.h"
#include "Object.h"
#include "Roue.h"
#include "Parallelepiped.h"
#include "Chemine.hpp"
#include "Wagon.hpp"
#include "Tube.hpp"
#include "Locomotive.hpp"






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

Train::Train() {

}

void Train::modelize(float indice) {



    Locomotive l;
    Locomotive l1;



    int nbWagons = 4;
    float longueur = ((nbWagons + 1) * 6 +(2*0.49) +3.95 )/ 2 ;


    glTranslated(longueur, 0, 0);
    l.draw(indice);
    glPushMatrix();

    for (int i = 0; i < nbWagons; i++) {
        Wagon w1;
        glTranslated(-7, 0, 0);
        w1.draw(indice);
    }
    glPopMatrix();


    glPushMatrix();
    glTranslated(- (longueur*2), 0.1, 0);

    glRotated(-180, 0, 0, 1);
    l1.draw();
    glPopMatrix();


}
