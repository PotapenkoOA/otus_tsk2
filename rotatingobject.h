#ifndef __ROTATINGOBJ
#define __ROTATINGOBJ

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;


class Angle{

    char n;
    char d;

    public:

    Angle( )
    {
        this->d = 0;
        this->n = 1;
    }

    Angle(int d, int n)
    {
        this->d = d;
        this->n = n;
    }

    Angle operator+( const Angle& a1 )
    {
        if( a1.n != n )
        {
            throw invalid_argument("a1.n != a2.n"); 
        }

        if( n == 0 )
            throw invalid_argument("n == 0");  

        return Angle(( d + a1.d )%a1.n, n );
    }

    Angle& operator = (const Angle& C) {
        
        d = C.d;
        n = C.n;
        return *this;
    }

    bool operator ==( const Angle& b){  return (n == b.n) && (d == b.d); }

    bool operator !=( const Angle& b){  return (n == b.n) && (d != b.d); }

    bool operator >=( const Angle& b){  return (n == b.n) && (d >= b.d); }
    bool operator <=( const Angle& b){  return (n == b.n) && (d <= b.d); }

    bool operator > ( const Angle& b){  return (n == b.n) && (d > b.d); }
    bool operator < ( const Angle& b){  return (n == b.n) && (d < b.d); }
}; 


class IRotatingObject{
public:
virtual Angle getAngle() = 0;
virtual Angle getAngularVelocity() = 0;
virtual void setAngle(Angle a) = 0;

};



class RotatingMock : public IRotatingObject {
  public:
    MOCK_METHOD(Angle, getAngularVelocity, (), (override));
    MOCK_METHOD(Angle, getAngle, (), (override));
    MOCK_METHOD(void, setAngle, (Angle a) , (override));
};

#endif
