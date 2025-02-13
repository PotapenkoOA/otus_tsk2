#ifndef __MOVE
#define __MOVE

#include "movingobject.h"
#include "command.h"

#include <iostream>
using namespace std;


class Move: public ICommand {

    IMovingObject *pObject;

    public: 
        Move(IMovingObject *obj)
        {
            pObject = obj;
        }

        void Execute()
        {
            pObject->setLocation( pObject->getLocation() + pObject->getVelocity()) ;

        }
};


#endif