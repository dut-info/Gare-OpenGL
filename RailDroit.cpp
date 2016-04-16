#include "RailDroit.h"
#include "Parallelepiped.h"

#include <GL/glut.h>

RailDroit::RailDroit(double longueur = 10, double espacement = 0.90)
{
	this->longueur = longueur;
	this->espacement = espacement;
}

void RailDroit::modelize()
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