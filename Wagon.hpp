#ifndef WAGON_HPP
#define WAGON_HPP

#include "Object.h"

class Wagon : public Object
{
public:
    Wagon();
protected:
    virtual void modelize(float indice);
};

#endif
