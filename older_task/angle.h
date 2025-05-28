#ifndef __ANGLE
#define __ANGLE

//# define M_PI           3.14159265358979323846  /* pi */

// хранение угла в целых числах
/// n - число частей, на которые делится круг
/// d - число задействованных частей круга

class Angle{

    char n;
    char d;

    public:

    float getRadAngle()
    {
        return 2*M_PI*d/(float)n;
    }

    Angle( )
    {
        this->d = 0;
        this->n = 1;
    }

    Angle(char d, char n)
    {
        this->d = d;
        this->n = (n != 0)? n : 1;
    }

    Angle operator +( const Angle& a1 )
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

    friend bool operator ==( const Angle& b, const Angle& c){  return (c.n == b.n) && (c.d == b.d); }

    friend bool operator !=( const Angle& b, const Angle& c){  return (c.n == b.n) && (c.d != b.d); }

    friend bool operator >=( const Angle& b, const Angle& c){  return (c.n >= b.n) && (c.d >= b.d); }
    friend bool operator <=( const Angle& b, const Angle& c){  return (c.n <= b.n) && (c.d <= b.d); }
}; 

#endif
