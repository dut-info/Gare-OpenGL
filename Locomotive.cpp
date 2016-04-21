#include "Wagon.hpp"
#include "Object.h"
#include "Parallelepiped.h"
#include "Roue.h"
#include "Tube.hpp"
#include "Locomotive.hpp"
#include "Chemine.hpp"



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


Locomotive::Locomotive() {
    
}

void Locomotive::modelize() {
    Roue r1;
    Roue r2;
    Roue r3;
    Roue r4;
    
    Chemine che;
    
    Parallelepiped c(6,1.8,2);
    
    Parallelepiped ch(1,1,4);
    
    Parallelepiped cb(3,1.8,1.4);

    Tube t2;

    //c box
    glPushMatrix();
    glTranslated(-3,-0.9,1);
    cb.draw();
    glPopMatrix();
    
    //chemine
    glPushMatrix();
    glTranslated(2, -1.6, 0);
    che.draw();
    glPopMatrix();
    
    //roue arriere droit
    glPushMatrix();
    glTranslated(-2, -1.1,-1);
    r1.draw();
    glPopMatrix();
    
    //roue arriere gauche
    glPushMatrix();
    glTranslated(-2, 1.1, -1);
    r2.draw();
    glPopMatrix();
    
    //roue avant gauche
    glPushMatrix();
    glTranslated(2, -1.1, -1);
    r3.draw();
    glPopMatrix();
    
    //roue avant gauche
    glPushMatrix();
    glTranslated(2, 1.1, -1);
    r4.draw();
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