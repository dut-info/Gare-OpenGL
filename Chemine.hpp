#ifndef CHEMINE_HPP
#define CHEMINE_HPP

#include "Object.h"

class Chemine : public Object
{
public:
    Chemine();
protected:
    virtual void modelize(float indice);
};

#endif
