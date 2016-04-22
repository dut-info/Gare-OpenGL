#ifndef TOUREPETITE_HPP
#define TOUREPETITE_HPP

#include "Object.h"

class TourePetite : public Object
{
public:
    TourePetite();
protected:
    virtual void modelize(float indice);
};

#endif
