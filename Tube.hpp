#ifndef TUBE_HPP
#define TUBE_HPP

#include "Object.h"

class Tube : public Object
{
public:
    Tube();
protected:
    virtual void modelize(float indice);
};

#endif
