#include "Roue.h"
#include "Object.h"
#include <GL/glut.h>

const double epaisseur = 0.34;
const double hauteur   = 0.7;

Roue::Roue() {

}

void Roue::modelize() {
  GLUquadric* params;
  params = gluNewQuadric();

  // centre la roue
  glTranslated(0, epaisseur/2, 0);
  // place la roue sur le bon axe
  glRotatef(90, 1, 0, 0);

  gluQuadricDrawStyle(params,GLU_FILL);
  gluCylinder(params, hauteur, hauteur, epaisseur, 20, 1);
  gluDisk(params, 0, hauteur, 20, 1);
  glTranslated(0, 0, epaisseur);
  gluDisk(params, 0, hauteur, 20, 1);
}
