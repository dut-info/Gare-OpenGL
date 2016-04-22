#ifndef SOL_HPP
#define SOL_HPP

#include "Object.h"

class Sol : public Object
{
public:
    Sol();
protected:
    virtual void modelize(float indice);
};

#endif
