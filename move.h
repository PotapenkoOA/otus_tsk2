#ifndef __MOVE
#define __MOVE

#include "movingobject.h"

#include <vector>
#include <iostream>
using namespace std;

class Vector{
    int x;
    int y;
    public:
    Vector(int x, int y){ this->x = x; this->y = y; }

    static Vector Plus( Vector a, Vector b )
    {
        return Vector( a.x + b.x, a.y + b.y );
    }

};

vector<int>  Plus(vector<int> a, vector<int> b)
{
   //проверка на двумерность
   vector<int> result {0,0};
   
   int max_size = 2;
   for( int i = 0; i <  max_size; i++ )
   {
      result[i] = a[i] + b [i];
   }

   return result;
}

class Move {

    IMovingObject *pObject;

    public: 
        Move(IMovingObject *obj)
        {
            pObject = obj;
        }

        void Execute()
        {
            pObject->setLocation( Plus(pObject->getLocation(), pObject->getVelocity())) ;

        }
};


#endif