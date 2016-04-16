#ifndef PARALLELEPIPED_H
#define PARALLELEPIPED_H

#include "Object.h"

class Parallelepiped : public Object
{
public:
	Parallelepiped(double x, double y, double z);
protected:
	virtual void modelize();
};

#endif