#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include "Object.h"

class Locomotive : public Object
{
public:
    Locomotive();
protected:
    virtual void modelize();
};

#endif
