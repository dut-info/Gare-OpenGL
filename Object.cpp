#include "Object.h"
#include "Point.h"

#include <GL/glut.h>

Object::Object()
{
	//origin[3] = {0, 0, 0};
}

void Object::glVertex3f(Point p) {
	glVertex3d(p.x, p.y, p.z);
}

void Object::draw() {
	glPushMatrix();
	modelize();
	glPopMatrix();
}