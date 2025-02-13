#ifndef __VECTOR
#define __VECTOR

#include <cmath>
using namespace std;

#include "angle.h"

class Vector2{

    int x;
    int y;

    public:
    
    Vector2(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2 operator +( const Vector2& v )
    {        
        return Vector2(  this->x + v.x, this->y + v.y );
    }

    Vector2 rotate(  Angle& v )
    {        
        return Vector2(  x*cos(v.getRadAngle()) +  y*sin(v.getRadAngle()),  
         x*sin(v.getRadAngle()) + y*cos(v.getRadAngle()));
    }

    Vector2& operator = (const Vector2& C) {
        
        x = C.x;
        y = C.y;
        return *this;
    }

    friend bool operator ==( const Vector2& b, const Vector2& c){  return (c.x == b.x) && (c.y == b.y); }

    friend bool operator !=( const Vector2& b, const Vector2& c){  return (c.x == b.x) && (c.y != b.y); }

    friend bool operator >=( const Vector2& b, const Vector2& c){  return (c.x >= b.x) && (c.y >= b.y); }
    friend bool operator <=( const Vector2& b, const Vector2& c){  return (c.x <= b.x) && (c.y <= b.y); }
}; 

#endif
