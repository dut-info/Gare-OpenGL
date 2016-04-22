#include "Wagon.hpp"
#include "Object.h"
#include "Parallelepiped.h"
#include "Roue.h"
#include "Tube.hpp"
#include <iostream>

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


Wagon::Wagon() {

}

void Wagon::modelize(float indice) {

    Roue r1;
    Roue r2;
    Roue r3;
    Roue r4;

    Parallelepiped c(6,1.8,2);
    Parallelepiped c1(6,1.8,0.5);
    Tube t;
    Tube t2;



    glColor3f (0.9f , 0.3f, 0.2f);

    //roue arriere droit
    glPushMatrix();

    glTranslated(-2, -1.1,-1);
    glRotatef(indice*15, 0, 1, 0);
    r1.draw();
    glPopMatrix();

    //roue arriere gauche
    glPushMatrix();
    glTranslated(-2, 1.1, -1);
    glRotatef(indice*15, 0, 1, 0);
    r2.draw();
    glPopMatrix();

    //roue avant gauche
    glPushMatrix();
    glTranslated(2, -1.1, -1);
    glRotatef(indice*15, 0, 1, 0);
    r3.draw();
    glPopMatrix();

    //roue avant gauche
    glPushMatrix();
    glTranslated(2, 1.1, -1);
    glRotatef(indice*15, 0, 1, 0);
    r4.draw();
    glPopMatrix();



    glPushMatrix();
    glTranslated(-3,-0.9, 1);
    c1.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(3, -0.2,0);
    t.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3.5,-0.2,0);
    t2.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3,-0.9, -1);
    glColor3f (0.1f , 0.8f, 0.8f);
    c.draw();
    glPopMatrix();

}
