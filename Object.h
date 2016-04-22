#ifndef OBJECT_H
#define OBJECT_H

#include "Point.h"

class Object
{
public:
	Object();
	void draw(float indice = -1);
	static void glVertex3f(Point p);
protected:
	// x, y, z
	virtual void modelize(float indice) = 0;
	double origin[3] = {0, 0, 0};
	Point *points;
};

#endif
