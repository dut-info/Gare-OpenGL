
#include "Sol.hpp"

#include "Wagon.hpp"
#include "Object.h"
#include "Parallelepiped.h"
#include "Roue.h"
#include "Tube.hpp"
#include "Locomotive.hpp"
#include "Chemine.hpp"
#include "Toure.hpp"
#include "TourePetite.hpp"



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



Sol::Sol() {


}

void Sol::modelize(float indice) {

    Parallelepiped herbe(1000,1000,0.1);


    Parallelepiped sol(10.2,10,0.4);

    Parallelepiped mur1(0.2,8,5);

    Parallelepiped mur2(0.2,8,7.6);

    Parallelepiped mur3(9.8,0.2,7.6);

    Parallelepiped porteI1(1.2,0.1,2.6);
    Parallelepiped porteE1(1.2,0.1,2.6);

    Parallelepiped porteI2(1.2,0.1,2.6);
    Parallelepiped porteE2(1.2,0.1,2.6);

    Parallelepiped plafond(11.6 , 9 , 0.1);


    Parallelepiped quai(10.2,2,0.4);

    Parallelepiped barriere(10.2,0.2,0.85);



    //bureau
    Parallelepiped pq1(0.1 , 4.8 , 2);
    Parallelepiped pq2(2.3, 0.1 , 2);
    Parallelepiped pqplafond(0.1,5,3);


    // les pylones
    Toure t1;
    TourePetite t2;


    glTranslated(0,0,0);


    glPushMatrix();
    glTranslated(0,0,0.2);
    mur1.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(10,0,0.2);
    mur2.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.2,0,0.2);
    mur3.draw();
    glPopMatrix();

        glPushMatrix();
        glTranslated(4 , 0.21 , 0.2);
        glColor3f (0.0f , 0.0f, 1.0f);
        porteI1.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(4 , -0.21 , 0.2);
        glColor3f (0.0f , 0.0f, 1.0f);
        porteE1.draw();
        glPopMatrix();


        glPushMatrix();
        glTranslated(5.3 , 0.21 , 0.2);
        glColor3f (0.0f , 0.0f, 1.0f);
        porteI2.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(5.3 , -0.21 , 0.2);
        glColor3f (0.0f , 0.0f, 1.0f);
        porteE2.draw();
        glPopMatrix();


   //*********** B U R E A U ****************
    glPushMatrix();
    glTranslated(2.4 , 0.2 , 0);
    glColor3f (0.0f , 0.0f, 1.0f);
    pq1.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.2 , 5 , 0);
    glColor3f (0.0f , 0.0f, 1.0f);
    pq2.draw();
    glPopMatrix();
    //*********** FIN ****************

    glPushMatrix();
    glTranslated(0, 0, -0.2);
    glColor3f (0.1f , 0.8f, 0.8f);
    sol.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-50, -50, -0.4);
    glColor3f (0.01f , 0.7f, 0.1f);
    herbe.draw();
    glPopMatrix();


    glPushMatrix();
    glTranslated(0, 14.3, 0.2);
    glColor3f (0.1f , 0.8f, 0.8f);
    quai.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 16.3, 0.2);
    glColor3f (0.1f , 0.8f, 0.8f);
    barriere.draw();
    glPopMatrix();


    glPushMatrix();
    glColor3f (0.1f , 0.8f, 0.0f);
    glTranslated(2.2, 4.9 , 0.2);
    t1.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslated(8.2, 4.9 ,0.2);
    t2.draw();
    glPopMatrix();


    glPushMatrix();
    glRotated(-15, 0, 1, 0);
    glTranslated(0.95, 0.2 ,5);
    glColor3f (0.4f , 0.2f, 2.8f);
    plafond.draw();
    glPopMatrix();


}
