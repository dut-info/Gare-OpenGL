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

void Locomotive::modelize(float indice) {
    Roue r1;
    Roue r2;
    Roue r3;
    Roue r4;


    /*GLubyte Texture[16] =
    {
    0,0,0,0, 0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF, 0,0,0,0
    };
        //Image (2x2)
    GLuint Nom;
    */

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


   /* glClearColor(.5,.5,.5,0);   //Change la couleur du fond
    glEnable(GL_DEPTH_TEST);    //Active le depth test
    glEnable(GL_TEXTURE_2D);    //Active le texturing
    glGenTextures(1,&Nom);  //Génère un n° de texture
    glBindTexture(GL_TEXTURE_2D,Nom);   //Sélectionne ce n°
    glTexImage2D (
        GL_TEXTURE_2D,  //Type : texture 2D
    0,  //Mipmap : aucun
    4,  //Couleurs : 4
    2,  //Largeur : 2
    2,  //Hauteur : 2
    0,  //Largeur du bord : 0
    GL_RGBA,    //Format : RGBA
    GL_UNSIGNED_BYTE,   //Type des couleurs
    Texture     //Addresse de l'image
    );  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);*/


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


   //glDisable(GL_TEXTURE_2D);    //Desactive le texturing
    

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