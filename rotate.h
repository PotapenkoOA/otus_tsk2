#ifndef ___ROTATE
#define ___ROTATE

#include <iostream>
using namespace std;

#include "rotatingobject.h"

class Rotate{

    IRotatingObject *obj;
    public:
    Rotate( IRotatingObject *o )
    {
        obj = o;
    }
    void Execute()
    {
       obj->setAngle(obj->getAngle()+obj->getAngularVelocity());
    }
};

#endif