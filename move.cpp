#include <move.h>

Move::Move()
{
}

void Move::setLocation(vector<double> newValue)
{
   m_Location = newValue;
}

vector<double> Move::getVelocity() 
{
   return m_Velocity;
}

vector<double> Move::getLocation()
{
   return m_Location;
}

vector<double>  Plus(vector<double> a, vector<double> b)
{
   vector<double> result;
   int max_size = a.size();

   for( int i = 0; i <  max_size; i++ )
   {
      result[i] = a[i] + b [i];
   }
   return result;
}

void Move::Execute()
{
   //setLocation( Plus(getLocation(), getVelocity())) ;
}
