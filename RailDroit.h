#ifndef RAIL_DROIT_H
#define RAIL_DROIT_H

#include "Object.h"

class RailDroit : public Object
{
public:
	RailDroit(double longueur, double espacement);
protected:
	virtual void modelize(float indice);
	double longueur;
	double espacement;
};

#endif
